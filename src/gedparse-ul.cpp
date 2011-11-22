/**
 * parseged.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <exception>
// mongo
#include "client/dbclient.h"
// boost
#include <boost/program_options.hpp>
// familysearch gedcom
#include "Gedcom.hpp"
#include "Record.hpp"
#include "GedparseULDelegate.hpp"
// fsdev
#include "CSVOStream.hpp"

using namespace std;
using namespace boost;
using namespace mongo;
using namespace FamilySearch::GEDCOM;
using namespace fsdev;

/**
 * Tool to parse through an unlinked GEDCOM file and put the data into a Mongo Database.
 *
 * ex.
 *
 *   ./parseged --if=MYGEDCOM.GED --db=scots --col=records_low
 *
 * - *if* in-file
 * - *db* the database to use
 * - *col* the collection to use in the database
 * - *ro* `YES`|=`NO` whether to just read the GEDCOM and not try any Mongo-stuff.
 */
int main(int argc, char **argv)
{
    string infile;
    string database;
    string collection;
    bool readonly=true;
    bool csv_readonly=true;
    string outfile;
    bool die=false;
    try {
        program_options::options_description desc("Allowed options");
        desc.add_options()
            ("if", program_options::value<std::string>(), "input file, probably a GEDCOM")
            ("db", program_options::value<std::string>(), "database to use in Mongo")
            ("col",program_options::value<std::string>(), "collection to use in Mongo")
            ("mongo-ro", program_options::value<bool>()->default_value(true), "if yes, just parse and don't write to Mongo")
            ("csv-ro", program_options::value<bool>()->default_value(true), "if yes, just parse and don't write to a CSV file")
            ("of", program_options::value<std::string>(), "output file, will be written as a CSV")
            ("help", "produce this here frigg'n help message")
        ;
    
        program_options::variables_map vm;
        program_options::store(program_options::parse_command_line(argc, argv, desc), vm);
    
        if (vm.count("help")) {
            cout << desc << endl;
            return 1;
        }
    
        if (vm.count("if")) {
            infile = vm["if"].as<string>();
            cout << "Using file " << infile << endl;
        } else {
            cout << "Input file was not set." << endl;
            die=true;
        }
        
        if (!vm["mongo-ro"].as<bool>()) {
      
            readonly = vm["mongo-ro"].as<bool>();
      
            if (!readonly) {
        
                if (vm.count("db")) {
                    database = vm["db"].as<string>();
                } else {
                    cout << "Database not set." << endl;
                    die=true;
                }
        
                if (vm.count("col")) {
                    collection = vm["col"].as<string>();
                } else {
                    cout << "Collection not set." << endl;
                    die=true;
                }
        
            }
      
        } else {
            cout << "Running in readonly mode, all database args ignored." << endl;
        }
        
        if (!vm["csv-ro"].as<bool>()) {
            
            csv_readonly = vm["csv-ro"].as<bool>();
            
            if (!csv_readonly) {
                if (vm.count("of")) {
                    outfile = vm["of"].as<string>();
                } else {
                    cout << "Outfile not set!" << endl;
                    die = true;
                }
            }
            
        }
    
        if (die) {
            cout << desc << endl;
            return 1;
        }
    
    } catch(std::exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    } catch(...) {
        cerr << "Exception of unknown type!" << endl;
        return 1;
    }
    
    GedparseULDelegate * dg = new GedparseULDelegate();
    
    if (!readonly) {
        DBClientConnection * conn = new DBClientConnection;
        conn->connect("localhost");
        string colstring;
        colstring.append(database);
        colstring.append(".");
        colstring.append(collection);
        dg->setCollection(colstring);
        dg->setConnection(*conn);
        dg->setUsingDb(true);
    }
    
    if (!csv_readonly) {
        CSVOStream * csv_os = new CSVOStream(outfile.c_str());
        FamilySearch::GEDCOM::Record().emitFieldHeaders(*csv_os);
        dg->setCSVOStream(*csv_os);
        dg->setUsingCSV(true);
    }

    auto_ptr<ifstream> inputFile(new ifstream(infile.c_str(), ifstream::in));
    auto_ptr<Gedcom> ged(new Gedcom());
    ged->setDelegate(*dg);
    inputFile->ignore(2, '\n');
    if (inputFile->peek()!='0') {
        cerr << "Malformed GEDCOM. It should start with a \\r\\n0!" << endl;
        return 1;
    } 
  
    *inputFile >> *ged;

    cout << "Record count: " << ged->getRecords().size() << endl;

    return 0;
}

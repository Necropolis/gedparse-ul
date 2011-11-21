/**
 * parseged.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
// mongo
#include "client/dbclient.h"
// boost
#include <boost/program_options.hpp>
// familysearch gedcom
#include "Gedcom.hpp"
#include "Record.hpp"

using namespace FamilySearch::GEDCOM;

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
  std::string infile;
  std::string database;
  std::string collection;
  bool readonly=false;
  bool die=false;
  try {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
      ("if", boost::program_options::value<std::string>(), "input file, probably a GEDCOM")
      ("db", boost::program_options::value<std::string>(), "database to use in Mongo")
      ("col",boost::program_options::value<std::string>(), "collection to use in Mongo")
      ("ro", boost::program_options::value<bool>()->default_value(false), "if yes, just parse and don't write to Mongo")
      ("help", "produce this here frigg'n help message")
    ;
    
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }
    
    if (vm.count("if")) {
      infile = vm["if"].as<std::string>();
      std::cout << "Using file " << infile << std::endl;
    } else {
      std::cout << "Input file was not set." << std::endl;
      die=true;
    }
    
    if (!vm["ro"].as<bool>()) {
      
      readonly = vm["ro"].as<bool>();
      
      if (!readonly) {
        
        if (vm.count("db")) {
          database = vm["db"].as<std::string>();
        } else {
          std::cout << "Database not set." << std::endl;
          die=true;
        }
        
        if (vm.count("col")) {
          collection = vm["col"].as<std::string>();
        } else {
          std::cout << "Collection not set." << std::endl;
          die=true;
        }
        
      }
      
    } else {
      std::cout << "Running in readonly mode, all database args ignored." << std::endl;
    }
    
    if (die) {
      std::cout << desc << std::endl;
      return 1;
    }
    
  } catch(std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  } catch(...) {
    std::cerr << "Exception of unknown type!" << std::endl;
    return 1;
  }

  std::auto_ptr<std::ifstream> inputFile(new std::ifstream(infile.c_str(), std::ifstream::in));
  std::auto_ptr<FamilySearch::GEDCOM::Gedcom> ged(new FamilySearch::GEDCOM::Gedcom());
  inputFile->ignore(2, '\n');
  if (inputFile->peek()!='0') {
    std::cerr << "Malformed GEDCOM. It should start with a \\r\\n0!" << std::endl;
    return 1;
  }
  
  *inputFile >> *ged;

  std::cout << "Record count: " << ged->getRecords().size() << std::endl;
    
//    std::cin.get();
    
    FamilySearch::GEDCOM::Record rec = *ged->getRecords()[0];
    std::cout << "Record: " << std::endl << rec << std::endl;
    mongo::BSONObj rec_low = BSON( "record" << rec );
    std::cout << "JSON: " << rec_low.jsonString() << std::endl;
    FamilySearch::GEDCOM::Record unrec(rec_low["record"]);
    std::cout << "Record From BSON: " << std::endl;
    std::cout << unrec << std::endl;

  return 0;
}

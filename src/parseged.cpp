/**
 * parseged.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

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

	return 0;
}

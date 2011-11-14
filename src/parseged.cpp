/**
 * parseged.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include <boost/program_options.hpp>

/**
 * Tool to parse through an unlinked GEDCOM file and put the data into a Mongo Database.
 *
 * ex.
 *
 *   ./parseged if=MYGEDCOM.GED db=scots col=records_low
 *
 * - *if* in-file
 * - *db* the database to use
 * - *col* the collection to use in the database
 * - *ro* `YES`|=`NO` whether to just read the GEDCOM and not try any Mongo-stuff.
 */
int main(int argc, char **argv)
{
	

	return 0;
}

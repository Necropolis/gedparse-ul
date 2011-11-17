/**
 * Gedcom.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
#include <vector>
// boost
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
// familysearch
#include "Record.hpp"

#ifndef __GEDCOM_HPP_
#define __GEDCOM_HPP_

namespace FamilySearch { namespace GEDCOM {

/**
 * Class representing an unlinked GEDCOM. Unlinked GEDCOMs are right little buggers to parse.
 * They look something like this:
 *
 * \r\n0 FAM
 * \r\n1 SEX F
 * \r\n1 SPOU George /BRUCE
 * \r\n1 MARR
 * \r\n2 PLAC Fife, Scotland, Fife, Kingsbarns
 * \r\n1 MISC FR582
 * \r\n1 BATC M114414
 * \r\n0 FAM
 * ...
 *
 * Defining characteristics are:
 *
 * 1. Every GEDCOM starts with a CR/LF
 */  
class Gedcom {
private:
  boost::scoped_ptr<std::vector<boost::shared_ptr<Record> > > records;
  
public:
  Gedcom();
  /** parse from a stream */
  friend std::istream& operator>> (std::istream &is, Gedcom &ged);
  
  std::vector<boost::shared_ptr<Record> >& getRecords();
};

std::istream& operator>> (std::istream &is, Gedcom &ged);
  
} }


#endif

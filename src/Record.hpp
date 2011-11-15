/**
 * Record.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <string>
// boost
#include <boost/scoped_ptr.hpp>
// familysearch
#include "RecordType.hpp"
#include "Name.hpp"
#include "Gender.hpp"

#ifndef __RECORD_HPP_
#define __RECORD_HPP_

namespace FamilySearch { namespace GEDCOM {

/**
 * Class representing a single record from an unlinked GEDCOM.
 *
 * Defining characteristics are:
 *
 * 1. Every record begings with CR/LF0
 * 2. Every record is of type FAM or INDI
 */  
class Record {
private:
  boost::scoped_ptr<std::string> type;
  boost::scoped_ptr<Name> name;
  boost::scoped_ptr<Gender> gender;
  
public:
  
  friend std::istream& operator>> (std::istream&, Record&);
  
  std::string getType();
  void setType(std::string&);
  Name& getName();
  void setName(Name&);
  Gender& getGender();
  void setGender(Gender&);
  
};

std::istream& operator>> (std::istream&, Record&);
  
} }

#endif

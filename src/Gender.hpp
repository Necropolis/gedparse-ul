/**
 * Gender.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// boost
#include <boost/scoped_ptr.hpp>

#ifndef __GENDER_HPP_
#define __GENDER_HPP_

namespace FamilySearch { namespace GEDCOM {
  
class Gender {
private:
  boost::scoped_ptr<std::string> gender;
public:
    Gender();
    Gender(std::string&);
  
    friend std::istream& operator>> (std::istream&, Gender&);
  
    std::string& getGender();
    void setGender(std::string&);
};
  
std::istream& operator>> (std::istream&, Gender&);
  
}}

#endif
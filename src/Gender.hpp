/**
 * Gender.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// familysearch
#include "Attribute.hpp"

#ifndef __GENDER_HPP_
#define __GENDER_HPP_

namespace FamilySearch { namespace GEDCOM {
  
    class Gender : public Attribute {
    private:
        std::string gender;
        
    public:
        Gender();
      
        friend std::ostream& operator<< (std::ostream&, Gender&);
        friend std::istream& operator>> (std::istream&, Gender&);
      
        std::string& getGender();
        void setGender(std::string);
    };
  
    /* outputs line ending, eg "SEX F\r\n" */
    std::ostream& operator<< (std::ostream&, Gender&);
    std::istream& operator>> (std::istream&, Gender&);
  
}}

#endif
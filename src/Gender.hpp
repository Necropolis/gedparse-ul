/**
 * Gender.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>

#ifndef __GENDER_HPP_
#define __GENDER_HPP_

namespace FamilySearch { namespace GEDCOM {
  
    class Gender {
    private:
        std::string gender;
        bool _isSet;
        
    public:
        Gender();
      
        friend std::ostream& operator<< (std::ostream&, Gender&);
        friend std::istream& operator>> (std::istream&, Gender&);
      
        std::string& getGender();
        void setGender(std::string);
        bool isSet();
    };
  
    /* outputs line ending, eg "SEX F\r\n" */
    std::ostream& operator<< (std::ostream&, Gender&);
    std::istream& operator>> (std::istream&, Gender&);
  
}}

#endif
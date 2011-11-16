/**
 * Gender.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Gender.hpp"

namespace FamilySearch { namespace GEDCOM {

    Gender::Gender() :gender(""), _isSet(false) {}
    
    std::string& Gender::getGender() { return this->gender; }
    void Gender::setGender(std::string gender) { this->gender = gender; _isSet = true; }
    bool Gender::isSet() { return _isSet; }

    std::ostream& operator<< (std::ostream& os, Gender& gender) {
        os << "SEX " << gender.gender << "\r\n";
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Gender& gender) {
        std::string str;
        is >> str;
        gender.setGender(str);
        return is;
    }
  
}}

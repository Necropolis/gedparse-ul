/**
 * Gender.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Gender.hpp"

namespace FamilySearch { namespace GEDCOM {

    Gender::Gender() { }
    Gender::Gender(std::string& gender) :gender(&gender) { }

    std::string& Gender::getGender() {
      return *(this->gender);
    }

    void Gender::setGender(std::string& gender) {
      this->gender.reset(&gender);
    }

    std::istream& operator>> (std::istream& is, Gender& gender) {
        std::string str;
        is >> str;
        gender.setGender(str);
        return is;
    }
  
}}

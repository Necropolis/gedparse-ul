/**
 * StandardisedName.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "StandardisedName.hpp"

namespace FamilySearch { namespace GEDCOM {
  
    StandardisedName::StandardisedName(): standardisedName(""), givenName(true), Attribute() {}
    
    std::string& StandardisedName::getStandardisedName() { return standardisedName; }
    void StandardisedName::setStandardisedName(std::string standardisedName) { this->standardisedName = standardisedName; set(true); }
    bool StandardisedName::isGivenName() { return givenName; }
    void StandardisedName::setGivenName(bool givenName) { this->givenName = givenName; set(true); }
    
    std::ostream& operator<< (std::ostream& os, StandardisedName& standardised_name) {
        if (standardised_name.givenName) os << "STGN "; else os << "STSN ";
        os << standardised_name.standardisedName << "\r\n";
        return os;
    }
    
    std::istream& operator>> (std::istream& is, StandardisedName& standardised_name) {
        
        
        return is;
    }
  
}}
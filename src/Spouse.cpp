/**
 * Spouse.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Spouse.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Name& Spouse::getName() {
        return this->name;
    }
    void Spouse::setName(Name name) {
        this->name = name;
    }
    
    std::ostream& operator<< (std::ostream& os, Spouse& spouse) {
        os << "1 SPOU " << spouse.name << "\r\n";
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Spouse& spouse) {
        // stream is now a NAME part
        is >> spouse.name;
        
        return is;
    }
    
} }

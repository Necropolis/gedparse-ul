/**
 * Spouse.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Spouse.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Name& Spouse::getName() {
        return *(this->name);
    }
    void Spouse::setName(Name& name) {
        this->name.reset(&name);
    }
    
    std::ostream& operator<< (std::ostream& os, Spouse& spouse) {
        os << " Spouse: " << std::endl;
        os << "  Name: " << spouse.name << std::endl;
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Spouse& spouse) {
        // stream is now a NAME part
        spouse.name.reset(new Name());
        is >> *spouse.name;
        
        return is;
    }
    
} }

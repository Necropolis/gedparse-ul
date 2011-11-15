/**
 * Marriage.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Marriage.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    std::ostream& operator<< (std::ostream& os, Marriage& marr) {
        
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Marriage& marr) {
        
        return is;
    }
    
} }

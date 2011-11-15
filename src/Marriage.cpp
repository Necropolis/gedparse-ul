/**
 * Marriage.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Marriage.hpp"

namespace FamilySearch { namespace GEDCOM {

    Place& Marriage::getPlace() {
        return *this->place;
    }
    
    void Marriage::setPlace(Place& place) {
        this->place.reset(&place);
    }
    
    std::ostream& operator<< (std::ostream& os, Marriage& marr) {
        
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Marriage& marr) {
        
        while (is.good()) {
            std::string line_level;
            is >> line_level;
            
            if (line_level=="1") {
                is.seekg(-2, std::ios_base::cur);
                return is; // end of marriage stuff
            } else if (line_level=="2") {
                std::string line_type;
                is >> line_type;
                
                if (line_type=="PLAC") {
                    Place *p = new Place();
                    is >> *p;
                    marr.setPlace(*p);
                } else {
                    std::cerr << "Unknown line type of " << line_type << std::endl;
                }
            }
            
            
        }
        
        return is;
    }
    
} }

/**
 * Marriage.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Marriage.hpp"

namespace FamilySearch { namespace GEDCOM {

    Place& Marriage::getPlace() { return this->place; }
    void Marriage::setPlace(Place place) { this->place = place; }
    Date& Marriage::getDate() { return date; }
    void Marriage::setDate(Date date) { this->date = date; }
    
    std::ostream& operator<< (std::ostream& os, Marriage& marr) {
        
        os << "1 MARR\r\n";
        if (marr.place.isSet()) os << "2 " << marr.place;
        if (marr.date.isSet()) os << "2 " << marr.date;
        
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Marriage& marr) {
        
        while (is.good()) {
            while (is.peek()<'0'||is.peek()>'9') {is.get();} // precondition: at line start
            std::string line_level;
            is >> line_level;
            
            if (line_level=="1") {
                is.seekg(-2, std::ios_base::cur);
                return is; // end of marriage stuff
            } else if (line_level=="2") {
                std::string line_type;
                is >> line_type;
                
                if (line_type=="PLAC") {
                    Place p;
                    is >> p;
                    marr.setPlace(p);
                } else if (line_type=="DATE") {
                    Date d;
                    is >> d;
                    marr.setDate(d);
                } else {
                    std::cerr << "Unknown line type of " << line_type << std::endl;
                }
            }
            
            
        }
        
        return is;
    }
    
} }

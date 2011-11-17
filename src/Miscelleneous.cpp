/**
 * Miscelleneous.cpp - 16 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Miscelleneous.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Miscelleneous::Miscelleneous(): note(""), Attribute() {}

    std::string& Miscelleneous::getNote() { return this->note; }
    void Miscelleneous::setNote(std::string note) { this->note = note; }
    
    std::ostream& operator<< (std::ostream& os, Miscelleneous& misc) {
        os << "MISC " << misc.note << "\r\n";
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Miscelleneous& misc) {
        std::string str;
        while (is.peek()!='\r') {
            is >> str;
            misc.note.append(str);
            misc.note.append(" ");
        }
        
        misc.set(true);
        
        return is;
    }

} }

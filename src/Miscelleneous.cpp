/**
 * Miscelleneous.cpp - 16 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Miscelleneous.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Miscelleneous::Miscelleneous(): note(""), Attribute() {}
    Miscelleneous::Miscelleneous(BSONElement elem): note(elem["note"].String()), Attribute(elem["attribute"]) { }
    Miscelleneous::Miscelleneous(BSONObj obj): note(obj["note"].String()), Attribute(obj["attribute"]) { }

    string& Miscelleneous::getNote() { return this->note; }
    void Miscelleneous::setNote(string note) { this->note = note; }
    
    ostream& operator<< (ostream& os, Miscelleneous& misc) {
        os << "MISC " << misc.note << "\r\n";
        return os;
    }
    
    istream& operator>> (istream& is, Miscelleneous& misc) {
        string str;
        while (is.peek()!='\r') {
            is >> str;
            misc.note.append(str);
            misc.note.append(" ");
        }
        
        misc.set(true);
        
        return is;
    }
    
    BSONObj Miscelleneous::asBSON() {
        BSONObjBuilder b;
        b   << "note"       << note
            << "attribute"  << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Miscelleneous& misc) {
        return bv << misc.asBSON();
    }

} }

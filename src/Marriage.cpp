/**
 * Marriage.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Marriage.hpp"

namespace FamilySearch { namespace GEDCOM {

    Marriage::Marriage() {}
    Marriage::Marriage(BSONElement elem): place(elem["place"]), date(elem["date"]), Attribute(elem["attribute"]) { }
    Marriage::Marriage(BSONObj obj): place(obj["place"]), date(obj["date"]), Attribute(obj["attribute"]) { }
    
    Place& Marriage::getPlace() { return this->place; }
    void Marriage::setPlace(Place place) { this->place = place; set(true); }
    Date& Marriage::getDate() { return date; }
    void Marriage::setDate(Date date) { this->date = date; set(true); }
    
    ostream& operator<< (ostream& os, Marriage& marr) {
        
        os << "1 MARR\r\n";
        if (marr.date.isSet()) os << "2 " << marr.date;
        if (marr.place.isSet()) os << "2 " << marr.place;
        
        return os;
    }
    
    istream& operator>> (istream& is, Marriage& marr) {
        
        while (is.good()) {
            while (is.peek()<'0'||is.peek()>'9') {is.get();} // precondition: at line start
            string line_level;
            is >> line_level;
            
            if (line_level=="1") {
                is.seekg(-2, ios_base::cur);
                return is; // end of marriage stuff
            } else if (line_level=="2") {
                string line_type;
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
                    cerr << "Unknown line type of " << line_type << endl;
                }
            }
            
            
        }
        
        return is;
    }
    
    BSONObj Marriage::asBSON() {
        BSONObjBuilder b;
        b   << "place"      << place
            << "date"       << date
            << "attribute"  << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Marriage& marr) {
        return bv << marr.asBSON();
    }
    
    void Marriage::emitFieldHeaders(CSVOStream& csv) {
        Place().emitFieldHeaders(csv);
        Date().emitFieldHeaders(csv);
    }
    
    void Marriage::emitData(CSVOStream& csv) {
        place.emitData(csv);
        date.emitData(csv);
    }
    
} }

/**
 * Marriage.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Marriage.hpp"

namespace FamilySearch { namespace GEDCOM {

    Marriage::Marriage() {}
    Marriage::Marriage(BSONElement elem): place(elem["place"]), date(elem["date"]) { }
    Marriage::Marriage(BSONObj obj): place(obj["place"]), date(obj["date"]) { }
    
    Place& Marriage::getPlace() { return this->place; }
    void Marriage::setPlace(Place place) { this->place = place; }
    Date& Marriage::getDate() { return date; }
    void Marriage::setDate(Date date) { this->date = date; }
    
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
        b   << "place"  << place
            << "date"   << date;
        return b.obj();
    }
    
    BSONArrayBuilder& operator<< (BSONArrayBuilder& a, list<Marriage>& marriages) {
        for (list<Marriage>::iterator it = marriages.begin();
             it != marriages.end();
             ++it)
            a << *it;
        return a;
    }
    
    BSONArrayBuilder& operator<< (BSONArrayBuilder& a, Marriage& marr) {
        return a << marr.asBSON();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Marriage& marr) {
        return bv << marr.asBSON();
    }
    
} }

/**
 * Event.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Event.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
   
    Event::Event(): type(""), date(Date()), place(Place()), Attribute() {}
    Event::Event(BSONElement elem): type(elem["type"].String()), date(elem["date"]), place(elem["place"]), Attribute(elem["attribute"]) { }
    Event::Event(BSONObj obj): type(obj["type"].String()), date(obj["date"]), place(obj["place"]), Attribute(obj["attribute"]) { }
    
    std::string& Event::getType() { return type; }
    void Event::setType(std::string type) { this->type = type; set(true); }
    Date& Event::getDate() { return date; }
    void Event::setDate(Date date) { this->date = date; set(true); }
    Place& Event::getPlace() { return place; }
    void Event::setPlace(Place place) { this->place = place; set(true); }
    
    std::ostream& operator<< (std::ostream& os, Event& event) {
        os << "1 EVEN " << event.type << "\r\n";
        if (event.date.isSet()) os << "2 " << event.date;
        if (event.place.isSet()) os << "2 " << event.place;
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Event& event) {
        is >> event.type;
        while (is.good()) {
            while (is.peek()<'0'||is.peek()>'9') {is.get();} // precondition: at line start
            char c = is.get();
            if (c=='0') {
                is.unget();
                break;
            } else if (c=='1') {
                is.unget();
                break;
            } else if (c=='2') {
                std::string line_type;
                is >> line_type;
                
                if (line_type=="DATE") {
                    is >> event.date;
                } else if (line_type=="PLAC") {
                    is >> event.place;
                } else {
                    std::cout << "Unknown line type \"" << line_type << "\"" << std::endl;
                    inspect_stream(is);
                    throw new std::exception();
                }
            } else {
                std::cout << "Unknown escalation type!" << std::endl;
                inspect_stream(is);
                throw new std::exception();
            }
        }
        
        return is;
    }
    
    BSONObj Event::asBSON() {
        BSONObjBuilder b;
        b   << "type"       << type
            << "date"       << date
            << "place"      << place
            << "attribute"  << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Event& event) {
        return bv << event.asBSON();
    }
    
} }
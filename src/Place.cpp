/**
 * Place.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Place.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {

    Place::Place(): countyCode(""), country(""), county(""), town(""), borough(""), Attribute() {}
    Place::Place(BSONElement elem): countyCode(elem["countyCode"].String()), country(elem["country"].String()), county(elem["county"].String()), town(elem["town"].String()), borough(elem["borough"].String()), Attribute(elem["attribute"]) { }
    Place::Place(BSONObj obj): countyCode(obj["countyCode"].String()), country(obj["country"].String()), county(obj["county"].String()), town(obj["town"].String()), borough(obj["borough"].String()), Attribute(obj["attribute"]) { }
    
    string& Place::getCountyCode() { return countyCode; }
    void Place::setCountyCode(string countyCode) { this->countyCode = countyCode; set(true); }
    string& Place::getCountry() { return country; }
    void Place::setCountry(string country) { this->country = country; set(true); }
    string& Place::getCounty() { return county; }
    void Place::setCounty(string county) { this->county = county; set(true); }
    string& Place::getTown() { return town; }
    void Place::setTown(string town) { this->town = town; set(true); }
    string& Place::getBorough() { return borough; }
    void Place::setBorough(string borough) { this->borough = borough; set(true); }
    
    ostream& operator<< (ostream& os, Place& place) {
        
        os << "PLAC " << place.countyCode << ", " << place.country << ", " << place.county << ", ";
        if (place.borough!="")
            os << place.borough << ", ";
        os << place.town << "\r\n";
        
        return os;
    }
    
    /**
     * Comes in two forms:
     *
     *           countyCode      county
     *                 country         town
     *     PLACE Fife, Scotland, Fife, Kingsbarns
     *
     * and
     *
     *           countyCode      county                 town/city
     *                 country               borough
     *     PLACE Mlot, Scotland, Midlothian, Canongate, Edinburgh
     */
    istream& operator>> (istream& is, Place& place) {
        
        char sentinels[] = ",\r";
        size_t sl = 2;
        
        // cc
        place.setCountyCode(trim(read_until_one_of(is, sentinels, sl)));
        
        // country
        place.setCountry(trim(read_until_one_of(is, sentinels, sl)));
        
        // county
        place.setCounty(trim(read_until_one_of(is, sentinels, sl)));

        // borough or town
        string buff = trim(read_until_one_of(is, sentinels, sl));
        if (is.peek()=='\n') {
            place.setTown(buff); // town
        } else {
            place.setBorough(buff); // borough
            place.setTown(trim(read_until_one_of(is, sentinels, sl))); // town
        }
        
        return is;
    }
    
    BSONObj Place::asBSON() {
        BSONObjBuilder b;
        b   << "countyCode" << countyCode
            << "country"    << country
            << "county"     << county
            << "town"       << town
            << "borough"    << borough
            << "attribute"  << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Place& place) {
        return bv << place.asBSON();
    }
    
    void Place::emitFieldHeaders(CSVOStream& csv) {
        csv << "countyCode"
            << "country"
            << "county"
            << "town"
            << "borough";
    }
    
    void Place::emitData(CSVOStream& csv) {
        csv << countyCode
            << country
            << county
            << town
            << borough;
    }
    
} }

/**
 * Place.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Place.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {

    Place::Place(): countyCode(""), country(""), county(""), town(""), borough(""), Attribute() {}
    
    std::string& Place::getCountyCode() { return countyCode; }
    void Place::setCountyCode(std::string countyCode) { this->countyCode = countyCode; set(true); }
    std::string& Place::getCountry() { return country; }
    void Place::setCountry(std::string country) { this->country = country; set(true); }
    std::string& Place::getCounty() { return county; }
    void Place::setCounty(std::string county) { this->county = county; set(true); }
    std::string& Place::getTown() { return town; }
    void Place::setTown(std::string town) { this->town = town; set(true); }
    std::string& Place::getBorough() { return borough; }
    void Place::setBorough(std::string borough) { this->borough = borough; set(true); }
    
    std::ostream& operator<< (std::ostream& os, Place& place) {
        
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
    std::istream& operator>> (std::istream& is, Place& place) {
        
        char sentinels[] = ",\r";
        size_t sl = 2;
        
        // cc
        place.setCountyCode(trim(read_until_one_of(is, sentinels, sl)));
        
        // country
        place.setCountry(trim(read_until_one_of(is, sentinels, sl)));
        
        // county
        place.setCounty(trim(read_until_one_of(is, sentinels, sl)));

        // borough or town
        std::string buff = trim(read_until_one_of(is, sentinels, sl));
        if (is.peek()=='\n') {
            place.setTown(buff); // town
        } else {
            place.setBorough(buff); // borough
            place.setTown(trim(read_until_one_of(is, sentinels, sl))); // town
        }
        
        return is;
    }
    
} }

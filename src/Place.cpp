/**
 * Place.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Place.hpp"

namespace FamilySearch { namespace GEDCOM {

    std::string& Place::getCountyCode() {
        return *countyCode;
    }
    
    void Place::setCountyCode(std::string& countyCode) {
        this->countyCode.reset(&countyCode);
    }
    
    std::string& Place::getCountry() {
        return *country;
    }
    
    void Place::setCountry(std::string& country) {
        this->country.reset(&country);
    }
    
    std::string& Place::getCounty() {
        return *county;
    }
    
    void Place::setCounty(std::string& county) {
        this->county.reset(&county);
    }
    
    std::string& Place::getTown() {
        return *town;
    }
    
    void Place::setTown(std::string& town) {
        this->town.reset(&town);
    }
    
    std::string& Place::getBorough() {
        return *borough;
    }
    
    void Place::setBorough(std::string& borough) {
        this->borough.reset(&borough);
    }
    
    std::ostream& operator<< (std::ostream& os, Place& place) {
        
        if (place.borough.get()!=NULL&&place.getBorough()=="") {
            os << *place.borough << ", ";
        }
        
        os << *place.town << ", " << *place.county << ", " << *place.country << " [CC:" << *place.countyCode << "]";
        
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
        
        std::string *buff;
        
        // cc
        buff = new std::string();
        getline(is, *buff, ',');
        if (buff->at(0)==' ') buff->erase(0,1);
        place.setCountyCode(*buff);
        
        buff = new std::string();
        getline(is, *buff, ',');
        if (buff->at(0)==' ') buff->erase(0,1);
        place.setCountry(*buff);
        
        buff = new std::string();
        getline(is, *buff, ',');
        if (buff->at(0)==' ') buff->erase(0,1);
        place.setCounty(*buff);
        
        buff = new std::string();
        getline(is, *buff, ',');
        if (buff->at(0)==' ') buff->erase(0,1);
        place.setTown(*buff);
        
        if (is.peek()!='\r') {
            place.setBorough(place.getTown());
            buff = new std::string();
            getline(is, *buff, ',');
            if (buff->at(0)==' ') buff->erase(0,1);
            place.setTown(*buff);
        }
        
        std::cout << place << std::endl;
        
        return is;
    }
    
} }

/**
 * Place.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// familysearch
#include "Attribute.hpp"

#ifndef __PLACE_HPP_
#define __PLACE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
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
    class Place : public Attribute {
    private:
        std::string countyCode;
        std::string country;
        std::string county;
        std::string town;
        std::string borough;
        
    public:
        Place();
        
        friend std::ostream& operator<< (std::ostream&, Place&);
        friend std::istream& operator>> (std::istream&, Place&);
    
        std::string& getCountyCode();
        void setCountyCode(std::string);
        std::string& getCountry();
        void setCountry(std::string);
        std::string& getCounty();
        void setCounty(std::string);
        std::string& getTown();
        void setTown(std::string);
        std::string& getBorough();
        void setBorough(std::string);
    };
    
    /* outputs header and newlines, eg "PLACE Fife, Scotland, Fife, Kingsbarns\r\n" */
    std::ostream& operator<< (std::ostream&, Place&);
    std::istream& operator>> (std::istream&, Place&);
    
} }

#endif

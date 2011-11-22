/**
 * Place.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"
// fsdev
#include "CSVOStream.hpp"

#ifndef __PLACE_HPP_
#define __PLACE_HPP_

using namespace std;
using namespace mongo;
using namespace fsdev;

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
    class Place : public Attribute, public CSVRecord {
    private:
        string countyCode;
        string country;
        string county;
        string town;
        string borough;
        
    public:
        Place();
        Place(BSONElement);
        Place(BSONObj);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Place&);
        friend istream& operator>> (istream&, Place&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Place&);
        
        // csv serialisation
        void emitFieldHeaders(CSVOStream&);
        void emitData(CSVOStream&);
    
        string& getCountyCode();
        void setCountyCode(string);
        string& getCountry();
        void setCountry(string);
        string& getCounty();
        void setCounty(string);
        string& getTown();
        void setTown(string);
        string& getBorough();
        void setBorough(string);
    };
    
    /* outputs header and newlines, eg "PLACE Fife, Scotland, Fife, Kingsbarns\r\n" */
    ostream& operator<< (ostream&, Place&);
    istream& operator>> (istream&, Place&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Place&);
    
} }

#endif

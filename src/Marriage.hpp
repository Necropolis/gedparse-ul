/**
 * Marriage.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
// mongo
#include "bson/bson.h"
// familysearch
#include "Place.hpp"
#include "Date.hpp"
// fsdev
#include "CSVOStream.hpp"

#ifndef __MARRIAGE_HPP_
#define __MARRIAGE_HPP_

using namespace std;
using namespace mongo;
using namespace fsdev;

namespace FamilySearch { namespace GEDCOM {
    
    class Marriage : public Attribute, public CSVRecord {
    private:
        Place place;
        Date date;
    public:
        Marriage();
        Marriage(BSONElement);
        Marriage(BSONObj);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Marriage&);
        friend istream& operator>> (istream&, Marriage&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONArrayBuilder& operator<< (BSONArrayBuilder&, Marriage&);
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Marriage&);
        
        // csv serialisation
        void emitFieldHeaders(CSVOStream&);
        void emitData(CSVOStream&);
        
        Place& getPlace();
        void setPlace(Place);
        Date& getDate();
        void setDate(Date);
    };
    
    ostream& operator<< (ostream&, Marriage&);
    istream& operator>> (istream&, Marriage&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Marriage&);
    
} }

#endif

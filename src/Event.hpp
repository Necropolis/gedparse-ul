/**
 * Event.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
#include <list>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"
#include "Date.hpp"
#include "Place.hpp"

#ifndef __EVENT_HPP_
#define __EVENT_HPP_

using namespace std;
using namespace mongo;

namespace FamilySearch { namespace GEDCOM {
    
    class Event : public Attribute {
    private:
        string type;
        Date date;
        Place place;
        
    public:
        Event();
        Event(BSONElement);
        Event(BSONObj);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Event&);
        friend istream& operator>> (istream&, Event&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONArrayBuilder& operator<< (BSONArrayBuilder&, Event&);
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Event&);
        
        string& getType();
        void setType(string);
        Date& getDate();
        void setDate(Date);
        Place& getPlace();
        void setPlace(Place);
    };
    
    ostream& operator<< (ostream&, Event&);
    istream& operator>> (istream&, Event&);
    
    BSONArrayBuilder& operator<< (BSONArrayBuilder&, list<Event>&);
    BSONArrayBuilder& operator<< (BSONArrayBuilder&, Event&);
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Event&);
    
} }

#endif

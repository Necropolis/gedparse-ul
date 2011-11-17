/**
 * Event.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// familysearch
#include "Attribute.hpp"
#include "Date.hpp"
#include "Place.hpp"

#ifndef __EVENT_HPP_
#define __EVENT_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    class Event : public Attribute {
    private:
        std::string type;
        Date date;
        Place place;
        
    public:
        Event();
        
        friend std::ostream& operator<< (std::ostream&, Event&);
        friend std::istream& operator>> (std::istream&, Event&);
        
        std::string& getType();
        void setType(std::string);
        Date& getDate();
        void setDate(Date);
        Place& getPlace();
        void setPlace(Place);
    };
    
    std::ostream& operator<< (std::ostream&, Event&);
    std::istream& operator>> (std::istream&, Event&);
    
} }

#endif

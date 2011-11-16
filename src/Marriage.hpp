/**
 * Marriage.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
// familysearch
#include "Place.hpp"
#include "Date.hpp"

#ifndef __MARRIAGE_HPP_
#define __MARRIAGE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    class Marriage {
    private:
        Place place;
        Date date;
    public:
        
        
        friend std::ostream& operator<< (std::ostream&, Marriage&);
        friend std::istream& operator>> (std::istream&, Marriage&);
        
        Place& getPlace();
        void setPlace(Place);
        Date& getDate();
        void setDate(Date);
    };
    
    std::ostream& operator<< (std::ostream&, Marriage&);
    std::istream& operator>> (std::istream&, Marriage&);
    
} }

#endif

/**
 * Date.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// familysearch
#include "Attribute.hpp"

#ifndef __DATE_HPP_
#define __DATE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    class Date : public Attribute {
    private:
        std::string day;
        std::string month;
        std::string year;
        
    public:
        Date();
        
        std::string& getDay();
        void setDay(std::string);
        std::string& getMonth();
        void setMonth(std::string);
        std::string& getYear();
        void setYear(std::string);
        
        friend std::ostream& operator<< (std::ostream&, Date&);
        friend std::istream& operator>> (std::istream&, Date&);
        
    };
    
} }

#endif

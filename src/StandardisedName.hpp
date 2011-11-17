/**
 * StandardisedName.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */
 
// stl
#include <iostream>
#include <string>
// familysearch
#include "Attribute.hpp"

#ifndef __STANDARDISED_NAME_HPP_
#define __STANDARDISED_NAME_HPP_

namespace FamilySearch { namespace GEDCOM {
  
    class StandardisedName : Attribute {
    private:
        std::string standardisedName;
        bool givenName; // if yes then given name, else surname
        
    public:
        StandardisedName();
        
        std::string& getStandardisedName();
        void setStandardisedName(std::string);
        bool isGivenName();
        void setGivenName(bool);
        
        friend std::ostream& operator<< (std::ostream&, StandardisedName&);
        friend std::istream& operator>> (std::istream&, StandardisedName&);
    };
    
    /* designed to output the tag (STGN or STSN) then the name and newline;
     * the level number must be provided by the caller because this
     * attribute doesn't know it's own level */
    std::ostream& operator<< (std::ostream&, StandardisedName&);
    std::istream& operator>> (std::istream&, StandardisedName&);
  
} }

#endif

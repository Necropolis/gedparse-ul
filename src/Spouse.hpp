/**
 * Spouse.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
// familysearch
#include "Attribute.hpp"
#include "Name.hpp"
#include "StandardisedName.hpp"

#ifndef __SPOUSE_HPP_
#define __SPOUSE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    /**
     * Spouse usually looks like this:
     * 1 SPOU Given Name /SURNAME
     * 2 STSN Sth
     * 2 STGN Giv'en Name
     */
    class Spouse : public Attribute {
    private:
        Name name;        
        std::list<StandardisedName> standardisedNames;
        
    public:
        Spouse();
        
        Name& getName();
        void setName(Name);
        std::list<StandardisedName>& getStandardisedNames();
        
        friend std::ostream& operator<< (std::ostream&, Spouse&);
        friend std::istream& operator>> (std::istream&, Spouse&);
    };
    
    std::ostream& operator<< (std::ostream&, Spouse&);
    std::istream& operator>> (std::istream&, Spouse&);
    
} }

#endif

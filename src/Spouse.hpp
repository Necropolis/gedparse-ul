/**
 * Spouse.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
// boost
#include <boost/scoped_ptr.hpp>
// familysearch
#include "Name.hpp"

#ifndef __SPOUSE_HPP_
#define __SPOUSE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    /**
     * Spouse usually looks like this:
     * 1 SPOU Given Name /SURNAME
     * 2 STSN Sth
     * 2 STGN Giv'en Name
     */
    class Spouse {
    private:
        Name name;        
        
    public:
        
        Name& getName();
        void setName(Name);
        
        friend std::ostream& operator<< (std::ostream&, Spouse&);
        friend std::istream& operator>> (std::istream&, Spouse&);
    };
    
    std::ostream& operator<< (std::ostream&, Spouse&);
    std::istream& operator>> (std::istream&, Spouse&);
    
} }

#endif

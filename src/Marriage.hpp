/**
 * Marriage.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>

#ifndef __MARRIAGE_HPP_
#define __MARRIAGE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    class Marriage {
    private:
        
    public:
        
        friend std::ostream& operator<< (std::ostream&, Marriage&);
        friend std::istream& operator>> (std::istream&, Marriage&);
        
    };
    
    std::ostream& operator<< (std::ostream&, Marriage&);
    std::istream& operator>> (std::istream&, Marriage&);
    
} }

#endif

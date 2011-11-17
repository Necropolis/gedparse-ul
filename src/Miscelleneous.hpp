/**
 * Miscelleneous.hpp - 16 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// familysearch
#include "Attribute.hpp"

#ifndef __MISCELLENEOUS_HPP_
#define __MISCELLENEOUS_HPP_

namespace FamilySearch { namespace GEDCOM {
  
    class Miscelleneous : public Attribute {
    private:
        std::string note;
        
    public:
        Miscelleneous();
        
        std::string& getNote();
        void setNote(std::string);
        
        friend std::ostream& operator<< (std::ostream&, Miscelleneous&);
        friend std::istream& operator>> (std::istream&, Miscelleneous&);
        
    };
    
    std::ostream& operator<< (std::ostream&, Miscelleneous&);
    std::istream& operator>> (std::istream&, Miscelleneous&);
    
} }


#endif

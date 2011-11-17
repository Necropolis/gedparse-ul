/**
 * Name.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
// familysearch
#include "Attribute.hpp"

#ifndef __NAME_HPP_
#define __NAME_HPP_

namespace FamilySearch { namespace GEDCOM {
  
    /**
    * A name record.
    */
    class Name : public Attribute {
    private:
        std::list<std::string> givenNames;
        std::string surname;
        
    public:
        Name();
        
        friend std::ostream& operator<< (std::ostream&, Name&);
        friend std::istream& operator>> (std::istream&, Name&);
        
        std::list<std::string>& getGivenNames();
        std::string& getSurname();
        void setSurname(std::string);
    };
    
    /* just a piece; no line begin or newline */
    std::ostream& operator<< (std::ostream&, Name&);
    std::istream& operator>> (std::istream&, Name&);
  
} }

#endif

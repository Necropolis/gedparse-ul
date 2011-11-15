/**
 * Name.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
// boost
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#ifndef __NAME_HPP_
#define __NAME_HPP_

namespace FamilySearch { namespace GEDCOM {
  
    /**
    * A name record.
    */
    class Name {
    private:
        boost::scoped_ptr<std::list<boost::shared_ptr<std::string> > > givenNames;
        boost::scoped_ptr<std::string> surname;
        
    public:
        Name();
        
        friend std::ostream& operator<< (std::ostream&, Name&);
        friend std::istream& operator>> (std::istream&, Name&);
        
        std::list<boost::shared_ptr<std::string> >& getGivenNames();
        std::string& getSurname();
        void setSurname(std::string&);
    };
    
    std::ostream& operator<< (std::ostream&, Name&);
    std::istream& operator>> (std::istream&, Name&);
  
} }

#endif

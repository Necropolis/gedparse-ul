/**
 * Spouse.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"
#include "Name.hpp"
#include "StandardisedName.hpp"

#ifndef __SPOUSE_HPP_
#define __SPOUSE_HPP_

using namespace std;
using namespace mongo;

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
        list<StandardisedName> standardisedNames;
        
    public:
        Spouse();
        Spouse(BSONElement);
        Spouse(BSONObj);
        
        Name& getName();
        void setName(Name);
        list<StandardisedName>& getStandardisedNames();
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Spouse&);
        friend istream& operator>> (istream&, Spouse&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONArrayBuilder& operator<< (BSONArrayBuilder&, Spouse&);
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Spouse&);
    };
    
    ostream& operator<< (ostream&, Spouse&);
    istream& operator>> (istream&, Spouse&);
    
    BSONArrayBuilder& operator<< (BSONArrayBuilder&, list<Spouse>&);
    BSONArrayBuilder& operator<< (BSONArrayBuilder&, Spouse&);
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, list<Spouse>&);
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Spouse&);
    
} }

#endif

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
// fsdev
#include "CSVOStream.hpp"

#ifndef __SPOUSE_HPP_
#define __SPOUSE_HPP_

using namespace std;
using namespace mongo;
using namespace fsdev;

namespace FamilySearch { namespace GEDCOM {
    
    /**
     * Spouse usually looks like this:
     * 1 SPOU Given Name /SURNAME
     * 2 STSN Sth
     * 2 STGN Giv'en Name
     */
    class Spouse : public Attribute, public CSVRecord {
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
        
        // csv serialisation
        void emitFieldHeaders(CSVOStream&);
        void emitData(CSVOStream&);
    };
    
    ostream& operator<< (ostream&, Spouse&);
    istream& operator>> (istream&, Spouse&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Spouse&);
    
} }

#endif

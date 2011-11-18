/**
 * StandardisedName.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */
 
// stl
#include <iostream>
#include <string>
#include <list>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"

#ifndef __STANDARDISED_NAME_HPP_
#define __STANDARDISED_NAME_HPP_

using namespace std;
using namespace mongo;

namespace FamilySearch { namespace GEDCOM {
  
    class StandardisedName : Attribute {
    private:
        string standardisedName;
        bool givenName; // if yes then given name, else surname
        
    public:
        StandardisedName();
        StandardisedName(BSONObj);
        StandardisedName(BSONElement);
        
        string& getStandardisedName();
        void setStandardisedName(string);
        bool isGivenName();
        void setGivenName(bool);
            
        // gedcom serialisation
        friend ostream& operator<< (ostream&, StandardisedName&);
        friend istream& operator>> (istream&, StandardisedName&);
        
        // bson serialisation
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, StandardisedName&);
        friend BSONArrayBuilder& operator<< (BSONArrayBuilder&, StandardisedName&);
        friend BSONObj& operator>> (BSONObj&, StandardisedName&);
    };
    
    /* designed to output the tag (STGN or STSN) then the name and newline;
     * the level number must be provided by the caller because this
     * attribute doesn't know it's own level */
    ostream& operator<< (ostream&, StandardisedName&);
    istream& operator>> (istream&, StandardisedName&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, StandardisedName&);
    BSONArrayBuilder& operator<< (BSONArrayBuilder&, list<StandardisedName>&);
    BSONArrayBuilder& operator<< (BSONArrayBuilder&, StandardisedName&);
    BSONObj& operator>> (BSONObj&, StandardisedName&);
  
} }

#endif

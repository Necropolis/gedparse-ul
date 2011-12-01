/**
 * Name.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"
#include "StandardisedName.hpp"
// fsdev
#include "CSVOStream.hpp"

#ifndef __NAME_HPP_
#define __NAME_HPP_

using namespace std;
using namespace mongo;
using namespace fsdev;

namespace FamilySearch { namespace GEDCOM {
  
    /**
    * A name record.
    */
    class Name : public Attribute, public CSVRecord {
    private:
        list<string> givenNames;
        string surname;
        list<StandardisedName> standardisedNames;
        bool standalone;
        
    public:
        Name();
        Name(bool);
        Name(BSONObj);
        Name(BSONElement);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Name&);
        friend istream& operator>> (istream&, Name&);
        
        // bson serialisation
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Name&);
        friend BSONObj& operator>> (BSONObj&, Name&);
        
        // csv serialisation
        void emitFieldHeaders(CSVOStream&);
        void emitData(CSVOStream&);
        
        list<string>& getGivenNames();
        string& getSurname();
        void setSurname(string);
        list<StandardisedName>& getStandardisedNames();
        bool isStandalone();
        void setStandalone(bool);
    };
    
    /* just a piece; no line begin or newline */
    ostream& operator<< (ostream&, Name&);
    istream& operator>> (istream&, Name&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Name&);
    BSONObj& operator>> (BSONObj&, Name&);
  
} }

#endif

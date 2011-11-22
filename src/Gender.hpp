/**
 * Gender.hpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"
// fsdev
#include "CSVOStream.hpp"

#ifndef __GENDER_HPP_
#define __GENDER_HPP_

using namespace std;
using namespace mongo;
using namespace fsdev;

namespace FamilySearch { namespace GEDCOM {
  
    class Gender : public Attribute, public CSVRecord {
    private:
        string gender;
        
    public:
        Gender();
        Gender(BSONElement);
        Gender(BSONObj);
      
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Gender&);
        friend istream& operator>> (istream&, Gender&);
        
        // bson serialisation
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Gender&);
        
        // csv serialisation
        void emitFieldHeaders(CSVOStream&);
        void emitData(CSVOStream&);
      
        string& getGender();
        void setGender(string);
    };
  
    /* outputs line ending, eg "SEX F\r\n" */
    ostream& operator<< (ostream&, Gender&);
    istream& operator>> (istream&, Gender&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Gender&);
  
}}

#endif
/**
 * Date.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"

#ifndef __DATE_HPP_
#define __DATE_HPP_

using namespace std;
using namespace mongo;

namespace FamilySearch { namespace GEDCOM {
    
    class Date : public Attribute {
    private:
        string day;
        string month;
        string year;
        
    public:
        Date();
        Date(BSONElement);
        Date(BSONObj);
        
        string& getDay();
        void setDay(string);
        string& getMonth();
        void setMonth(string);
        string& getYear();
        void setYear(string);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Date&);
        friend istream& operator>> (istream&, Date&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Date&);
        
    };
    
    ostream& operator<< (ostream&, Date&);
    istream& operator>> (istream&, Date&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Date&);
    
} }

#endif

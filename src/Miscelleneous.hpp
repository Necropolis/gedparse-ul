/**
 * Miscelleneous.hpp - 16 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <string>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"

#ifndef __MISCELLENEOUS_HPP_
#define __MISCELLENEOUS_HPP_

using namespace std;
using namespace mongo;

namespace FamilySearch { namespace GEDCOM {
  
    class Miscelleneous : public Attribute {
    private:
        string note;
        
    public:
        Miscelleneous();
        Miscelleneous(BSONElement);
        Miscelleneous(BSONObj);
        
        string& getNote();
        void setNote(string);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Miscelleneous&);
        friend istream& operator>> (istream&, Miscelleneous&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Miscelleneous&);
        
    };
    
    ostream& operator<< (ostream&, Miscelleneous&);
    istream& operator>> (istream&, Miscelleneous&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Miscelleneous&);
    
} }


#endif

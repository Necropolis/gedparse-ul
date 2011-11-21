//
//  Batch.hpp
//  gedparse-ul
//
//  Created by Christopher Miller on 11/16/11.
//  Copyright (c) 2011 FSDEV. All rights reserved.
//

// stl
#include <iostream>
#include <string>
// mongo
#include "bson/bson.h"
// familysearch
#include "Attribute.hpp"

#ifndef __BATCH_HPP_
#define __BATCH_HPP_

using namespace std;
using namespace mongo;

namespace FamilySearch { namespace GEDCOM {
   
    class Batch : public Attribute {
    private:
        string batch;
        
    public:
        Batch();
        Batch(BSONElement);
        Batch(BSONObj);
        
        string& getBatch();
        void setBatch(string);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Batch&);
        friend istream& operator>> (istream&, Batch&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Batch&);
    };
    
    ostream& operator<< (ostream&, Batch&);
    istream& operator>> (istream&, Batch&);
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Batch&);
    
} }

#endif

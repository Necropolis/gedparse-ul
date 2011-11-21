//
//  Batch.cpp
//  gedparse-ul
//
//  Created by Christopher Miller on 11/16/11.
//  Copyright (c) 2011 FSDEV. All rights reserved.
//

#include "Batch.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Batch::Batch(): batch(""), Attribute() {}
    Batch::Batch(BSONElement elem): batch(elem["batch"].String()), Attribute(elem["attribute"]) { }
    Batch::Batch(BSONObj obj): batch(obj["batch"].String()), Attribute(obj["attribute"]) { }
    
    string& Batch::getBatch() { return batch; }
    void Batch::setBatch(string batch) { this->batch = batch; set(true); }
    
    ostream& operator<< (ostream& os, Batch& batch) {
        os << "BATC " << batch.batch << "\r\n";
        return os;
    }
    
    istream& operator>> (istream& is, Batch& batch) {
        is.ignore();
        string st;
        getline(is, st);
        batch.setBatch(st);
        return is;
    }
    
    BSONObj Batch::asBSON() {
        BSONObjBuilder b;
        b   << "batch"      << batch
            << "attribute"  << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Batch& batch) {
        return bv << batch.asBSON();
    }
    
} }
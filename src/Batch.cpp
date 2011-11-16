//
//  Batch.cpp
//  gedparse-ul
//
//  Created by Christopher Miller on 11/16/11.
//  Copyright (c) 2011 FSDEV. All rights reserved.
//

#include "Batch.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Batch::Batch() :batch(""), _isSet(false) {}
    
    std::string& Batch::getBatch() { return batch; }
    void Batch::setBatch(std::string batch) { this->batch = batch; _isSet = true; }
    bool Batch::isSet() { return _isSet; }
    
    std::ostream& operator<< (std::ostream& os, Batch& batch) {
        os << "BATC " << batch.batch << "\r\n";
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Batch& batch) {
        is.ignore();
        std::string st;
        getline(is, st);
        batch.setBatch(st);
        return is;
    }
    
} }
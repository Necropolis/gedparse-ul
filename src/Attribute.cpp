//
//  Attribute.cpp
//  gedparse-ul
//
//  Created by Christopher Miller on 11/17/11.
//  Copyright (c) 2011 FSDEV. All rights reserved.
//

#include "Attribute.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Attribute::Attribute() :_isSet(false) {}
    Attribute::Attribute(BSONElement elem): _isSet(elem["_isSet"].Bool()) { }
    Attribute::Attribute(BSONObj obj): _isSet(obj["_isSet"].Bool()) { }
    
    bool Attribute::isSet() { return _isSet; }
    void Attribute::set(bool _isSet) { this-> _isSet = _isSet; }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Attribute& attr) {
        return bv << BSON( "_isSet" << attr._isSet );
    }
    
} }
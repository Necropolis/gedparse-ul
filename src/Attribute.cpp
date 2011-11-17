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
    
    bool Attribute::isSet() { return _isSet; }
    void Attribute::set(bool _isSet) { this-> _isSet = _isSet; }
    
} }
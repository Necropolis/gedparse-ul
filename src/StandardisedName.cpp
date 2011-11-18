/**
 * StandardisedName.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "StandardisedName.hpp"

namespace FamilySearch { namespace GEDCOM {
  
    StandardisedName::StandardisedName(): standardisedName(""), givenName(true), Attribute() {}
    
    string& StandardisedName::getStandardisedName() { return standardisedName; }
    void StandardisedName::setStandardisedName(string standardisedName) { this->standardisedName = standardisedName; set(true); }
    bool StandardisedName::isGivenName() { return givenName; }
    void StandardisedName::setGivenName(bool givenName) { this->givenName = givenName; set(true); }
    
    ostream& operator<< (ostream& os, StandardisedName& standardised_name) {
        if (standardised_name.givenName) os << "STGN "; else os << "STSN ";
        os << standardised_name.standardisedName << "\r\n";
        return os;
    }
    
    istream& operator>> (istream& is, StandardisedName& standardised_name) {
        while (is.peek()!='\r') {
            string str;
            is >> str;
            standardised_name.standardisedName.append(str);
        }
        
        return is;
    }
    
    BSONObj StandardisedName::asBSON() {
        return BSON("given_name" << givenName << "standardised_name" << standardisedName);
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& stream,
                                StandardisedName& standardised_name) {
        return stream << standardised_name.asBSON();
    }
    
    BSONArrayBuilder& operator<< (BSONArrayBuilder& builder,
                                  StandardisedName& standardised_name) {
        return builder << standardised_name.asBSON();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& builder,
                                list<StandardisedName>& standardised_names) {
        BSONArrayBuilder a;
        list<StandardisedName>::iterator it;
        for (it=standardised_names.begin(); it!=standardised_names.end(); ++it)
            a << *it;
        return builder << a.done();
    }
    
    BSONObj& operator>> (BSONObj& obj,
                         StandardisedName& standardised_name) {
        standardised_name.setGivenName(obj["given_name"].boolean());
        standardised_name.setStandardisedName(obj["standardised_name"].str());
        return obj;
    }
  
}}
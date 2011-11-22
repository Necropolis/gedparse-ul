/**
 * Gender.cpp - 15 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Gender.hpp"

namespace FamilySearch { namespace GEDCOM {

    Gender::Gender(): gender(""), Attribute() {}
    Gender::Gender(BSONElement elem): gender(elem["gender"].String()), Attribute(elem["attribute"]) { }
    Gender::Gender(BSONObj obj): gender(obj["gender"].String()), Attribute(obj["attribute"]) { }
    
    string& Gender::getGender() { return this->gender; }
    void Gender::setGender(string gender) { this->gender = gender; set(true); }

    ostream& operator<< (ostream& os, Gender& gender) {
        os << "SEX " << gender.gender << "\r\n";
        return os;
    }
    
    istream& operator>> (istream& is, Gender& gender) {
        string str;
        is >> str;
        gender.setGender(str);
        return is;
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Gender& gender) {
        return bv << BSON( "gender" << gender.gender << "attribute" << (Attribute&)gender );
    }
    
    void Gender::emitFieldHeaders(CSVOStream& csv) {
        csv << "gender";
    }
    
    void Gender::emitData(CSVOStream& csv) {
        csv << gender;
    }
  
}}

/**
 * Name.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Name.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Name::Name(): surname(""), givenNames(list<string>()), Attribute(), standardisedNames(list<StandardisedName>()), standalone(false) {
        
    }
    
    Name::Name(BSONObj obj): surname(obj["surname"].String()), standalone(obj["standalone"].Bool()), Attribute(obj["attribute"]) {
        // pull given names and standardised names out of lists
        
    }
    
    Name::Name(BSONElement elem): surname(elem["surname"].String()), standalone(elem["standalone"].Bool()), Attribute(elem["attribute"]) {
        // TODO: Write me!
    }
    
    list<string>& Name::getGivenNames() { return givenNames; }
    string& Name::getSurname() { return surname; }
    void Name::setSurname(string surname) { this->surname = surname; set(true); }
    list<StandardisedName>& Name::getStandardisedNames() { return standardisedNames; }
    bool Name::isStandalone() { return standalone; }
    void Name::setStandalone(bool standalone) { this->standalone = standalone; }
    
    ostream& operator<< (ostream& os, Name& name) {
        list<string>::iterator iter;
        for (iter = name.givenNames.begin(); iter != name.givenNames.end(); iter++)
            os << *iter << " ";
        if (name.surname!="") os << "/" << name.surname;
        if (name.standalone) {
            os << "\r\n";
            list<StandardisedName>::iterator it;
            for (it = name.standardisedNames.begin(); it != name.standardisedNames.end(); it++)
                os << "2 " << *it;
        }
        return os;
    }
    
    istream& operator>> (istream& is, Name& name) {
        string str;
        bool surname=false;
        while (is.peek()!='\r') {
            is >> str;
            if (str[0]=='/'||surname) {
                surname=true;
                if (str[0]=='/') str.erase(0,1);
                name.surname.append(str);
                name.surname.append(" ");
            } else {
                name.givenNames.push_back(str);
            }
        }
        if (name.standalone) {
            is.ignore(2, '\n');
            while (is.good()) {
                while (is.peek()<'0'||is.peek()>'9') {is.get();} // precondition: at line start
                char c = is.get();
                if (c=='0') {
                    is.unget();
                    break;
                } else if (c=='1') {
                    is.unget();
                    break;
                } else if (c=='2') {
                    string line_type;
                    is >> line_type;
                    if (line_type=="STGN") {
                        StandardisedName stgn;
                        is >> stgn;
                        stgn.setGivenName(true);
                        name.standardisedNames.push_back(stgn);
                    } else if (line_type=="STSN") {
                        StandardisedName stsn;
                        is >> stsn;
                        stsn.setGivenName(false);
                        name.standardisedNames.push_back(stsn);
                    } else {
                        cout << "Unknown line type \"" << line_type << "\"" << endl;
                        inspect_stream(is);
                        throw new exception();
                    }
                } else {
                    cout << "Unknown escalation type!" << endl;
                    inspect_stream(is);
                    throw new exception();
                }
            }
        }
        
        
        name.set(true);
        
        return is;
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& builder, Name& name) {
        BSONObjBuilder b;
        b   << "given_names" << name.getGivenNames()
            << "surname" << name.getSurname()
            << "standardised_names" << name.getStandardisedNames()
            << "standalone" << name.isStandalone()
            << "attribute" << (Attribute&)name;
        return builder << b.obj();
    }
    
} }

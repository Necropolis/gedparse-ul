/**
 * Name.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Name.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Name::Name(): surname(""), givenNames(std::list<std::string>()), Attribute(), standardisedNames(std::list<StandardisedName>()), standalone(false) {}
    
    std::list<std::string>& Name::getGivenNames() { return givenNames; }
    std::string& Name::getSurname() { return surname; }
    void Name::setSurname(std::string surname) { this->surname = surname; set(true); }
    std::list<StandardisedName>& Name::getStandardisedNames() { return standardisedNames; }
    bool Name::isStandalone() { return standalone; }
    void Name::setStandalone(bool standalone) { this->standalone = standalone; }
    
    std::ostream& operator<< (std::ostream& os, Name& name) {
        std::list<std::string>::iterator iter;
        for (iter = name.givenNames.begin(); iter != name.givenNames.end(); iter++)
            os << *iter << " ";
        if (name.surname!="") os << "/" << name.surname;
        if (name.standalone) {
            os << "\r\n";
            std::list<StandardisedName>::iterator it;
            for (it = name.standardisedNames.begin(); it != name.standardisedNames.end(); it++)
                os << "2 " << *it;
        }
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Name& name) {
        std::string str;
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
                    std::string line_type;
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
                        std::cout << "Unknown line type \"" << line_type << "\"" << std::endl;
                        inspect_stream(is);
                        throw new std::exception();
                    }
                } else {
                    std::cout << "Unknown escalation type!" << std::endl;
                    inspect_stream(is);
                    throw new std::exception();
                }
            }
        }
        
        
        name.set(true);
        
        return is;
    }
    
} }

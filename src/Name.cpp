/**
 * Name.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Name.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Name::Name() :surname(""), givenNames(std::list<std::string>()), _isSet(false) {}
    
    std::list<std::string>& Name::getGivenNames() { return this->givenNames; }
    std::string& Name::getSurname() { return this->surname; }
    void Name::setSurname(std::string surname) { this->surname = surname; }
    bool Name::isSet() { return _isSet; }
    
    std::ostream& operator<< (std::ostream& os, Name& name) {
        std::list<std::string>::iterator iter;
        for (iter = name.givenNames.begin(); iter != name.givenNames.end(); iter++)
            os << *iter << " ";
        if (name.surname!="") os << "/" << name.surname;
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
            } else {
                name.givenNames.push_back(str);
            }
        }
        
        name._isSet = true;
        
        return is;
    }
    
} }

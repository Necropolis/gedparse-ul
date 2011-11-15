/**
 * Name.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Name.hpp"

namespace FamilySearch { namespace GEDCOM {

    Name::Name() :givenNames(new std::list<boost::shared_ptr<std::string> >()), surname(new std::string()) {}
    
    std::list<boost::shared_ptr<std::string> >& Name::getGivenNames() {
        return *this->givenNames;
    }
    std::string& Name::getSurname() {
        return *this->surname;
    }
    void Name::setSurname(std::string& surname) {
        this->surname.reset(&surname);
    }
    
    std::ostream& operator<< (std::ostream& os, Name& name) {
        os << "Given Names: ";
        std::list<boost::shared_ptr<std::string> >::iterator iter;
        for (iter = name.givenNames->begin(); iter != name.givenNames->end(); iter++) {
            os << **iter;
        }
        os << " Last Name: " << *name.surname;
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Name& name) {
        char c = is.peek(), c2;
        std::string str;
        switch (c) {
            default:
                // parse given names
                
                while (true) {
                    c2=is.peek();
                    if (c2 == '\r' || c2 == '/') // end of line or last name, in which case just pass to the next case statement
                        break;
                    is >> str;
                    name.givenNames->push_back(boost::shared_ptr<std::string>(new std::string(str)));
                    is.ignore();
                }
                
            case '/':
                // parse surname
                is.ignore();
                while (is.get()!='\r') {
                    is.unget();
                    is >> str;
                    name.surname->append(str);
                }
                break;
            case '\r':
                // end of line
                break;
        }
        
        return is;
    }
    
} }

/**
 * Record.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Record.hpp"

namespace FamilySearch { namespace GEDCOM {
  
    std::string Record::getType() {
        return *(this->type);
    }
    void Record::setType(std::string& type) {
        this->type.reset(&type);
    }
    Name& Record::getName() {
        return *(this->name);
    }
    void Record::setName(Name &name) {
        this->name.reset(&name);
    }
    Gender& Record::getGender() {
        return *(this->gender);
    }
    void Record::setGender(Gender& gender) {
        this->gender.reset(&gender);
    }

    std::istream& operator>> (std::istream& is, Record& rec) {

        is.ignore(2, '\n');

        while (is.good()) {
            // precondition: at line start
            char c = is.get();
            if (c=='0') {
                return is;
            } else if (c=='1') {
            // one of various record attribute types
            std::string line_type;
            is >> line_type;
            std::cout << "Encountered line of type \"" << line_type << "\"" << std::endl;
              
            if (line_type=="SEX") {
                Gender *g = new Gender();
                is >> *g;
                rec.setGender(*g);
            } else {
                std::cout << "Unknown line type \"" << line_type << "\"" << std::endl;
            }
              
            is.ignore(2, '\n');
            
          } else if (c=='2') {
              // an escelation
          } else {
              // fubar
              std::cerr << "Unknown record level (ASCII)" << (int)c << " on line " << __LINE__ << std::endl;
              return is;
          }
          
        }

        return is;
    }
  
} }
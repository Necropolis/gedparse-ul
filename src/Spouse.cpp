/**
 * Spouse.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Spouse.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Spouse::Spouse(): standardisedNames(std::list<StandardisedName>()), name(Name()), Attribute() {}
    
    Name& Spouse::getName() { return name; }
    void Spouse::setName(Name name) { this->name = name; }
    std::list<StandardisedName>& Spouse::getStandardisedNames() { return standardisedNames; }
    
    std::ostream& operator<< (std::ostream& os, Spouse& spouse) {
        os << "1 SPOU " << spouse.name << "\r\n";
        std::list<StandardisedName>::iterator iter;
        for (iter=spouse.standardisedNames.begin(); iter!=spouse.standardisedNames.end(); ++iter)
            os << "2 " << *iter;
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Spouse& spouse) {
        // stream is now a NAME part
        is >> spouse.name;
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
                    spouse.standardisedNames.push_back(stgn);
                } else if (line_type=="STSN") {
                    StandardisedName stsn;
                    is >> stsn;
                    stsn.setGivenName(false);
                    spouse.standardisedNames.push_back(stsn);
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
        return is;
    }
    
} }

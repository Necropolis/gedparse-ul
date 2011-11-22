/**
 * Spouse.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Spouse.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Spouse::Spouse(): standardisedNames(list<StandardisedName>()), name(Name()), Attribute() {}
    Spouse::Spouse(BSONElement elem): name(elem["name"]), Attribute(elem["attribute"]) {
        // standardised names?
        vector<BSONElement> _standardised_names = elem["standardisedNames"].Array();
        for (vector<BSONElement>::iterator it = _standardised_names.begin();
             it != _standardised_names.end();
             ++it)
            standardisedNames.push_back(StandardisedName(*it));
    }
    Spouse::Spouse(BSONObj obj): name(obj["name"]), Attribute(obj["name"]) {
        // standardised names?
        vector<BSONElement> _standardised_names = obj["standardisedNames"].Array();
        for (vector<BSONElement>::iterator it = _standardised_names.begin();
             it != _standardised_names.end();
             ++it)
            standardisedNames.push_back(StandardisedName(*it));
    }
    
    Name& Spouse::getName() { return name; }
    void Spouse::setName(Name name) { this->name = name; }
    list<StandardisedName>& Spouse::getStandardisedNames() { return standardisedNames; }
    
    ostream& operator<< (ostream& os, Spouse& spouse) {
        os << "1 SPOU " << spouse.name << "\r\n";
        list<StandardisedName>::iterator iter;
        for (iter=spouse.standardisedNames.begin(); iter!=spouse.standardisedNames.end(); ++iter)
            os << "2 " << *iter;
        return os;
    }
    
    istream& operator>> (istream& is, Spouse& spouse) {
        // stream is now a NAME part
        is >> spouse.name;
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
                    spouse.standardisedNames.push_back(stgn);
                } else if (line_type=="STSN") {
                    StandardisedName stsn;
                    is >> stsn;
                    stsn.setGivenName(false);
                    spouse.standardisedNames.push_back(stsn);
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
        
        spouse.set(true);
        
        return is;
    }
    
    BSONObj Spouse::asBSON() {
        BSONObjBuilder b;
        b << "name" << name;
        BSONArrayBuilder a;
        a<<standardisedNames;
        b.appendArray("standardisedNames", a.done());
        b << "attribute" << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Spouse& spouse) {
        return bv << spouse.asBSON();
    }
    
    void Spouse::emitFieldHeaders(CSVOStream& csv) {
        Name().emitFieldHeaders(csv); // name
        csv << "standardised given names"
            << "standardised surnames";
    }
    
    void Spouse::emitData(CSVOStream& csv) {
        name.emitData(csv);
        basic_string<char> stgn;
        basic_string<char> stsn;
        for (list<StandardisedName>::iterator it = standardisedNames.begin();
             it != standardisedNames.end();
             ++it)
            if (it->isGivenName())
                stgn.append(it->getStandardisedName()).append(" ");
            else
                stsn.append(it->getStandardisedName()).append(" ");
        if (stgn.length()>0)stgn.erase(stgn.length()-1, 1);
        if (stsn.length()>0)stsn.erase(stsn.length()-1, 1);
        csv << stgn
            << stsn;
    }
    
} }

/**
 * Record.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Record.hpp"

#include <exception>

namespace FamilySearch { namespace GEDCOM {
    
    std::string& Record::getType() { return type; }
    void Record::setType(std::string type) { this->type = type; }
    std::list<Spouse>& Record::getSpouses() { return spouses; }
    std::list<Marriage>& Record::getMarriages() { return marriages; }
    Name& Record::getName() { return name; }
    void Record::setName(Name name) { this->name = name; }
    Gender& Record::getGender() { return gender; }
    void Record::setGender(Gender gender) { this->gender = gender; }
    Miscelleneous& Record::getMiscelleneous() { return misc; }
    void Record::setMiscelleneous(Miscelleneous misc) { this->misc = misc; }
    Batch& Record::getBatch() { return batch; }
    void Record::setBatch(Batch batch) { this->batch = batch; }
    Date& Record::getDate() { return date; }
    void Record::setDate(Date date) { this->date = date; }

    std::ostream& operator<< (std::ostream& os, Record& rec) {
        os << "0 " << rec.type << "\r\n";
        if (rec.getName().isSet()) os << "1 NAME " << rec.name << "\r\n";
        if (rec.gender.isSet()) os << "1 " << rec.gender;
        for (std::list<Spouse>::iterator it = rec.spouses.begin(); it != rec.spouses.end(); ++it)
            os << *it;
        for (std::list<Marriage>::iterator it = rec.marriages.begin(); it != rec.marriages.end(); ++it)
            os << *it;
        if (rec.misc.isSet()) os << "1 " << rec.misc;
        if (rec.batch.isSet()) os << "1 " << rec.batch;
        
#ifdef DEBUG
        std::cout << std::endl << std::endl << "Raw bytes: " << std::endl << rec.raw << std::endl;
        std::cout << "Beginning Location: " << rec.begin << std::endl << "Ending Location: " << rec.end << std::endl << std::endl;
#endif
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Record& rec) {

#ifdef DEBUG
        rec.begin = is.tellg();
#endif
        
        is.ignore(2, '\n');

        while (is.good()) {
            while (is.peek()<'0'||is.peek()>'9') {is.get();} // precondition: at line start
            char c = is.get();
            if (c=='0') {
                is.unget();
                break;
            } else if (c=='1') {
                // one of various record attribute types
                std::string line_type;
                is >> line_type;

                if (line_type=="SEX") {
                    Gender g;
                    is >> g;
                    rec.setGender(g);
                } else if (line_type=="SPOU") {
                    Spouse s;
                    is >> s;
                    rec.spouses.push_back(s);
                } else if (line_type=="MARR") {
                    Marriage m;
                    is >> m;
                    rec.marriages.push_back(m);
                } else if (line_type=="MISC") {
                    Miscelleneous m;
                    is >> m;
                    rec.setMiscelleneous(m);
                } else if (line_type=="BATC") {
                    Batch b;
                    is >> b;
                    rec.setBatch(b);
                } else if (line_type=="NAME") {
                    Name n;
                    is >> n;
                    rec.setName(n);
                } else {
                    std::cout << "Unknown line type \"" << line_type << "\"" << std::endl;
                    inspect_stream(is);
                    throw new std::exception();
                }
            
            } else if (c=='2') {
                // an unexpected escelation
            } else {
                // fubar
                std::cout << "Error area:" << std::endl;
                inspect_stream(is);
                std::cerr << "Unknown record level (ASCII)" << (int)c << " on line " << __LINE__ << std::endl;
                return is;
            }
          
        }
        
#ifdef DEBUG
        rec.end = is.tellg();
        
        is.seekg(rec.begin);
        std::streamsize len= rec.end - rec.begin;
        char* _raw = (char*)malloc(sizeof(char)*len);
        is.readsome(_raw, len);
        rec.raw = std::string(_raw, len);
        std::string raw_pfx("0 ");
        raw_pfx.append(rec.type);
        rec.raw.insert(0, raw_pfx);
#endif
        
        return is;
    }
  
} }
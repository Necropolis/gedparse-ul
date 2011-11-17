/**
 * Record.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Record.hpp"

#include <exception>
#ifdef DEBUG
#include <sstream>
#include <vector>
#endif

namespace FamilySearch { namespace GEDCOM {
    
    std::string& Record::getType() { return type; }
    void Record::setType(std::string type) { this->type = type; }
    std::list<Spouse>& Record::getSpouses() { return spouses; }
    std::list<Marriage>& Record::getMarriages() { return marriages; }
    std::list<Event>& Record::getEvents() { return events; }
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
    Name& Record::getFather() { return father; }
    void Record::setFather(Name father) { this->father = father; }
    Name& Record::getMother() { return mother; }
    void Record::setMother(Name mother) { this->mother = mother; }
#ifdef DEBUG
    std::string& Record::getRaw() { return raw; }
    void Record::setRaw(std::string raw) { this->raw = raw; }
    std::iostream::pos_type& Record::getBegin() { return begin; }
    void Record::setBegin(std::iostream::pos_type begin) { this->begin = begin; }
    std::iostream::pos_type& Record::getEnd() { return end; }
    void Record::setEnd(std::iostream::pos_type end) { this->end = end; }
#endif

#ifdef DEBUG
    void Record::output_debug_info(std::ostream& os) {
        os << "Beginning Location: ";
        std::ios_base::fmtflags flags = os.flags();
        os.flags(std::ios::hex| std::ios::showbase);
        os << begin << std::endl << "Ending Location: " << end << std::endl;
        os.flags(flags);
        os << std::endl << "Parsed Record: " << std::endl << *this;
        os << std::endl << "Raw bytes: " << std::endl << raw << std::endl;
    }
    bool Record::validate_parse() {
        std::stringstream orig(raw, std::stringstream::in|std::stringstream::out);
        std::stringstream pars(std::string(), std::stringstream::in|std::stringstream::out);
        pars << *this;
        
        std::vector<std::string> orig_vec; orig.seekg(0, std::ios_base::beg);
        std::vector<std::string> pars_vec; pars.seekg(0, std::ios_base::beg);
        while (orig.good()) { std::string str; orig >> str; if (str!="") orig_vec.push_back(str); }
        while (pars.good()) { std::string str; pars >> str; if (str!="") pars_vec.push_back(str); }
        
        std::vector<std::string> smaller, larger;
        if (orig_vec.size()<pars_vec.size()) { smaller = orig_vec; larger = pars_vec; }
        else { smaller = pars_vec; larger = orig_vec; }
        
        bool retval = true;
        if (orig_vec.size()!=pars_vec.size()) {
            std::cerr << "Wordcount of original does not equal parsed!" << std::endl;
            std::cerr << "Wordcount of Original: " << orig_vec.size() << std::endl;
            std::cerr << "Wordcount of Parsed  : " << pars_vec.size() << std::endl;
                            
            std::cerr << "          orig      pars" << std::endl;
            for (size_t j=0; j < smaller.size(); ++j)
                std::cerr << "Word " << j << ": " << orig_vec[j] << "  " << pars_vec[j] << std::endl;
            for (size_t j=smaller.size(); j < larger.size(); ++j) {
                if (smaller==orig_vec)
                    std::cerr << "Word " << j << ": " << "NULL  " << pars_vec[j] << std::endl;
                else
                    std::cerr << "Word " << j << ": " << orig_vec[j] << "  NULL"  << std::endl;
            }
            
            retval = false;
        }

        
        for (size_t i=0; i < smaller.size(); ++i) {
            std::string st0 = pars_vec[i];
            std::string st1 = orig_vec[i];
            if (st0!=st1) {
                retval= false;
            }
        }
                
        return retval;
    }
#endif
    
    std::ostream& operator<< (std::ostream& os, Record& rec) {
        os << "0 " << rec.type << "\r\n";
        if (rec.getName().isSet()) os << "1 NAME " << rec.name;
        if (rec.gender.isSet()) os << "1 " << rec.gender;
        if (rec.father.isSet()) os << "1 FATH " << rec.father;
        if (rec.mother.isSet()) os << "1 MOTH " << rec.mother;
        for (std::list<Event>::iterator it = rec.events.begin(); it != rec.events.end(); ++it) os << *it;
        for (std::list<Spouse>::iterator it = rec.spouses.begin(); it != rec.spouses.end(); ++it) os << *it;
        for (std::list<Marriage>::iterator it = rec.marriages.begin(); it != rec.marriages.end(); ++it) os << *it;
        if (rec.misc.isSet()) os << "1 " << rec.misc;
        if (rec.batch.isSet()) os << "1 " << rec.batch;
        return os;
    }
    
    std::istream& operator>> (std::istream& is, Record& rec) {

#ifdef DEBUG
        rec.begin = is.tellg();
#endif
        
        is.ignore(2, '\n');

        while (is.good()) {
            while (is.peek()<'0'||is.peek()>'9') { is.get();} // precondition: at line start
            char c = is.get();
            if (c=='0') {
                is.unget();
                break;
            } else if (c=='1') {
                // one of various record attribute types
                std::string line_type;
                is >> line_type;

                if (line_type=="SEX") { // Gender
                    is >> rec.gender;
                } else if (line_type=="SPOU") { // Spouse
                    Spouse s;
                    is >> s;
                    rec.spouses.push_back(s);
                } else if (line_type=="MARR") { // Marriage
                    Marriage m;
                    is >> m;
                    rec.marriages.push_back(m);
                } else if (line_type=="MISC") { // Miscellenous
                    is >> rec.misc;
                } else if (line_type=="BATC") { // Batch Number
                    is >> rec.batch;
                } else if (line_type=="NAME") { // Name
                    rec.name.setStandalone(true);
                    is >> rec.name;
                } else if (line_type=="FATH") {
                    rec.father.setStandalone(true);
                    is >> rec.father;
                } else if (line_type=="MOTH") {
                    rec.mother.setStandalone(true);
                    is >> rec.mother;
                } else if (line_type=="EVEN") { // Event
                    Event e;
                    is >> e;
                    rec.events.push_back(e);
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
        if (!is.good()) {
            is.clear();
            is.seekg(0,std::ios_base::end);
        }
        rec.end = is.tellg();
        is.seekg(rec.begin);
        std::streamsize len = rec.end - rec.begin;
        char* sz = (char*)malloc(sizeof(char)*len);
        is.read(sz, len);
        rec.raw=std::string(sz, len);
        free(sz);
        std::string raw_pfx("0 ");
        raw_pfx.append(rec.type);
        rec.raw.insert(0, raw_pfx);
#endif
        
        return is;
    }
  
} }
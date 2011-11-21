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
    
    Record::Record() { }
    
    Record::Record(BSONElement elem): type(elem["type"].String()), name(elem["name"]), father(elem["father"]), mother(elem["mother"]), gender(elem["gender"]), misc(elem["misc"]), batch(elem["batch"]) {
        // spouses
        /*
         vector<BSONElement> _givenNames = obj["given_names"].Array();
         vector<BSONElement>::iterator it;
         for (it = _givenNames.begin(); it != _givenNames.end(); ++it) givenNames.push_back(it->String());
         vector<BSONElement> _stadardisedNames = obj["standardised_names"].Array();
         for (it = _stadardisedNames.begin(); it != _stadardisedNames.end(); ++it) standardisedNames.push_back(StandardisedName(it->Obj()));

         */
        vector<BSONElement> _spouses = elem["spouses"].Array();
        for (vector<BSONElement>::iterator it = _spouses.begin();
             it != _spouses.end();
             ++it)
            spouses.push_back(Spouse(*it));
        vector<BSONElement> _marriages = elem["marriages"].Array();
        for (vector<BSONElement>::iterator it = _marriages.begin();
             it != _marriages.end();
             ++it)
            marriages.push_back(Marriage(*it));
        vector<BSONElement> _events = elem["events"].Array();
        for (vector<BSONElement>::iterator it = _events.begin();
             it != _events.end();
             ++it)
            events.push_back(Event(*it));
    }
    
    Record::Record(BSONObj obj): type(obj["type"].String()), name(obj["name"]), father(obj["father"]), mother(obj["mother"]), gender(obj["gender"]), misc(obj["misc"]), batch(obj["batch"]) {
        // spouses
        vector<BSONElement> _spouses = obj["spouses"].Array();
        for (vector<BSONElement>::iterator it = _spouses.begin();
             it != _spouses.end();
             ++it)
            spouses.push_back(Spouse(*it));
        vector<BSONElement> _marriages = obj["marriages"].Array();
        for (vector<BSONElement>::iterator it = _marriages.begin();
             it != _marriages.end();
             ++it)
            marriages.push_back(Marriage(*it));
        vector<BSONElement> _events = obj["events"].Array();
        for (vector<BSONElement>::iterator it = _events.begin();
             it != _events.end();
             ++it)
            events.push_back(Event(*it));
    }
    
    string& Record::getType() { return type; }
    void Record::setType(string type) { this->type = type; }
    list<Spouse>& Record::getSpouses() { return spouses; }
    list<Marriage>& Record::getMarriages() { return marriages; }
    list<Event>& Record::getEvents() { return events; }
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
    string& Record::getRaw() { return raw; }
    void Record::setRaw(string raw) { this->raw = raw; }
    iostream::pos_type& Record::getBegin() { return begin; }
    void Record::setBegin(iostream::pos_type begin) { this->begin = begin; }
    iostream::pos_type& Record::getEnd() { return end; }
    void Record::setEnd(iostream::pos_type end) { this->end = end; }
    void Record::clearRaw() { raw.clear(); }
#endif

#ifdef DEBUG
    void Record::output_debug_info(ostream& os) {
        os << "Beginning Location: ";
        ios_base::fmtflags flags = os.flags();
        os.flags(ios::hex| ios::showbase);
        os << begin << endl << "Ending Location: " << end << endl;
        os.flags(flags);
        os << endl << "Parsed Record: " << endl << *this;
        os << endl << "Raw bytes: " << endl << raw << endl;
    }
    bool Record::validate_parse() {
        stringstream orig(raw, stringstream::in|stringstream::out);
        stringstream pars(string(), stringstream::in|stringstream::out);
        pars << *this;
        
        vector<string> orig_vec; orig.seekg(0, ios_base::beg);
        vector<string> pars_vec; pars.seekg(0, ios_base::beg);
        while (orig.good()) { string str; orig >> str; if (str!="") orig_vec.push_back(str); }
        while (pars.good()) { string str; pars >> str; if (str!="") pars_vec.push_back(str); }
        
        vector<string> smaller, larger;
        if (orig_vec.size()<pars_vec.size()) { smaller = orig_vec; larger = pars_vec; }
        else { smaller = pars_vec; larger = orig_vec; }
        
        bool retval = true;
        if (orig_vec.size()!=pars_vec.size()) {
            cerr << "Wordcount of original does not equal parsed!" << endl;
            cerr << "Wordcount of Original: " << orig_vec.size() << endl;
            cerr << "Wordcount of Parsed  : " << pars_vec.size() << endl;
                            
            cerr << "          orig      pars" << endl;
            for (size_t j=0; j < smaller.size(); ++j)
                cerr << "Word " << j << ": " << orig_vec[j] << "  " << pars_vec[j] << endl;
            for (size_t j=smaller.size(); j < larger.size(); ++j) {
                if (smaller==orig_vec)
                    cerr << "Word " << j << ": " << "NULL  " << pars_vec[j] << endl;
                else
                    cerr << "Word " << j << ": " << orig_vec[j] << "  NULL"  << endl;
            }
            
            retval = false;
        }

        
        for (size_t i=0; i < smaller.size(); ++i) {
            string st0 = pars_vec[i];
            string st1 = orig_vec[i];
            if (st0!=st1) {
                retval= false;
            }
        }
                
        return retval;
    }
#endif
    
    ostream& operator<< (ostream& os, Record& rec) {
        os << "0 " << rec.type << "\r\n";
        if (rec.getName().isSet()) os << "1 NAME " << rec.name;
        if (rec.gender.isSet()) os << "1 " << rec.gender;
        if (rec.father.isSet()) os << "1 FATH " << rec.father;
        if (rec.mother.isSet()) os << "1 MOTH " << rec.mother;
        for (list<Event>::iterator it = rec.events.begin(); it != rec.events.end(); ++it) os << *it;
        for (list<Spouse>::iterator it = rec.spouses.begin(); it != rec.spouses.end(); ++it) os << *it;
        for (list<Marriage>::iterator it = rec.marriages.begin(); it != rec.marriages.end(); ++it) os << *it;
        if (rec.misc.isSet()) os << "1 " << rec.misc;
        if (rec.batch.isSet()) os << "1 " << rec.batch;
        return os;
    }
    
    istream& operator>> (istream& is, Record& rec) {

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
                string line_type;
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
                    cout << "Unknown line type \"" << line_type << "\"" << endl;
                    inspect_stream(is);
                    throw new exception();
                }
            
            } else if (c=='2') {
                // an unexpected escelation
            } else {
                // fubar
                cout << "Error area:" << endl;
                inspect_stream(is);
                cerr << "Unknown record level (ASCII)" << (int)c << " on line " << __LINE__ << endl;
                return is;
            }
          
        }
        
#ifdef DEBUG
        if (!is.good()) {
            is.clear();
            is.seekg(0,ios_base::end);
        }
        rec.end = is.tellg();
        is.seekg(rec.begin);
        streamsize len = rec.end - rec.begin;
        char* sz = (char*)malloc(sizeof(char)*len);
        is.read(sz, len);
        rec.raw=string(sz, len);
        free(sz);
        string raw_pfx("0 ");
        raw_pfx.append(rec.type);
        rec.raw.insert(0, raw_pfx);
#endif
        
        return is;
    }
    
    BSONObj Record::asBSON() {
        BSONObjBuilder b;
        b   << "type"       << type
            << "name"       << name
            << "father"     << father
            << "mother"     << mother
            << "gender"     << gender;
        BSONArrayBuilder as;
        as << spouses;
        b.appendArray("spouses", as.done());
        BSONArrayBuilder am;
        am << marriages;
        b.appendArray("marriages", am.done());
        BSONArrayBuilder ae;
        ae << events;
        b.appendArray("events", ae.done());
        b   << "misc"       << misc
            << "batch"      << batch;
        return b.obj();
    }
    
    /* serialise a Record to a BSONObjBuilder, fit for becoming a BSONObj */
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Record& rec) {
        return bv << rec.asBSON();
    }
      
} }

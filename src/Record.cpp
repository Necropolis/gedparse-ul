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

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    Record::Record(): name(true), father(true), mother(true) { }
    
    Record::Record(string _type): type(_type), name(true), father(true), mother(true) { }
    
    Record::Record(BSONElement elem): type(elem["type"].String()), name(elem["name"]), father(elem["father"]), mother(elem["mother"]), gender(elem["gender"]), misc(elem["misc"]), batch(elem["batch"]), marriage(elem["marriage"]), spouse(elem["spouse"]), event(elem["event"]) { }
    
    Record::Record(BSONObj obj): type(obj["type"].String()), name(obj["name"]), father(obj["father"]), mother(obj["mother"]), gender(obj["gender"]), misc(obj["misc"]), batch(obj["batch"]), marriage(obj["marriage"]), spouse(obj["spouse"]), event(obj["event"]) { }
    
    string& Record::getType() { return type; }
    void Record::setType(string type) { this->type = type; }
    Spouse& Record::getSpouse() { return spouse; }
    void Record::setSpouse(Spouse& spouse) { this->spouse = spouse; }
    Marriage& Record::getMarriage() { return marriage; }
    void Record::setMarriage(Marriage& marriage) { this->marriage = marriage; }
    Event& Record::getEvent() { return event; }
    void Record::setEvent(Event& event) { this->event = event; }
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
        if (rec.event.isSet()) os << rec.event;
        if (rec.spouse.isSet()) os << rec.spouse;
        if (rec.marriage.isSet()) os << rec.marriage;
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
                    is >> rec.spouse;
                } else if (line_type=="MARR") { // Marriage
                    is >> rec.marriage;
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
                    is >> rec.event;
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
            << "gender"     << gender
            << "marriage"   << marriage
            << "spouse"     << spouse
            << "event"      << event
            << "misc"       << misc
            << "batch"      << batch;
        return b.obj();
    }
    
    /* serialise a Record to a BSONObjBuilder, fit for becoming a BSONObj */
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Record& rec) {
        return bv << rec.asBSON();
    }
    
    /**
     * Observations by David Barss:
     *
     * Field                FAM     INDI
     * TYPE                 X       X
     * NAME                 X       X
     *   GIVEN NAMES        X       X
     *   SURNAMES           X       X
     *   STGN               X       X
     *   STSN               X       X
     * FATHER                       X
     *   GIVEN NAMES                X
     *   SURNAMES                   X
     *   STGN                       X
     *   STSN                       X
     * MOTHER                       X
     *   GIVEN NAMES                X
     *   SURNAMES                   X
     *   STGN                       X
     *   STSN                       X
     * GENDER               X
     * MARRIAGE             X
     *   PLACE              X
     *     COUNTY CODE      X
     *     COUNTRY          X
     *     COUNTY           X
     *     TOWN             X
     *     BOROUGH          X
     *   DATE               X
     * SPOUSE               X
     *   NAME               X
     *     GIVEN NAMES      X
     *     SURNAMES         X
     *     STGN
     *     STSN
     *   STGN               X
     *   STSN               X
     * EVENT                        X
     *   TYPE                       X
     *   DATE                       X
     *   PLACE                      X
     *     COUNTY CODE              X
     *     COUNTRY                  X
     *     COUNTY                   X
     *     TOWN                     X
     *     BOROUGH                  X
     * MISC                 X       X
     * BATCH                X       X
     */
    
    void Record::emitFieldHeaders(CSVOStream& csv) {
        csv << "type";
        Name().emitFieldHeaders(csv); // name
        if (type=="INDI") {
            Name().emitFieldHeaders(csv); // father
            Name().emitFieldHeaders(csv); // mother
        }
        if (type=="FAM") {
            Gender().emitFieldHeaders(csv); // gender
            Marriage().emitFieldHeaders(csv); // marriage
            Spouse().emitFieldHeaders(csv); // spouse
        }
        if (type=="INDI")
            Event().emitFieldHeaders(csv); // event
        csv << "misc"
            << "batch";
    }
    
    void Record::emitData(CSVOStream& csv) {
        csv << type;
        name.emitData(csv);
        if (type=="INDI") {
            father.emitData(csv);
            mother.emitData(csv);
        }
        if (type=="FAM") {
            gender.emitData(csv);
            marriage.emitData(csv);
            spouse.emitData(csv);
        }
        if (type=="INDI")
            event.emitData(csv);
        csv << trim(misc.getNote()).c_str()
            << batch.getBatch();
    }
      
} }

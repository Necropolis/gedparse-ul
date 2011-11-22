/**
 * Record.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <string>
#include <list>
// mongo
#include "bson/bson.h"
// familysearch
#include "Marriage.hpp"
#include "Spouse.hpp"
#include "Event.hpp"
#include "Name.hpp"
#include "Gender.hpp"
#include "Miscelleneous.hpp"
#include "Batch.hpp"
#include "Date.hpp"
#include "Util.hpp"
// fsdev
#include "CSVOStream.hpp"

#ifndef __RECORD_HPP_
#define __RECORD_HPP_

using namespace std;
using namespace mongo;
using namespace fsdev;

namespace FamilySearch { namespace GEDCOM {

    /**
     * Class representing a single record from an unlinked GEDCOM.
     *
     * Defining characteristics are:
     *
     * 1. Every record begings with CR/LF0
     * 2. Every record is of type FAM or INDI
     */  
    class Record : public CSVRecord {
    private:
        string type;
        Spouse spouse;
        Marriage marriage;
        Event event;
        Name name, father, mother;
        Gender gender;
        Miscelleneous misc;
        Batch batch;
        Date date;
#ifdef DEBUG
        string raw;
        iostream::pos_type begin;
        iostream::pos_type end;
#endif
      
    public:
        Record();
        Record(BSONElement);
        Record(BSONObj);
        
        // gedcom serialisation
        friend ostream& operator<< (ostream&, Record&);
        friend istream& operator>> (istream&, Record&);
        
        // bson serialisation
        BSONObj asBSON();
        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Record&);
        
        // csv serialisation
        void emitFieldHeaders(CSVOStream&);
        void emitData(CSVOStream&);
        
#ifdef DEBUG
        /* show the original stream against what gedparse-ul can recreate */
        void output_debug_info(ostream&);
        /* try to word-for-word validate the record against the original stream */
        bool validate_parse();
#endif
      
        string& getType();
        void setType(string);
        Spouse& getSpouse();
        void setSpouse(Spouse&);
        Marriage& getMarriage();
        void setMarriage(Marriage&);
        Event& getEvent();
        void setEvent(Event&);
        Name& getName();
        void setName(Name);
        Gender& getGender();
        void setGender(Gender);
        Miscelleneous& getMiscelleneous();
        void setMiscelleneous(Miscelleneous);
        Batch& getBatch();
        void setBatch(Batch);
        Date& getDate();
        void setDate(Date);
        Name& getFather();
        void setFather(Name);
        Name& getMother();
        void setMother(Name);
#ifdef DEBUG
        string& getRaw();
        void setRaw(string);
        iostream::pos_type& getBegin();
        void setBegin(iostream::pos_type);
        iostream::pos_type& getEnd();
        void setEnd(iostream::pos_type);
        void clearRaw();
#endif
    };

    // gedcom serialisation
    ostream& operator<< (ostream&, Record&);
    istream& operator>> (istream&, Record&);
    
    // bson serialisation
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Record&);
  
} }

#endif

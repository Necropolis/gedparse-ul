/**
 * Record.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <string>
#include <list>
// familysearch
#include "Marriage.hpp"
#include "Spouse.hpp"
#include "Name.hpp"
#include "Gender.hpp"
#include "Miscelleneous.hpp"
#include "Batch.hpp"
#include "Date.hpp"
#include "Util.hpp"

#ifndef __RECORD_HPP_
#define __RECORD_HPP_

namespace FamilySearch { namespace GEDCOM {

    /**
     * Class representing a single record from an unlinked GEDCOM.
     *
     * Defining characteristics are:
     *
     * 1. Every record begings with CR/LF0
     * 2. Every record is of type FAM or INDI
     */  
    class Record {
    private:
        std::string type;
        std::list<Spouse> spouses;
        std::list<Marriage> marriages;
        Name name;
        Gender gender;
        Miscelleneous misc;
        Batch batch;
        Date date;
#ifdef DEBUG
        std::string raw;
        std::iostream::pos_type begin;
        std::iostream::pos_type end;
#endif
      
    public:
        
        friend std::ostream& operator<< (std::ostream&, Record&);
        friend std::istream& operator>> (std::istream&, Record&);
      
        std::string& getType();
        void setType(std::string);
        std::list<Spouse>& getSpouses();
        std::list<Marriage>& getMarriages();
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
    };

    std::ostream& operator<< (std::ostream&, Record&);
    std::istream& operator>> (std::istream&, Record&);
  
} }

#endif

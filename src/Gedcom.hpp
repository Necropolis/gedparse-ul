/**
 * Gedcom.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <list>
#include <vector>
// boost
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
// familysearch
#include "Record.hpp"

#ifndef __GEDCOM_HPP_
#define __GEDCOM_HPP_

namespace FamilySearch { namespace GEDCOM {

    using namespace std;
    using namespace boost;
    using namespace mongo;
    
    class Gedcom;
    
    class GedcomParseDelegate {
    public:
        virtual void parsedRecord(Gedcom&,
                                  Record&,
                                  istream::pos_type,
                                  istream::pos_type)=0;
    };
    
    /**
     * Class representing an unlinked GEDCOM. Unlinked GEDCOMs are right little buggers to parse.
     * They look something like this:
     *
     * \r\n0 FAM
     * \r\n1 SEX F
     * \r\n1 SPOU George /BRUCE
     * \r\n1 MARR
     * \r\n2 PLAC Fife, Scotland, Fife, Kingsbarns
     * \r\n1 MISC FR582
     * \r\n1 BATC M114414
     * \r\n0 FAM
     * ...
     *
     * Defining characteristics are:
     *
     * 1. Every GEDCOM starts with a CR/LF
     */  
    class Gedcom {
    private:
        scoped_ptr<vector<boost::shared_ptr<FamilySearch::GEDCOM::Record> > > records;
        scoped_ptr<GedcomParseDelegate> dg;
      
    public:
        Gedcom();
        /** parse from a stream */
        friend istream& operator>> (istream &is, Gedcom &ged);
      
        vector<boost::shared_ptr<Record> >& getRecords();
        GedcomParseDelegate& getDelegate();
        void setDelegate(GedcomParseDelegate& dg);
    };

    istream& operator>> (istream &is, Gedcom &ged);
  
} }


#endif

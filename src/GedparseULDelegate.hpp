/**
 * GedparseULDelegate.hpp - 21 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
// boost
#include <boost/shared_ptr.hpp>
// mongo
#include "client/dbclient.h"
// familysearch
#include "Gedcom.hpp"
#include "Record.hpp"
// fsdev
#include "CSVOStream.hpp"

using namespace std;
using namespace boost;
using namespace mongo;

#ifndef __GEDPARSEULDELEGATE_HPP_
#define __GEDPARSEULDELEGATE_HPP_

namespace FamilySearch { namespace GEDCOM {
    
    class GedparseULDelegate : public GedcomParseDelegate {
    private:
        size_t records;
        shared_ptr<DBClientConnection> conn;
        string collection;
        bool useDb;
        
    public:
        GedparseULDelegate();
        
        void parsedRecord(Gedcom&,
                          Record&,
                          istream::pos_type,
                          istream::pos_type);
        
        DBClientConnection& getConnection();
        void setConnection(DBClientConnection&);
        string& getCollection();
        void setCollection(string);
        bool isUsingDb();
        void setUsingDb(bool);
    };
    
} }

#endif
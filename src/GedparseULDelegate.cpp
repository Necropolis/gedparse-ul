/**
 * GedparseULDelegate.cpp - 21 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "GedparseULDelegate.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    GedparseULDelegate::GedparseULDelegate(): records(0), collection(""), useDb(false) { }
    
    void GedparseULDelegate::parsedRecord(Gedcom& ged,
                                          Record& r,
                                          istream::pos_type current,
                                          istream::pos_type length) {
        ++ records;
        
        cout << "[[ WIN ]] Now treating record " << records << endl;
        cout << "          " << (double)current/(double)length*100.0f << "% of the way done" << endl;
        
#ifdef DEBUG
        if (r.validate_parse()) {
            cout << "          " << "[[ DEBUG ]] Parsed Successfully" << endl;
            r.clearRaw();
        } else {
            cout << "          " << "[[ DEBUG ]] Parsed [[ FAILED ]]" << endl;
            r.output_debug_info(cout);
        }
#endif
        
        if (useDb) {
            // insert the record
            conn->insert(collection, r.asBSON());
            cout << "          " << "[[ WIN ]] Inserted into DB Successfully" << endl;
        }
        
        CSVOStream csv("/Users/cmiller/Desktop/tmp.csv");
        r.emitFieldHeaders(csv);
        csv << CSVRecordSeparator;
        r.emitData(csv);
        csv << CSVRecordSeparator;
        
    }
    
    DBClientConnection& GedparseULDelegate::getConnection() { return *conn; }
    void GedparseULDelegate::setConnection(DBClientConnection& conn) { this->conn.reset(&conn); useDb = true; }
    string& GedparseULDelegate::getCollection() { return collection; }
    void GedparseULDelegate::setCollection(string collection) { this->collection = collection; useDb = true; }
    bool GedparseULDelegate::isUsingDb() { return useDb; }
    void GedparseULDelegate::setUsingDb(bool _useDb) { useDb = _useDb; }
    
} }

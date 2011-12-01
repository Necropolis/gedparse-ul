/**
 * GedparseULDelegate.cpp - 21 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "GedparseULDelegate.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    GedparseULDelegate::GedparseULDelegate(): records(0), collection(""), useDb(false), useCsv(false) { }
    
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
        
        if (useCsv) {
            if (r.getType() == "INDI") {
                r.emitData(*csv_indi);
                *csv_indi << CSVRecordSeparator;
            } else {
                r.emitData(*csv_fam);
                *csv_fam << CSVRecordSeparator;
            }
        }
        
    }
    
    DBClientConnection& GedparseULDelegate::getConnection() { return *conn; }
    void GedparseULDelegate::setConnection(DBClientConnection& conn) { this->conn.reset(&conn); useDb = true; }
    string& GedparseULDelegate::getCollection() { return collection; }
    void GedparseULDelegate::setCollection(string collection) { this->collection = collection; useDb = true; }
    CSVOStream& GedparseULDelegate::getIndiCSVOStream() { return *csv_indi; }
    void GedparseULDelegate::setIndiCSVOStream(CSVOStream& csv) { this->csv_indi.reset(&csv); useCsv = true; }
    CSVOStream& GedparseULDelegate::getFamCSVOStream() { return *csv_fam; }
    void GedparseULDelegate::setFamCSVOStream(CSVOStream& csv) { this->csv_fam.reset(&csv); useCsv = true; }
    bool GedparseULDelegate::isUsingDb() { return useDb; }
    void GedparseULDelegate::setUsingDb(bool _useDb) { useDb = _useDb; }
    bool GedparseULDelegate::isUsingCSV() { return useCsv; }
    void GedparseULDelegate::setUsingCSV(bool _useCsv) { useCsv = _useCsv; }
    
} }

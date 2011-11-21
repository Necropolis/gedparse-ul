/**
 * Gedcom.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Gedcom.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
  
    Gedcom::Gedcom(): records(new vector<shared_ptr<Record> >()) { }
  
    vector<shared_ptr<Record> >& Gedcom::getRecords() { return *records; }
  
    istream& operator>> (istream &is, Gedcom &ged) {
        istream::pos_type tmp = is.tellg();
        is.seekg(0, istream::end);
        istream::pos_type length = is.tellg();
        is.seekg(tmp);
        size_t records = 0;
        
        while (is.good()) {
            ios::pos_type loc = is.tellg();
            char c = is.get();
            if (!is.good()) {
                cout << "End of GEDCOM" << endl;
                break;                
            } else if (c!='0') {
                cout << "Breaking because of precondition fail on line " << __LINE__ << endl;
                inspect_stream(is);
                break;
            }
            is.ignore(); // fast-forward to the record type
            string str;
            is >> str; // read one word
    
            if (str.compare("FAM")||str.compare("INDI")) {
                // all is well in zion
                shared_ptr<Record> r(new Record());
                r->setType(str);
          
                is >> *r;
                ged.records->push_back(r);
                ++records;
          
#ifdef DEBUG
                if (r->validate_parse()) {
                    cout << "[[ WIN ]] Record No. " << records << " Parsed Successfully ";
                    cout << (double)is.tellg()/(double)length*100.0f << "% of the way done\r";
                    r->clearRaw();
                } else {
                    cout << endl << "[[ FAIL ]] Record No. " << ged.records->size() << " Didn't Parse Right" << endl;
                    r->output_debug_info(cout);
                    fail("Crap, a parse failed.", is);
                }
#endif
            } else {
                // all is not well in zion, yea, zion doth not prosper.
                fail("Record found which is not of type FAM or INDI", is);
            }
        }
#ifdef DEBUG
        cout << endl;
#endif
    
        return is;
    }

} }

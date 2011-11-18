/**
 * Gedcom.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Gedcom.hpp"

#include "Util.hpp"

// the parser is proven up until this record:
#define PARSE_SUCCESS_UNTIL 16431

namespace FamilySearch { namespace GEDCOM {
  
    Gedcom::Gedcom(): records(new std::vector<boost::shared_ptr<Record> >()) { }
  
    std::vector<boost::shared_ptr<Record> >& Gedcom::getRecords() { return *records; }
  
    std::istream& operator>> (std::istream &is, Gedcom &ged) {
        std::istream::pos_type tmp = is.tellg();
        is.seekg(0, std::istream::end);
        std::istream::pos_type length = is.tellg();
        is.seekg(tmp);
        size_t records = 0;
        
        while (is.good()) {
            std::ios::pos_type loc = is.tellg();
            char c = is.get();
            if (!is.good()) {
                std::cout << "End of GEDCOM" << std::endl;
                break;                
            } else if (c!='0') {
                std::cout << "Breaking because of precondition fail on line " << __LINE__ << std::endl;
                inspect_stream(is);
                break;
            }
            is.ignore(); // fast-forward to the record type
            std::string str;
            is >> str; // read one word
    
            if (str.compare("FAM")||str.compare("INDI")) {
                // all is well in zion
                boost::shared_ptr<Record> r(new Record());
                r->setType(str);
          
                is >> *r;
                ged.records->push_back(r);
                ++records;
          
#ifdef DEBUG
                if (r->validate_parse()) {
                    std::cout << "[[ WIN ]] Record No. " << records << " Parsed Successfully ";
                    std::cout << (double)is.tellg()/(double)length*100.0f << "% of the way done\r";
                    r->clearRaw();
                } else {
                    std::cout << std::endl << "[[ FAIL ]] Record No. " << ged.records->size() << " Didn't Parse Right" << std::endl;
                    r->output_debug_info(std::cout);
                    fail("Crap, a parse failed.", is);
                }
#endif
            } else {
                // all is not well in zion, yea, zion doth not prosper.
                fail("Record found which is not of type FAM or INDI", is);
            }
        }
#ifdef DEBUG
        std::cout << std::endl;
#endif
    
        return is;
    }

} }

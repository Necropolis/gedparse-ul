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
        
        while (is.good()) {
            char c = is.get();
            if (c!='0') {
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
          
#ifdef DEBUG
                if (r->validate_parse()) {
                    if (ged.records->size()%71==0) {
                        std::cout << "[[ WIN ]] Record No. " << ged.records->size() << " Parsed Successfully ";
                        std::cout << (double)is.tellg()/(double)length*100.0f << "% of the way done" << std::endl;
                    }
                } else {
                    std::cout << "[[ FAIL ]] Record No. " << ged.records->size() << " Didn't Parse Right" << std::endl;
                    r->output_debug_info(std::cout);
                    fail("Crap, a parse failed.", is);
                }
#endif
            } else {
                // all is not well in zion, yea, zion doth not prosper.
                fail("Record found which is not of type FAM or INDI", is);
            }

#ifdef DEBUG
//            if (ged.records->size()>=PARSE_SUCCESS_UNTIL) {
//                std::cout << "Hit the any key to continue, or x to die" << std::endl;
//                c=std::cin.get();
//                switch (c) {
//                    case 'x':
//                        std::cout << "Exiting..." << std::endl;
//                        return is;
//                }
//            }
#endif
        }
    
        return is;
    }

} }

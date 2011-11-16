/**
 * Gedcom.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Gedcom.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
  
    Gedcom::Gedcom()
        :records(new std::list<boost::shared_ptr<Record> >()) {
      
        }
  
    std::list<boost::shared_ptr<Record> >& Gedcom::getRecords() {
        return *records;
    }
  
    std::istream& operator>> (std::istream &is, Gedcom &ged) {
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
          
                std::cout << "Just parsed: " << std::endl;
                std::cout << *r << std::endl;
        
            } else {
                // all is not well in zion, yea, zion doth not prosper.
                std::cout << "Record found which is not of type FAM or INDI" << std::endl;
            }

            // debugging code
            std::cout << "Hit the any key to continue, or x to die" << std::endl;
            c=std::cin.get();
            switch (c) {
                case 'x':
                    std::cout << "Exiting..." << std::endl;
                    return is;
            }
            // end of debugging code
        }
    
        return is;
    }

} }

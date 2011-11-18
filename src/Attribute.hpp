/**
 * Attribute.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// mongo
#include "bson/bson.h"

#ifndef __ATTRIBUTE_HPP_
#define __ATTRIBUTE_HPP_

using namespace mongo;

namespace FamilySearch { namespace GEDCOM {
  
    /**
    * Virtual class which defines the interface which all attributes inherit from.
    */
    class Attribute {
    private:
        bool _isSet;
      
    public:
        Attribute();
        Attribute(BSONElement);
        Attribute(BSONObj);

        bool isSet();
        void set(bool);

        friend BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Attribute&);
    };
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream&, Attribute&);
  
} }

#endif

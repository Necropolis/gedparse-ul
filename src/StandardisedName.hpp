/**
 * StandardisedName.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */
 
#include "Attribute.hpp"

#ifndef __STANDARDISED_NAME_
#define __STANDARDISED_NAME_

namespace FamilySearch { namespace GEDCOM {
  
  class StandardisedName : Attribute {
    
  public:
    std::istream& operator>> (std::istream& is);
  };
  
} }

#endif

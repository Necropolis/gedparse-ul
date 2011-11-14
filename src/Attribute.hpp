/**
 * Attribute.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#import <iostream>

#ifndef __ATTRIBUTE_HPP_
#define __ATTRIBUTE_HPP_

namespace FamilySearch { namespace GEDCOM {
	
	/**
	 * Virtual class which defines the interface which all attributes inherit from.
	 */
	class Attribute {
	public:
		virtual std::istream& operator>> (std::istream& is) = 0;
		
	};
	
} }

#endif

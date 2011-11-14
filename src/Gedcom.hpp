/**
 * Gedcom.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include <iostream>

#ifndef __GEDCOM_HPP_
#define __GEDCOM_HPP_

namespace FamilySearch { namespace GEDCOM {
	
	class Gedcom {
	private:
		
	public:
		/** parse me from a stream */
		// std::istream& operator>> (std::istream& is);
		friend std::istream& operator>> (std::istream &is, Gedcom &ged);
	};
	
	
	std::istream& operator>> (std::istream &is, Gedcom &ged);
	
} }


#endif

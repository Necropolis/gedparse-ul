/**
 * Gedcom.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include <iostream>
#include <boost/scoped_ptr.hpp>

#ifndef __GEDCOM_HPP_
#define __GEDCOM_HPP_

namespace FamilySearch { namespace GEDCOM {
	class Gedcom {
	private:
		boost::scoped_ptr<std::istream> inputStream;
		
	public:
		Gedcom(std::istream& inputStream);
		
		void parse();
		
		std::istream& getInputStream();
	};
} }

#endif

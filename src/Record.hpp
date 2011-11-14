/**
 * Record.hpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include <boost/scoped_ptr.hpp>

#include "RecordType.hpp"
#include "Name.hpp"

#ifndef __RECORD_HPP_
#define __RECORD_HPP_

namespace FamilySearch { namespace GEDCOM {
	
	class Record {
	private:
		enum RecordType type;
		boost::scoped_ptr<Name> name;
		
	public:
		
		enum RecordType getType();
		void setType(enum RecordType type);
		Name& getName();
		void setName(Name& name);
		
	};
	
} }

#endif

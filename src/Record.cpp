/**
 * Record.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Record.hpp"

namespace FamilySearch { namespace GEDCOM {
	
	enum RecordType Record::getType() {
		return this->type;
	}
	void Record::setType(enum RecordType type) {
		this->type = type;
	}
	Name& Record::getName() {
		return *this->name;
	}
	void Record::setName(Name &name) {
		this->name = &name;
	}
	
} }
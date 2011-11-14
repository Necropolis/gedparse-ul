#include "Gedcom.hpp"

namespace FamilySearch { namespace GEDCOM {
	
	Gedcom::Gedcom(std::istream& inputStream) {
		this->inputStream.reset(&inputStream);
	}
	
	void Gedcom::parse() {
		// oh my, go through and do some stuffs!
	}
	
} }

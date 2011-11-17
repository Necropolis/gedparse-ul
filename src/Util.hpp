/**
 * Util.hpp - 16 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <string>
#include <iostream>
#include <vector>

#ifndef __UTIL_HPP_
#define __UTIL_HPP_

namespace FamilySearch { namespace GEDCOM {
    std::string read_until_one_of(std::istream&, char*, size_t);
    std::string trim(std::string);
    void inspect_stream(std::istream&, long long);
    void inspect_stream(std::istream&);
    void fail(const char*, std::istream&);
} }

#endif

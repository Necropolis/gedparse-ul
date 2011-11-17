/**
 * Util.cpp - 16 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {

    /* probably leaks like a seive */
    std::string read_until_one_of(std::istream& is, char* sentinels, size_t len) {
        std::istream::pos_type orig = is.tellg();
        
        std::vector<std::string> results;
        std::vector<std::istream::pos_type> result_ends;
        for (size_t i=0; i<len; ++i) {
            is.seekg(orig);
            std::string sz;
            getline(is, sz, sentinels[i]);
            results.push_back(sz);
            result_ends.push_back(is.tellg());
        }
        size_t smallest_idx = 0;
        for (size_t i=0; i<results.size(); ++i) {
            if (results[smallest_idx].length() > results[i].length()) smallest_idx = i;
        }
        is.seekg(result_ends[smallest_idx]);
        return results[smallest_idx];
    }

    std::string trim(std::string str) {
        while (str[0]==' ') str.erase(0, 1);
        while (str[str.length()-1]==' ') str.erase(str.length()-1, 1);
        return str;
    }
    
    void inspect_stream(std::istream& is, long long seek_amt) {
        std::istream::pos_type orig = is.tellg();
        if (orig<seek_amt) seek_amt = orig;
        is.seekg(-1*seek_amt, std::ios::cur);
        while (is.tellg()< orig) std::cout << (char)is.get();
        std::cout << "<<CURSOR>>";
        for (size_t i=0; i<seek_amt; ++i) std::cout << (char)is.get();
        is.seekg(orig);
        std::cout << std::endl << "Next Char: " << is.peek() << " '";
        if (is.peek()=='\r') std::cout << "\\r";
        if (is.peek()=='\n') std::cout << "\\n";
        else std::cout << (char)is.peek();
        std::cout << "'" << std::endl;
    }
    
    void inspect_stream(std::istream& is) {
        inspect_stream(is, 100);
    }
    
    void fail(const char* msg, std::istream& is) {
        std::cout << msg << std::endl;
        inspect_stream(is, 100);
        std::cout << "Hit the any key to continue, or x to die" << std::endl;
        char c=std::cin.get();
        switch (c) {
            case 'x':
                std::cout << "Exiting..." << std::endl;
                exit(1);
        }
    }

} }
/**
 * CSVOStream.hpp - 22 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

// stl
#include <iostream>
#include <fstream>

#ifndef __CSVOSTREAM_HPP_
#define __CSVOSTREAM_HPP_

using namespace std;

namespace fsdev {
    
    static class __csvrecdsep { } CSVRecordSeparator;
    static class __csvelemsep { } CSVElementSeparator;
    class CSVRecord;
        
    class CSVOStream : public basic_ofstream<char> {
    private:
        char element_separator;
        char line_separator;
        
    public:
        CSVOStream();
        CSVOStream(const char*, ios_base::openmode=ios_base::out);
        
        char getElementSeparator();
        void setElementSeparator(char);
        char getLineSeparator();
        void setLineSeparator(char);
        
        CSVOStream& operator<< (__csvrecdsep&);
        CSVOStream& operator<< (__csvelemsep&);
        
        CSVOStream& operator<< (bool);
        CSVOStream& operator<< (short);
        CSVOStream& operator<< (unsigned short);
        CSVOStream& operator<< (int);
        CSVOStream& operator<< (unsigned int);
        CSVOStream& operator<< (long);
        CSVOStream& operator<< (unsigned long);
        CSVOStream& operator<< (float);
        CSVOStream& operator<< (double);
        CSVOStream& operator<< (long double);
        CSVOStream& operator<< (const void*);
        
        CSVOStream& operator<< (streambuf*);
        
        CSVOStream& operator<< (ostream&);
        
        CSVOStream& operator<< (CSVRecord&);
    };
    
    class CSVRecord {
    public:
        /* only called once at the beginning of an emission */
        virtual void
        emitFieldHeaders(CSVOStream&)=0;
        /* called by CSVOStream& CSVOStream::operator<< (CSVRecord&) */
        virtual void
        emitData(CSVOStream&)=0;
    };
    
    CSVOStream& operator<< (CSVOStream&, char);
    CSVOStream& operator<< (CSVOStream&, signed char);
    CSVOStream& operator<< (CSVOStream&, unsigned char);
    
    CSVOStream& operator<< (CSVOStream&, const char*);
    
    void replace_all(basic_string<char>,
                     basic_string<char>,
                     basic_string<char>);
    
    CSVOStream& operator<< (CSVOStream&, basic_string<char>&);
    
}


#endif

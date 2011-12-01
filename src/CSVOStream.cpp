/**
 * CSVOStream.cpp - 22 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "CSVOStream.hpp"

namespace fsdev {
    
    CSVOStream::CSVOStream(): basic_ofstream<char>(), element_separator(','), line_separator('\n') { }
    CSVOStream::CSVOStream(const char* fname, ios_base::openmode mode): basic_ofstream<char>(fname, mode), element_separator(','), line_separator('\n') { }
    
    char CSVOStream::getElementSeparator() { return element_separator; }
    void CSVOStream::setElementSeparator(char c) { element_separator = c; }
    char CSVOStream::getLineSeparator() { return line_separator; }
    void CSVOStream::setLineSeparator(char c) { line_separator = c; }
    
    CSVOStream& CSVOStream::operator<< (__csvrecdsep&) {
        basic_ofstream<char>::seekp(-1, ios_base::cur);
        static_cast<basic_ofstream<char>&>(*this) << line_separator;
        return *this;
    }
    
    CSVOStream& CSVOStream::operator<< (__csvelemsep&) {
        static_cast<basic_ofstream<char>&>(*this) << element_separator;
        return *this;
    }
    
    CSVOStream& CSVOStream::operator<< (bool val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (short val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (unsigned short val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (int val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (unsigned int val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (long val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (unsigned long val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (float val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (double val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (long double val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (const void* val) {
        basic_ofstream<char>::operator<<(val);
        return *this << CSVElementSeparator;
    }
    
    CSVOStream& CSVOStream::operator<< (streambuf* buff) {
        // filter the stream to replace element_separator with "\element_separator" and
        // line_separator with "\line_separator"
        char* c = (char*)malloc(sizeof(char)*buff->in_avail());
        buff->sgetn(c, buff->in_avail());
        return *this << c;
    }
    
    CSVOStream& CSVOStream::operator<< (CSVRecord& record) {
        record.emitData(*this);
        return *this << CSVRecordSeparator;
    }
    
    CSVOStream& operator<< (CSVOStream& csv, char c) {
        basic_ofstream<char>& _underlying = (basic_ofstream<char>&)csv;
        if (c==csv.getLineSeparator()||c==csv.getElementSeparator()||c=='"')
            _underlying << '"';
        if (c=='"') _underlying << "\"\"";
        else _underlying << c;
        if (c==csv.getLineSeparator()||c==csv.getElementSeparator()||c=='"')
            _underlying << '"';
        return csv << CSVElementSeparator;
    }
    
    CSVOStream& operator<< (CSVOStream& csv, signed char c) {
        basic_ofstream<char>& _underlying = (basic_ofstream<char>&)csv;
        if (c==csv.getLineSeparator()||c==csv.getElementSeparator()||c=='"')
            _underlying << '"';
        if (c=='"') _underlying << "\"\"";
        else _underlying << c;
        if (c==csv.getLineSeparator()||c==csv.getElementSeparator()||c=='"')
            _underlying << '"';
        return csv << CSVElementSeparator;
    }
    
    CSVOStream& operator<< (CSVOStream& csv, unsigned char c) {
        basic_ofstream<char>& _underlying = (basic_ofstream<char>&)csv;
        if (c==csv.getLineSeparator()||c==csv.getElementSeparator()||c=='"')
            _underlying << '"';
        if (c=='"') _underlying << "\"\"";
        else _underlying << c;
        if (c==csv.getLineSeparator()||c==csv.getElementSeparator()||c=='"')
            _underlying << '"';
        return csv << CSVElementSeparator;
    }
    
    CSVOStream& operator<< (CSVOStream& csv, const char* c) {
        basic_string<char> str(c, strlen(c));
        return csv << str;
    }
    
    void replace_all(basic_string<char> haystack,
                     basic_string<char> needle,
                     basic_string<char> thread) {
        basic_string<char>::size_type i=haystack.rfind(needle);
        while (i!=basic_string<char>::npos) {
            haystack.replace(i, needle.length(), thread);
            --i;
        }
    }
    
    CSVOStream& operator<< (CSVOStream& csv, basic_string<char>& str) {
        replace_all(str, basic_string<char>("\""), basic_string<char>("\"\""));
        if (str.find("\"")!=basic_string<char>::npos||
            str.find("\n")!=basic_string<char>::npos||
            str.find(",")!=basic_string<char>::npos) {
            str.insert(str.begin(), '"');
            str.append(1, '"');
        }
        (basic_ofstream<char>&)csv << str;
        return csv << CSVElementSeparator;
    }
        
}

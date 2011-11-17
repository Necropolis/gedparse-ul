/**
 * Date.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Date.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    void setPart(std::string&, Date&);
    
    Date::Date(): day(""), month(""), year(""), Attribute() {}
    
    std::string& Date::getDay() { return day; }
    void Date::setDay(std::string day) { this->day = day; set(true); }
    std::string& Date::getMonth() { return month; }
    void Date::setMonth(std::string month) { this->month = month; set(true); }
    std::string& Date::getYear() { return year; }
    void Date::setYear(std::string year) { this->year = year; set(true); }
    
    std::ostream& operator<< (std::ostream& os, Date& date) {
        os << "DATE ";
        if (date.day!="") os << date.day << " ";
        if (date.month!="") os << date.month << " ";
        if (date.year!="") os << date.year;
        os << "\r\n";
        return os;
    }
    
    void setPart(std::string& str, Date& date) {
        // is year?
        if (isdigit(str[0])&&str.length()>2) {
            date.setYear(str);
        } else if (isalpha(str[0])) { // it's a month
            date.setMonth(str);
        } else {
            // it's a day
            date.setDay(str);
        }
    }
    
    std::istream& operator>> (std::istream& is, Date& date) {
        std::string str;
        
        is >> str;
        setPart(str, date);
        while (is.peek()==' ') is.get();
        if (is.peek()=='\r') return is;
        
        is >> str;
        setPart(str, date);
        while (is.peek()==' ') is.get();
        if (is.peek()=='\r') return is;
        
        is >> str;
        setPart(str, date);
        
        return is;
    }
    
} }
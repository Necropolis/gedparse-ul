/**
 * Date.cpp - 14 November 2011
 * (C) 2011 Chris Miller. All rights reserved.
 */

#include "Date.hpp"

#include "Util.hpp"

namespace FamilySearch { namespace GEDCOM {
    
    void setPart(string&, Date&);
    
    Date::Date(): day(""), month(""), year(""), Attribute() {}
    Date::Date(BSONElement elem): day(elem["day"].String()), month(elem["month"].String()), year(elem["year"].String()), Attribute(elem["attribute"]) { }
    Date::Date(BSONObj obj): day(obj["day"].String()), month(obj["month"].String()), year(obj["year"].String()), Attribute(obj["attribute"]) { }
    
    string& Date::getDay() { return day; }
    void Date::setDay(string day) { this->day = day; set(true); }
    string& Date::getMonth() { return month; }
    void Date::setMonth(string month) { this->month = month; set(true); }
    string& Date::getYear() { return year; }
    void Date::setYear(string year) { this->year = year; set(true); }
    
    ostream& operator<< (ostream& os, Date& date) {
        os << "DATE ";
        if (date.day!="") os << date.day << " ";
        if (date.month!="") os << date.month << " ";
        if (date.year!="") os << date.year;
        os << "\r\n";
        return os;
    }
    
    void setPart(string& str, Date& date) {
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
    
    istream& operator>> (istream& is, Date& date) {
        string str;
        
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
    
    BSONObj Date::asBSON() {
        BSONObjBuilder b;
        b   << "day"        << day
            << "month"      << month
            << "year"       << year
            << "attribute"  << (Attribute&)*this;
        return b.obj();
    }
    
    BSONObjBuilder& operator<< (BSONObjBuilderValueStream& bv, Date& date) {
        return bv << date.asBSON();
    }
    
    void Date::emitFieldHeaders(CSVOStream& csv) {
        csv << "date";
    }
    
    void Date::emitData(CSVOStream& csv) {
        string str;
        str.append(day).append(" ").append(month).append(" ").append(year);
        csv << trim(str).c_str();
    }
    
} }
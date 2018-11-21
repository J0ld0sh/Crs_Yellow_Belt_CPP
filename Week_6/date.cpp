#include "date.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>

using namespace std;

Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    month = new_month;
    day = new_day;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
            make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
};

bool operator<=(const Date &lhs, const Date &rhs) {
    return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
            make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
};

bool operator>(const Date &lhs, const Date &rhs) {
    return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
            make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
};

bool operator>=(const Date &lhs, const Date &rhs) {
    return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
            make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
};

bool operator==(const Date &lhs, const Date &rhs) {
    return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
            make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
};

bool operator!=(const Date &lhs, const Date &rhs) {
    return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
            make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
};

Date ParseDate(istream &is) {

    int year;
    is >> year;

    is.ignore();

    int month;
    is >> month;
    is.ignore();

    int day;
    is >> day;

    return {year, month, day};
};

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setw(4) << setfill('0') << date.GetYear() <<
           "-" << setw(2) << setfill('0') << date.GetMonth() <<
           "-" << setw(2) << setfill('0') << date.GetDay();
    return stream;
}
#pragma once

#include <string>
#include <stdexcept>

using namespace std;

class Date {
public:
    // конструктор выбрасывает исключение, если его аргументы некорректны
    Date(int new_year = 0, int new_month = 0, int new_day = 0);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date &lhs, const Date &rhs);

bool operator<=(const Date &lhs, const Date &rhs);

bool operator>(const Date &lhs, const Date &rhs);

bool operator>=(const Date &lhs, const Date &rhs);

bool operator==(const Date &lhs, const Date &rhs);

bool operator!=(const Date &lhs, const Date &rhs);

Date ParseDate(istream &is);

ostream &operator<<(ostream &stream, const Date &date);
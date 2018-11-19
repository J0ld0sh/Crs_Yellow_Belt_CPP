#include "W3_02_phone_number.h"
#include <algorithm>
#include <exception>
#include <stdexcept>

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}

PhoneNumber::PhoneNumber(const string &international_number) {
    if (international_number[0] != '+') {
        throw invalid_argument("");
    }
    if (count(international_number.begin(), international_number.end(), '-') < 2) {
        throw invalid_argument("");
    }
    size_t k = 1;

    for (size_t i = k; i < international_number.size(); ++i) {
        if (international_number[i] != '-') {
            country_code_.push_back(international_number[i]);
        } else {
            k = i + 1;
            break;
        }
    }
    for (size_t i = k; i < international_number.size(); ++i) {
        if (international_number[i] != '-') {
            city_code_.push_back(international_number[i]);
        } else {
            k = i + 1;
            break;
        }
    }
    for (size_t i = k; i < international_number.size(); ++i) {
        local_number_.push_back(international_number[i]);
    }
    bool ln_format = local_number_.size() == count(local_number_.begin(), local_number_.end(), '-');
    if (country_code_.size() == 0 || city_code_.size() == 0 || local_number_.size() == 0 || ln_format) {
        throw invalid_argument("");
    }

}
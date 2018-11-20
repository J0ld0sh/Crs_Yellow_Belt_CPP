#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool stringComparator(const string &lhs, string rhs) {
    ++rhs.back();
    return (rhs > lhs.substr(0, rhs.length()));
}

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix) {

    auto itLow = lower_bound(range_begin, range_end, prefix);
    auto itUpper = lower_bound(range_begin, range_end, prefix, stringComparator);

    return make_pair(itLow, itUpper);
}

int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " "
         << (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " "
         << (na_result.second - begin(sorted_strings)) << endl;


    return 0;
}
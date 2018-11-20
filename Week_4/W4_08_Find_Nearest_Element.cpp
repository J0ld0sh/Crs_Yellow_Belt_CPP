#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border) {

    if (numbers.empty()) { return end(numbers); }

    if (border >= *prev(numbers.end())) {

        return prev(numbers.end());

    } else if (border <= *numbers.begin()) {

        return numbers.begin();

    } else if (numbers.count(border) == 0) {

        if (border - *prev(numbers.lower_bound(border)) <= *numbers.lower_bound(border) - border) {
            return prev(numbers.lower_bound(border));
        } else {
            return numbers.lower_bound(border);
        };

    } else {
        return numbers.lower_bound(border);
    }

};
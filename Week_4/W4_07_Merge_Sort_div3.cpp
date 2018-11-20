#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {

    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> result(range_begin, range_end);

    auto range_middle_1 = begin(result) + result.size() / 3;
    auto range_middle_2 = range_middle_1 + (end(result) - range_middle_1) / 2;

    MergeSort(begin(result), range_middle_1);
    MergeSort(range_middle_1, range_middle_2);
    MergeSort(range_middle_2, end(result));

    vector<typename RandomIt::value_type> temp;

    merge(begin(result), range_middle_1, range_middle_1, range_middle_2, back_inserter(temp));

    merge(begin(temp), end(temp), range_middle_2, end(result), range_begin);

};
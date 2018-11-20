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

    auto range_middle = begin(result) + result.size() / 2;

    MergeSort(begin(result), range_middle);
    MergeSort(range_middle, end(result));

    merge(begin(result), range_middle, range_middle, end(result), range_begin);
};
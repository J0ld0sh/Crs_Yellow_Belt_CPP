#include <iostream>
#include <set>
#include <vector>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {

    auto it_begin = find_if(begin(elements), end(elements),
                            [border](const T &item) { return item > border; });

    return {it_begin, end(elements)};
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string &s) {
    vector<string> words;

    auto it_1 = s.begin();

    while (it_1 != s.end()) {

        auto it_2 = find(it_1, s.end(), ' ');

        words.push_back({it_1, it_2});

        if (it_2 != s.end()) {
            it_1 = it_2 + 1;
        } else {
            it_1 = it_2;
        }
    }

    return words;
}
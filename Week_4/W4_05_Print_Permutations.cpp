#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(const vector<int> &vec) {
    for (auto &v : vec) {
        cout << v << ' ';
    }
    cout << endl;
}

int main() {

    int n;
    cin >> n;

    vector<int> vec;

    for (int i = n; i >= 1; --i) {
        vec.push_back(i);
    }

    do {
        PrintVector(vec);
    } while (prev_permutation(vec.begin(), vec.end()));

    return 0;
}
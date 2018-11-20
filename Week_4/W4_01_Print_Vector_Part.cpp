#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int> &numbers) {
    auto it_end = find_if(
            begin(numbers), end(numbers),
            [](const int &num) {
                return num < 0;
            }
    );

    while (it_end != begin(numbers)) {
        --it_end;
        cout << *it_end << " ";
    }
    cout << endl;
}
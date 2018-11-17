#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<long int> temperature(n);

    for (auto &t : temperature) {
        cin >> t;
    }

    long int midArithmetic = 0;
    for (auto i : temperature) {
        midArithmetic += i;
    }
    midArithmetic /= static_cast<long int>(temperature.size());


    vector<int> day;

    for (int i = 0; i < n; ++i) {
        if (temperature[i] > midArithmetic) {
            day.push_back(i);
        }
    }

    cout << day.size() << endl;
    for (auto i : day) {
        cout << i << " ";
    }

    return 0;
}
#include <iostream>
#include <vector>


using namespace std;

int main() {

    int n;
    int r;

    cin >> n >> r;

    unsigned long int all_mass = 0;

    for (int i = 0; i < n; ++i) {
        unsigned long int w, h, d;
        cin >> w >> h >> d;
        all_mass += w * h * d * r;
    }

    cout << all_mass << "\n";

    return 0;
}
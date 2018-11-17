#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
T Sqr(T &x);

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> &p);

template<typename T>
vector<T> Sqr(vector<T> &v);

template<typename First, typename Second>
map<First, Second> Sqr(map<First, Second> &m);


template<typename T>
T Sqr(T &x) {
    return x * x;
}

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> &p) {
    First f = Sqr(p.first);
    Second s = Sqr(p.second);
    return make_pair(f, s);
}

template<typename T>
vector<T> Sqr(vector<T> &v) {
    for (auto &item : v) {
        item = Sqr(item);
    }
    return v;
}

template<typename First, typename Second>
map<First, Second> Sqr(map<First, Second> &m) {
    for (auto &item : m) {
        item.second = Sqr(item.second);
    };
    return m;
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;
    map<int, pair<int, int>> map_of_pairs = {{4, {2, 2}},
                                             {7, {4, 3}}};
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second
             << endl;
    }

    int i = 4;
    cout << Sqr(i) << endl;

    pair<int, double> p = {4, 2.25};
    p = Sqr(p);
    cout << p.first << ' ' << p.second << endl;

    return 0;
}
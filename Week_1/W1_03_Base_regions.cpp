#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

tuple<const string &, const string &, const map<Lang, string> &, const int64_t &>
GetRank(const Region &reg) {
    return tie(reg.std_name, reg.parent_std_name, reg.names, reg.population);
}

bool operator<(const Region &reg_1, const Region &reg_2) {
    if (GetRank(reg_1) < GetRank(reg_2)) {
        return true;
    }
    return false;
};

bool operator==(const Region &reg_1, const Region &reg_2) {
    if (GetRank(reg_1) == GetRank(reg_2)) {
        return true;
    }
    return false;
};

int FindMaxRepetitionCount(const vector<Region> &regions) {
    if (regions.size() == 0) {
        return 0;
    }
    set<Region> r(regions.begin(), regions.end());
    vector<int> cnt;
    for (auto i : r) {
        cnt.push_back(count(begin(regions), end(regions), i)); //counting repetitions
    }
    sort(begin(cnt), end(cnt)); //sort in ascending order
    return cnt[cnt.size() - 1]; // return max element after sorting

};

int main() {
	    
    cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;
  
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;
    
	return 0;
}
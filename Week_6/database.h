#pragma once

#include "date.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iterator>

using namespace std;

class Database {
public:

    void Add(const Date &date, const string &event);

    void Print(ostream &stream) const;

    template<class Func>
    int RemoveIf(Func predicate) {
        int count = 0;
        auto it_storage = storage.begin();
        while (it_storage != storage.end()) {
            auto it_events = stable_partition(it_storage->second.begin(), it_storage->second.end(),
                                              [&](const string str) { return !predicate(it_storage->first, str); });
            if (it_events != it_storage->second.end()) {
                count += distance(it_events, it_storage->second.end());
                it_storage->second.erase(it_events, it_storage->second.end());
                storage_Set[it_storage->first].clear();
                storage_Set[it_storage->first].insert(it_storage->second.begin(), it_storage->second.end());
            };

            if (it_storage->second.empty()) {
                storage_Set.erase(it_storage->first);
                it_storage = storage.erase(it_storage);
            } else {
                ++it_storage;
            }
        }
        return count;
    };

    template<class Func>
    vector<pair<Date, string>> FindIf(Func predicate) const {
        vector<pair<Date, string>> revealedPair;
        auto it_storage = storage.begin();
//        cout << "First===========\n";
        while (it_storage != storage.end()) {
//            cout << "Second==============\n";
            auto it_events = it_storage->second.begin();
            while (it_events != it_storage->second.end()) {
//                cout << "Third==============\n";
                it_events = find_if(it_events, it_storage->second.end(),
                                    [&](const string str) { return predicate(it_storage->first, str); });
                if (it_events != it_storage->second.end()) {
                    revealedPair.emplace_back(it_storage->first, *it_events);
                    ++it_events;
                };
            }
            ++it_storage;
        }
//        cout << "In metod FindIf. Vector size is: " << revealedPair.size() << endl;

        return revealedPair;
    };

    pair<Date, string> Last(const Date &date) const;

private:
    map<Date, vector<string>> storage;
    map<Date, set<string>> storage_Set;
};

ostream &operator<<(ostream &stream, const pair<Date, string> &p);
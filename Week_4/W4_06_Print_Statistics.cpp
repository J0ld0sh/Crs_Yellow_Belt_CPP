#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

    auto it = partition(persons.begin(), persons.end(), [](Person pr) { return pr.gender == Gender::FEMALE; });
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << endl;

    it = partition(persons.begin(), persons.end(), [](Person pr) { return pr.gender == Gender::MALE; });
    cout << "Median age for males = " << ComputeMedianAge(persons.begin(), it) << endl;

    it = partition(persons.begin(), persons.end(),
                   [](Person pr) { return ((pr.gender == Gender::FEMALE) && (pr.is_employed)); });
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it) << endl;

    it = partition(persons.begin(), persons.end(),
                   [](Person pr) { return ((pr.gender == Gender::FEMALE) && (!pr.is_employed)); });
    cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), it) << endl;

    it = partition(persons.begin(), persons.end(),
                   [](Person pr) { return ((pr.gender == Gender::MALE) && (pr.is_employed)); });
    cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), it) << endl;

    it = partition(persons.begin(), persons.end(),
                   [](Person pr) { return ((pr.gender == Gender::MALE) && (!pr.is_employed)); });
    cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), it) << endl;
};
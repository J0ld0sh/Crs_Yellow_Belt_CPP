#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Person {
public:
    void ChangeFirstName(int year, const string &first_name) {
        firstName[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name) {
        lastName[year] = last_name;
    }

    string GetFullName(int year) {
        string frName = "";
        string lsName = "";
        for (auto &item : firstName) {
            if (item.first <= year) {
                frName = item.second;
            }
        }
        for (auto &item : lastName) {
            if (item.first <= year) {
                lsName = item.second;
            }
        }
        if (frName.empty() && lsName.empty()) {
            return "Incognito";
        } else if (frName.empty()) {
            return (lsName + " with unknown first name");
        } else if (!frName.empty() && lsName.empty()) {
            return (frName + " with unknown last name");
        } else {
            return (frName + " " + lsName);
        }
    }

private:
    // приватные поля
    map<int, string> firstName;
    map<int, string> lastName;
};

void Test() {

    Person person;

    AssertEqual(person.GetFullName(1900), "Incognito");

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    AssertEqual(person.GetFullName(1910), "Incognito");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name");
    AssertEqual(person.GetFullName(1990), "Polina Sergeeva");

    person.ChangeFirstName(1970, "Appolinaria");

    AssertEqual(person.GetFullName(1969), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

    person.ChangeLastName(1968, "Volkova");

    AssertEqual(person.GetFullName(1969), "Polina Volkova");
    AssertEqual(person.GetFullName(1970), "Appolinaria Volkova");

    person.ChangeLastName(1958, "Orlova");

    AssertEqual(person.GetFullName(1910), "Incognito");
    AssertEqual(person.GetFullName(1959), "Orlova with unknown first name");
    AssertEqual(person.GetFullName(1965), "Polina Orlova");
    AssertEqual(person.GetFullName(1990), "Appolinaria Volkova");

}


int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(Test, "Test");
    return 0;
}
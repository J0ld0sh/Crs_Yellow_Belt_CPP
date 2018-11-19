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
        os << "Assertion failed: " << t << " != " << u; //<< boolalpha 
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


//========== IS Palindrom ======================
bool IsPalindrom(const string &str) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    for (size_t i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}


void TestEmptyString() {
    string str;
    Assert(IsPalindrom(str), "Empty string");
}

void TestOneSymbolString() {
    string str = "A";
    Assert(IsPalindrom(str), "One Symbol String");
    str = "c";
    Assert(IsPalindrom(str), "One Symbol String");
}

void TestIsPalindrom() {
    string str = "madam";
    Assert(IsPalindrom(str), "This is Polindrom: " + str);
    str = "  ";
    Assert(IsPalindrom(str), "This is Polindrom: " + str);
    str = "c  c";
    Assert(IsPalindrom(str), "This is Polindrom: " + str);
    str = "pot top";
    Assert(IsPalindrom(str), "This is Polindrom: " + str);
    str = "pot Q top";
    Assert(IsPalindrom(str), "This is Polindrom: " + str);
    str = " madam";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "madam ";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "m a da m";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "asdfQAfdsa";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "asdfdsab";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = " asdfdsa";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "asdfdsaqwe";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "pot Qtop";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);
    str = "               a";
    Assert(!IsPalindrom(str), "Not Polindrom: " + str);

}

int main() {
    TestRunner runner;

    // добавьте сюда свои тесты

    runner.RunTest(TestEmptyString, "TestEmptyString");
    runner.RunTest(TestOneSymbolString, "TestOneSymbolString");
    runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
    return 0;
}

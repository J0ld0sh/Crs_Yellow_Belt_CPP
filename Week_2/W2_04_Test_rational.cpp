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

//============== Class Rational =========================
class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator != 0) {
            if (numerator == 0) {
                num = 0;
                den = 1;
            } else {
                int n = Nod(numerator, denominator);
                num = numerator / n;
                den = denominator / n;
                CheckSign();
            }
        } else {
            throw invalid_argument("");
        }
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return den;
    }

private:
    int num;
    int den;

    int Nod(int a, int b) {
        a = abs(a);
        b = abs(b);
        while (a != 0 && b != 0) {
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        return (a + b);
    }

    void CheckSign() {
        if ((num < 0 && den < 0) || (num >= 0 && den < 0)) {
            num *= -1;
            den *= -1;
        }
    }
};


bool operator==(Rational rat_1, Rational rat_2) {
    return (rat_1.Numerator() == rat_2.Numerator() && rat_1.Denominator() == rat_2.Denominator());
};

bool operator!=(Rational rat_1, Rational rat_2) {
    return (rat_1.Numerator() != rat_2.Numerator() || rat_1.Denominator() != rat_2.Denominator());
};

ostream &operator<<(ostream &stream, const Rational &rat) {
    stream << rat.Numerator() << '/' << rat.Denominator();
    return stream;
}

//================= T E S T's ============================

void TestDefaultConstructor() {
    Rational rt_def;
    Rational rt_expected = {0, 1};
    AssertEqual(rt_def, rt_expected, "Default constructor");
}

void TestReductionFraction() {
    vector<Rational> rt = {{-5,  25},
                           {-3,  -9},
                           {4,   -8},
                           {125, 225}};
    vector<Rational> rt_expcted = {{-1, 5},
                                   {1,  3},
                                   {1,  -2},
                                   {5,  9}};

    for (size_t i = 0; i < rt.size(); ++i) {
        AssertEqual(rt[i].Numerator(), rt_expcted[i].Numerator(), "Numerator Reduction");
        AssertEqual(rt[i].Denominator(), rt_expcted[i].Denominator(), "Denominator Reduction");
    }
}

void TestNegativeFraction() {
    Rational rt_1 = {1, -2};
    AssertEqual(rt_1.Numerator(), -1, "Numerator Negative Fraction");
    AssertEqual(rt_1.Denominator(), 2, "Denominator Negative Fraction");
}

void TestPositiveFraction() {
    Rational rt_1 = {1, 2};
    AssertEqual(rt_1.Numerator(), 1, "Numerator Positive Fraction");
    AssertEqual(rt_1.Denominator(), 2, "Denominator Positive Fraction");
    Rational rt_2 = {-7, -9};
    AssertEqual(rt_2.Numerator(), 7, "Numerator Positive Fraction");
    AssertEqual(rt_2.Denominator(), 9, "Denominator Positive Fraction");
}

void TestZeroNumerator() {
    Rational rt_1 = {0, 10};
    AssertEqual(rt_1.Numerator(), 0, "Numerator Zero Numerator");
    AssertEqual(rt_1.Denominator(), 1, "Denomintor Zero Numerator");
    Rational rt_2 = {0, -125};
    AssertEqual(rt_2.Numerator(), 0, "Numerator Zero Numerator");
    AssertEqual(rt_2.Denominator(), 1, "Denominator Zero Numerator");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestReductionFraction, "TestReductionFraction");
    runner.RunTest(TestNegativeFraction, "TestNegativeFraction");
    runner.RunTest(TestPositiveFraction, "TestPositiveFraction");
    runner.RunTest(TestZeroNumerator, "TestZeroNumerator");

    return 0;
}
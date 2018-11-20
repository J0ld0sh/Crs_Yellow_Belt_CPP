#include <iostream>
#include <string>
#include <deque>

using namespace std;

void Brackets(deque<string> &expression, char ops, int num, bool cond) {

    string strOps;
    strOps.push_back(' ');
    strOps.push_back(ops);
    strOps.push_back(' ');

    if (!cond) {
        expression.push_front("(");
        expression.push_back(strOps);
        expression.push_back(to_string(num));
        expression.push_back(")");
    } else {
        expression.push_back(strOps);
        expression.push_back(to_string(num));
    }
}

int main() {

    int first;
    cin >> first;

    int countOps;
    cin >> countOps;

    if (countOps == 0) {
        cout << first << endl;
        return 0;
    }

    deque<string> expression;
    expression.push_back("(" + to_string(first) + ")");

    for (int i = 1; i <= countOps; ++i) {

        char ops;
        int num;
        cin >> ops >> num;

        Brackets(expression, ops, num, i == countOps);

    }

    for (auto i : expression) {
        cout << i;
    }
    cout << "\n";


    return 0;
}
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
        expression.push_back(")");
        expression.push_back(strOps);
        expression.push_back(to_string(num));
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
    expression.push_back(to_string(first));

    char prevOps;

    for (int i = 1; i <= countOps; ++i) {

        char ops;
        int num;
        cin >> ops >> num;

        if (i == 1) {
            Brackets(expression, ops, num, true);
        } else if (prevOps == '-' || prevOps == '+') {

            if (ops == '*' || ops == '/') {
                Brackets(expression, ops, num, false); //i == countOps
            } else {
                Brackets(expression, ops, num, true);
            }
        } else {
            Brackets(expression, ops, num, true);
        }

        prevOps = ops;
    }

    for (auto i : expression) {
        cout << i;
    }
    cout << "\n";


    return 0;
}
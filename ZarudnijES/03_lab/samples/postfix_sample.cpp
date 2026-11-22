#include "postfix_form.h"
#include <iostream>
#include <vector>
#include <utility>

int main() {
    try {
        string expr;
        cout << "Enter Expression: ";
        getline(cin, expr);

        TPostfixExpression pe(expr);
        cout << "Postfix: " << pe.GetPostfix() << "\n";

        vector<pair<char, double>> values;
        pe.SetOperand(values);

        cout << "Result: " << pe.Calculate(values) << "\n";
    }
    catch (const exception& e) {
        cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
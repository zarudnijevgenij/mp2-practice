#include "postfix_form.h"
#include "stack.h"
#include "string"
#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

int TPostfixExpression::Priority(char op) const {
    switch (op) {
    case '*': return 3;
    case '/': return 3;
    case '+': return 2;
    case '-': return 2;
    case ')': return 1;
    case '(': return 1;
    default: return 0;
    }
}


double TPostfixExpression::ReadValue(char name) const {
    while (true) {
        cout << "Enter value for " << name << endl;
        string line;
        if (!getline(cin, line))
            throw runtime_error("the input can't be recognized, try again");

        istringstream iss(line);
        double v;
        char extra;
        if ((iss >> v) && !(iss >> extra))
            return v;

        cout << "Enter correct value";
    }
}


bool TPostfixExpression::IsOperand(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}


bool TPostfixExpression::IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}


TPostfixExpression::TPostfixExpression(const string& expr) : infixExpr(expr) {
    TStack<char> TStack1(expr.size() + 1);
    TStack<char> TStack2(expr.size() + 1);
    int balance = 0;

    for (char c : infixExpr) {
        if (c == ' ') continue;
        else if (IsOperand(c)) TStack1.push(c);
        else if (c == '(') {
            TStack2.push(c);
            balance++;
        }
        else if (c == ')') {
            if (--balance < 0) throw std::runtime_error("Error with ()");
            while (TStack2.Top() != '(' && (!TStack2.isEmpty())) {
                TStack1.push(TStack2.Top());
                TStack2.pop();
            }
            TStack2.pop();
        }
        else if (IsOperator(c)) {
            while (!TStack2.isEmpty() && TStack2.Top() != '(' && Priority(TStack2.Top()) >= Priority(c)) {
                TStack1.push(TStack2.Top());
                TStack2.pop();
            }
            TStack2.push(c);
        }
        else throw runtime_error(string("Incorrect symbol '") + c + "'");
    }

    if (balance != 0) throw std::runtime_error("Error with ()");
    while (!TStack2.isEmpty()) {
        TStack1.push(TStack2.Top());
        TStack2.pop();
    }
    while (!TStack1.isEmpty()) {
        postfixExpr = TStack1.Top() + postfixExpr;
        TStack1.pop();
    }
    
}


void TPostfixExpression::SetOperand(vector<pair<char, double>>& operands) const {
    for (char c : postfixExpr) {
        if (!IsOperand(c)) continue;

        bool isDuplicate = false;
        for (const pair<char, double>& p : operands) {
            if (p.first == c) {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) continue;

        double val = ReadValue(c);
        operands.push_back({c,val});
    }
}


double TPostfixExpression::Calculate(const vector<pair<char, double>>& operands) const {
    if (postfixExpr.empty())
        throw runtime_error("Error: empty string");

    TStack<double> st(postfixExpr.size() + 1);

    for (char c : postfixExpr) {
        if (IsOperand(c)) {
            double val = 0.0;
            bool found = false;
            for (const std::pair<char, double>& p : operands) {
                if (p.first == c) {
                    val = p.second;
                    found = true;
                    break;
                }
            }

            if (!found)
                throw runtime_error(string("Error: operand ") + c + " has no value");
            st.push(val);
        }
        else if (IsOperator(c)) {
            if (st.isEmpty())
                throw runtime_error("Error: there isn't operands in stack");
            double b = st.Top(); st.pop();
            if (st.isEmpty())
                throw runtime_error("Error: there isn't operands in stack");
            double a = st.Top(); st.pop();

            double res = 0.0;
            switch (c) {
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/':
                if (b == 0.0)
                    throw runtime_error("Error: cannot divide by zero");
                res = a / b;
                break;
            }
            st.push(res);
        }
    }

    if (st.isEmpty())
        throw runtime_error("Error: empty result");

    double result = st.Top(); st.pop();

    if (!st.isEmpty())
        throw runtime_error("Error: steak is not empty at the end of the calculation");

    return result;

}
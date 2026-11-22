#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
class TPostfixExpression {
private:
    string infixExpr;
    string postfixExpr;

    int Priority(const char) const;
    double ReadValue(const char) const;
    static bool IsOperand(char c);
    static bool IsOperator(char c);
public:
    TPostfixExpression(const string&);
    string GetPostfix() const { return postfixExpr; }
    void SetOperand(vector<pair<char, double>>&) const;
    double Calculate(const vector<pair<char, double>>&) const;
};
#include "postfix_form.h"
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <stdexcept>

namespace {
    std::vector<std::pair<char, double>> MakeVars(
        std::initializer_list<std::pair<char, double>> list) {
        return std::vector<std::pair<char, double>>(list);
    }
}

TEST(TPostfixExpression, creates_without_throwing_on_valid_input)
{
    ASSERT_NO_THROW(TPostfixExpression expr("X+Y"));
}

TEST(TPostfixExpression, copies_expression_correctly)
{
    TPostfixExpression src("(P-Q)*R");
    TPostfixExpression copy(src);
    ASSERT_EQ("PQ-R*", copy.GetPostfix());
}

TEST(TPostfixExpression, converts_single_operand)
{
    ASSERT_EQ("X", TPostfixExpression("X").GetPostfix());
}

TEST(TPostfixExpression, converts_simple_addition)
{
    ASSERT_EQ("AB+", TPostfixExpression("A+B").GetPostfix());
}

TEST(TPostfixExpression, handles_multiplication_priority)
{
    ASSERT_EQ("ABC*+", TPostfixExpression("A+B*C").GetPostfix());
}

TEST(TPostfixExpression, handles_left_associativity)
{
    ASSERT_EQ("AB-C-", TPostfixExpression("A-B-C").GetPostfix());
}

TEST(TPostfixExpression, handles_simple_parentheses)
{
    ASSERT_EQ("AB+C*", TPostfixExpression("(A+B)*C").GetPostfix());
}

TEST(TPostfixExpression, handles_nested_parentheses)
{
    ASSERT_EQ("AB+", TPostfixExpression("((A+B))").GetPostfix());
}

TEST(TPostfixExpression, ignores_spaces)
{
    ASSERT_EQ("AB+", TPostfixExpression("     A  + B  ").GetPostfix());
}

TEST(TPostfixExpression, handles_empty_expression)
{
    ASSERT_EQ("", TPostfixExpression("").GetPostfix());
}

TEST(TPostfixExpression, throws_on_extra_closing_bracket)
{
    ASSERT_THROW(TPostfixExpression("A+B)"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_missing_closing_bracket)
{
    ASSERT_THROW(TPostfixExpression("A+(B"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_only_opening_bracket)
{
    ASSERT_THROW(TPostfixExpression("("), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_digit)
{
    ASSERT_THROW(TPostfixExpression("A+7"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_special_character)
{
    ASSERT_THROW(TPostfixExpression("A%B"), std::runtime_error);
}


TEST(TPostfixExpression, evaluates_addition)
{
    auto vars = MakeVars({ {'M', 15.0}, {'N', 5.0} });
    ASSERT_DOUBLE_EQ(20.0, TPostfixExpression("M+N").Calculate(vars));
}

TEST(TPostfixExpression, evaluates_subtraction)
{
    auto vars = MakeVars({ {'M', 15.0}, {'N', 5.0} });
    ASSERT_DOUBLE_EQ(10.0, TPostfixExpression("M-N").Calculate(vars));
}

TEST(TPostfixExpression, evaluates_multiplication)
{
    auto vars = MakeVars({ {'M', 3.0}, {'N', 4.0} });
    ASSERT_DOUBLE_EQ(12.0, TPostfixExpression("M*N").Calculate(vars));
}

TEST(TPostfixExpression, evaluates_division)
{
    auto vars = MakeVars({ {'M', 15.0}, {'N', 3.0} });
    ASSERT_DOUBLE_EQ(5.0, TPostfixExpression("M/N").Calculate(vars));
}

TEST(TPostfixExpression, evaluates_single_variable)
{
    auto vars = MakeVars({ {'Z', 5.5} });
    ASSERT_DOUBLE_EQ(5.5, TPostfixExpression("Z").Calculate(vars));
}

TEST(TPostfixExpression, respects_math_precedence)
{
    auto vars = MakeVars({ {'A', 2.0}, {'B', 3.0}, {'C', 4.0} });
    // 2 + 3 * 4 = 14
    ASSERT_DOUBLE_EQ(14.0, TPostfixExpression("A+B*C").Calculate(vars));
}

TEST(TPostfixExpression, throws_on_empty_expression_during_calculation)
{
    TPostfixExpression expr("");
    std::vector<std::pair<char, double>> vars;
    ASSERT_THROW(expr.Calculate(vars), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_division_by_zero)
{
    auto vars = MakeVars({ {'A', 10.0}, {'B', 0.0} });
    ASSERT_THROW(TPostfixExpression("A/B").Calculate(vars), std::runtime_error);
}

TEST(TPostfixExpression, throws_when_variable_is_missing)
{
    auto vars = MakeVars({ {'A', 10.0} });
    ASSERT_THROW(TPostfixExpression("A+B").Calculate(vars), std::runtime_error);
}

TEST(TPostfixExpression, throws_when_stack_underflows)
{
    ASSERT_ANY_THROW({
        TPostfixExpression expr("A+");
        auto vars = MakeVars({ {'A', 1.0} });
        expr.Calculate(vars);
        });
}

TEST(TPostfixExpression, throws_when_stack_has_leftovers)
{
    ASSERT_ANY_THROW({
        TPostfixExpression expr("AB");
        auto vars = MakeVars({ {'A', 1.0}, {'B', 2.0} });
        expr.Calculate(vars);
        });
}
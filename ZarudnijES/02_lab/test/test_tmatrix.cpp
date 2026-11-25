#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5)); 
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(m);
  EXPECT_EQ(1, m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(m);
	m[0][0] = 1;
	m1[0][0] = 2;
	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(2);
	EXPECT_EQ(2, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m[0][-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m[0][2] = 0);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 2;
	ASSERT_NO_THROW(m1 = m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 2;
	m1 = m;
	EXPECT_EQ(m.size(), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 2;
	m1 = m;
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 1;
	EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, compare_different_matrices_return_false) 
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);
	m1[0][0] = 1; 
	m2[0][0] = 2;
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_false_for_not_equal_operator) {
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);
	EXPECT_FALSE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size) // done
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 1;
	TDynamicMatrix<int> exp(2);
	exp[0][0] = m[0][0] + m1[0][0];
	EXPECT_EQ(m1 + m, exp);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 1;
	ASSERT_ANY_THROW(m1 + m);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) // done
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 1;
	TDynamicMatrix<int> exp(2);
	exp[0][0] = m[0][0] - m1[0][0];
	EXPECT_EQ(m1 - m, exp);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 1;
	TDynamicMatrix<int> m2(3);
	ASSERT_ANY_THROW(m2 = m1 - m);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar) { // done	
	const int k = 3;
	TDynamicMatrix<int> m(2), exp(2);
	m[0][0] = 2;
	exp[0][0] = m[0][0] * k;
	EXPECT_EQ(m*k, exp);
}

TEST(TDynamicMatrix, can_add_scalar_to_matrix) { // done
	const int k = 3;
	TDynamicMatrix<int> m(2), exp(2);
	m[0][0] = 2;
	exp[0][0] = m[0][0] + k; exp[0][1] = k; exp[1][0] = k;
	EXPECT_EQ(m + k, exp);
}

TEST(TDynamicMatrix, can_subtract_scalar_from_matrix) { // done
	const int k = 3;
	TDynamicMatrix<int> m(2), exp(2);
	m[0][0] = 2;
	exp[0][0] = m[0][0] - k; exp[0][1] = -k; exp[1][0] = -k;
	EXPECT_EQ(m - k, exp);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector) { // done
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2), exp(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 3;
	v[0] = 4; v[1] = 5;
	exp[0] = 14; exp[1] = 15;
	EXPECT_EQ(m * v, exp);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_of_wrong_size) {
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_of_equal_size) { // done
	TDynamicMatrix<int> m1(2), m2(2), exp(2);
	m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3;
	m2[0][0] = 4; m2[0][1] = 5; m2[1][0] = 6;
	exp[0][0] = 4; exp[0][1] = 17; exp[1][0] = 18;
	EXPECT_EQ(m1 * m2, exp);
}

TEST(TDynamicMatrix, cant_multiply_matrices_of_not_equal_size) {
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 * m2);
}
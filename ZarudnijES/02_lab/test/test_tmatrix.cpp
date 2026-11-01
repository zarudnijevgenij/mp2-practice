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
	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(2, m1[0][0]);
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
	int get_val = m[0][0];
	EXPECT_EQ(1, get_val);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m[-1][0] = 0);
	ASSERT_ANY_THROW(m[0][-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m[2][0] = 0);
	ASSERT_ANY_THROW(m[0][2] = 0);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 2;
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(1, m1[0][0]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 2;
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(2, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 2;
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(1, m1[0][0]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 1;
	EXPECT_EQ(1, m1 == m);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	EXPECT_EQ(1, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 1;
	EXPECT_EQ(0, m1 == m);
}

TEST(TDynamicMatrix, compare_different_matrices_return_false) 
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);
	m1[0][0] = 1; 
	m2[0][0] = 2;
	EXPECT_EQ(1, m1 != m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_false_for_not_equal_operator) {
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);
	EXPECT_EQ(0, m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 1;
	TDynamicMatrix<int> m2(2);
	ASSERT_NO_THROW(m2 = m1 + m);
	EXPECT_EQ(2, m2[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 1;
	TDynamicMatrix<int> m2(2);
	TDynamicMatrix<int> m3(3);
	ASSERT_ANY_THROW(m2 = m1 + m);
	ASSERT_ANY_THROW(m3 = m1 + m);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1;
	m1[0][0] = 2;
	TDynamicMatrix<int> m2(2);
	ASSERT_NO_THROW(m2 = m1 - m);
	EXPECT_EQ(1, m2[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1[0][0] = 1;
	TDynamicMatrix<int> m2(2);
	TDynamicMatrix<int> m3(3);
	ASSERT_ANY_THROW(m2 = m1 - m);
	ASSERT_ANY_THROW(m3 = m1 - m);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar) {
	TDynamicMatrix<int> m(2);
	m[0][0] = 2;
	TDynamicMatrix<int> res = m * 3;
	EXPECT_EQ(6, res[0][0]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector) {
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][1] = 3;

	TDynamicVector<int> v(2);
	v[0] = 4;
	v[1] = 5;

	TDynamicVector<int> v1(2);
	v[0] = 14; 
	v[1] = 15;

	// res[0] = 1*4 + 2*5 = 14
	// res[1] = 0*4 + 3*5 = 15
	EXPECT_EQ(v1, m * v);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_of_wrong_size) {
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_of_equal_size) {
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][1] = 3;

	m2[0][0] = 4;
	m2[0][1] = 5;
	m2[1][1] = 6;

	TDynamicMatrix<int> res = m1 * m2;
	// C[0][0] = 1*4 = 4
	// C[0][1] = 1*5 + 2*6 = 17
	// C[1][1] = 3*6 = 18
	EXPECT_EQ(4, res[0][0]);
	EXPECT_EQ(17, res[0][1]);
	EXPECT_EQ(18, res[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_of_not_equal_size) {
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 * m2);
}
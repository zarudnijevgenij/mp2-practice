#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length) 
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(v);

  EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> a(1);
  a[0] = 1;
  TDynamicVector<int> b(a);
  b[0] = 2;
  EXPECT_NE(a, b);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[-4] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE + 1] = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	ASSERT_NO_THROW(v = v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(6);
	v = v1;
	EXPECT_EQ(6, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(6);
	ASSERT_NO_THROW(v = v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(6);
	EXPECT_TRUE(v != v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	const int k = 5;
	TDynamicVector<int> v(3), exp(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	exp[0] = v[0] + k; exp[1] = v[1] + k; exp[2] = v[2] + k;
	EXPECT_EQ(v + k, exp);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	const int k = 5;
	TDynamicVector<int> v(3), exp(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	exp[0] = v[0] - k; exp[1] = v[1] - k; exp[2] = v[2] - k;
	EXPECT_EQ(v - k, exp);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector) //todo
{
	TDynamicVector<int> v(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v = v * 5;
	EXPECT_EQ(5, v[0]);
	EXPECT_EQ(10, v[1]);
	EXPECT_EQ(15, v[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) //todo
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	ASSERT_NO_THROW(v + v1); //remove
	TDynamicVector<int> v2(3);
	v2 = v + v1;
	EXPECT_EQ(2, v2[0]);
	EXPECT_EQ(4, v2[1]);
	EXPECT_EQ(6, v2[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(2);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v1[0] = 1;
	v1[1] = 2;
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)  //todo
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	v[0] = 10;
	v[1] = 20;
	v[2] = 30;
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	ASSERT_NO_THROW(v - v1); // remove
	TDynamicVector<int> v2(3);
	v2 = v - v1;
	EXPECT_EQ(9, v2[0]);
	EXPECT_EQ(18, v2[1]);
	EXPECT_EQ(27, v2[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(2);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v1[0] = 1;
	v1[1] = 2;
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	ASSERT_NO_THROW(v * v1); //remove
	int res = v * v1;
	EXPECT_EQ(14, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(2);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v1[0] = 1;
	v1[1] = 2;
	ASSERT_ANY_THROW(v * v1);
}


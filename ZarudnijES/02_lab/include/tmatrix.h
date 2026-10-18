// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size) {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be greater than zero");
      pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s) {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz) {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept: sz(v.sz), pMem(v.pMem) {
      v.pMem = nullptr;
  }

  ~TDynamicVector() {
      delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v) {
      if (this == &v) return *this;
      if (sz == v.sz) {
          std::copy(v.pMem, v.pMem + sz, pMem);
          return *this;
      }
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept {
      if (this == &v) return *this;
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      return *this;
  }

  size_t size() const noexcept { return sz; }


  // индексация
  T& operator[](size_t ind) {
      if (ind >= sz || ind < 0)
        throw out_of_range("Index out of the vector");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const {
      if (ind >= sz || ind < 0)
          throw out_of_range("Index out of the vector");
      return pMem[ind];
  }

  // индексация с контролем
  T& at(size_t ind) {
      if (ind >= sz || ind < 0)
          throw out_of_range("Index out of the vector");
      return pMem[ind];
  }
  const T& at(size_t ind) const {
      if (ind >= sz || ind < 0)
          throw out_of_range("Index out of the vector");
      return pMem[ind];
  }


  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept {
      if (sz != v.sz) return 0;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return 0;
      }
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept {
      if (*this == v) return 0;
      return 1;
  }


  // скалярные операции
  TDynamicVector operator+(T val) {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(T val) {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(T val) {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }


  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) {
      if (sz != v.sz)
          throw std::exception("size of vectors not equal");
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }
      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v) {
      if (sz != v.sz)
          throw std::exception("size of vectors not equal");
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) {
      if (sz != v.sz)
          throw std::exception("size of vectors not equal");
      T result = 0;
      for (size_t i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
      std::swap(lhs.sz, rhs.sz);
      std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v) {
      for (size_t i = 0; i < v.sz; i++)
        istr >> v.pMem[i]; 
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
      for (size_t i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << ' '; 
      return ostr;
  }
};




// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
    if ((s <= 0) || (s > MAX_MATRIX_SIZE))
        throw out_of_range("matrix size should be greater than zero");
    for (size_t i = 0; i < sz; i++) // идем по строкам
      pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T>>(m) {
      sz = m.sz;
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              pMem[i][j] = m.pMem[i][j];
          }
      }
  }
  using TDynamicVector<TDynamicVector<T>>::operator[];

  size_t size() const noexcept { return sz; }


  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
      if (sz != m.sz) return 0;
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              if (pMem[i][j] != m.pMem[i][j]) return 0;
          }      
      }
      return 1;
  }


  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) {
      TDynamicMatrix res = TDynamicMatrix(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res.pMem[i][j] = pMem[i][j] * val;
          }
      }
      return res;
  }


  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
      if (sz != v.sz)
          throw std::exception("size of matrix and vector not equal");
      TDynamicVector<T> res = TDynamicVector(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res.pMem[i] += pMem[i][j] * v.pMem[j];
          }
      }
      return res;
  }


  // матрично-матричные операции
  TDynamicMatrix operator=(const TDynamicMatrix& m) {
      if (this == &m) return *this;
      if (sz == m.sz) {
          std::copy(m.pMem, m.pMem + sz, pMem);
          return *this;
      }
      delete[] pMem;
      sz = m.sz;
      pMem = new TDynamicVector<T>[sz];
      std::copy(m.pMem, m.pMem + sz, pMem);
      return *this;
  }
  TDynamicMatrix operator=(TDynamicMatrix&& m) noexcept {
      if (this == &m) return *this;
      sz = m.sz;
      pMem = m.pMem;
      m.pMem = nullptr;
      return *this;
  }

  TDynamicMatrix operator+(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::exception("size of matrixes not equal");
      TDynamicMatrix res = TDynamicMatrix(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
          }
      }
      return res;

  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::exception("size of matrixes not equal");
      TDynamicMatrix res = TDynamicMatrix(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::exception("size of matrixes not equal");
      TDynamicMatrix res = TDynamicMatrix(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              T sum = 0;
              for (size_t k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m[k][j];
              }
              res.pMem[i][j] = sum;
          }
      }
      return res;
  }


  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              istr >> m.pMem[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              ostr << m.pMem[i][j];
              if (j + 1 < m.sz) ostr << " ";
          }
          ostr << "\n";
      }
      return ostr;
  }
};

#endif

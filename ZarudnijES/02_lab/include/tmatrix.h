// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

using namespace std;

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
      if (sz != v.sz) {
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
      }
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
      return at(ind);
  }
  const T& operator[](size_t ind) const {
      return at(ind);
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
      return (!(*this == v));
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
      pMem[i] = TDynamicVector<T>(sz - i);
  }

  TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T>>(m.sz) {
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = m.pMem[i];
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;


  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
      if (sz != m.sz) return 0;
      for (int i = 0; i < sz; i++) if (pMem[i] != m.pMem[i]) return 0;
      return 1;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept {
      return (!(*this == m));
  }


  // матрично-скалярные операции
  TDynamicMatrix<T> operator+(T val) {
      TDynamicMatrix<T> res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] + val;
      }
      return res;
  }

  TDynamicMatrix<T> operator-(T val) {
      return (*this) + (val * (-1));
  }

  TDynamicMatrix operator*(const T& val) {
      TDynamicMatrix<T> res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] * val;
      }
      return res;
  }


  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
      if (sz != v.size())
          throw std::exception("size of matrix and vector not equal");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < pMem[i].size() ; j++) {
              res[i] += pMem[i][j] * v[i+j];
          }
      }
      return res;
  }


  //// матрично-матричные операции
  //TDynamicMatrix operator=(const TDynamicMatrix& m) {
  //    if (this == &m) return *this;
  //    if (sz != m.sz) {
  //        delete[] pMem;
  //        sz = m.sz;
  //        pMem = new TDynamicVector<T>[sz];
  //    }
  //    std::copy(m.pMem, m.pMem + sz, pMem);
  //    return *this;
  //}
  //TDynamicMatrix operator=(TDynamicMatrix&& m) noexcept {
  //    if (this == &m) return *this;
  //    sz = m.sz;
  //    pMem = m.pMem;
  //    m.pMem = nullptr;
  //    return *this;
  //}
  TDynamicMatrix& operator=(const TDynamicMatrix& m) {
      if (this == &m) return *this;
      TDynamicVector<TDynamicVector<T>>::operator=(m);
      return *this;
  }
  TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept {
      if (this == &m) return *this;
      TDynamicVector<TDynamicVector<T>>::operator=(std::move(m));
      return *this;
  }

  TDynamicMatrix operator+(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::exception("size of matrixes not equal");
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] + m[i];
      }
      return res;

  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::exception("size of matrixes not equal");
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] - m[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      if (m.sz != sz) throw std::exception("Invalid argument");
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = i; j < sz; j++) {
              for (int k = i; k <= j; k++)
                  res[i][j - i] += pMem[i][k - i] * m[k][j - k];
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
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < i; j++) {
              ostr << "  "; 
          }
          ostr << v[i] << endl;
      }
      return ostr;
  }
};

#endif

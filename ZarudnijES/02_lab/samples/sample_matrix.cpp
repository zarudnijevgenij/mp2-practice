#include <iostream>
#include <stdexcept>
#include "tmatrix.h"
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "========== 1. ТЕСТИРОВАНИЕ ВЕКТОРА ==========\n";
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TDynamicVector<int> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 - v2 = " << v1 - v2 << endl;
    cout << "v1 * 2  = " << v1 * 2 << endl;

    cout << " v1 * v2 = " << (v1 * v2) << endl;


    cout << "\n========== 2. ТЕСТИРОВАНИЕ ТРЕУГОЛЬНОЙ МАТРИЦЫ ==========\n";

    TDynamicMatrix<int> m1(3);

    m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
    m1[1][0] = 4; m1[1][1] = 5;
    m1[2][0] = 6;

    TDynamicMatrix<int> m2(3);
    m2[0][0] = 1;
    m2[1][0] = 1;
    m2[2][0] = 1;

    cout << "Матрица m1:\n" << m1;
    cout << "Матрица m2 (единичная):\n" << m2;

    cout << "m1 + m2:\n" << (m1 + m2);
    cout << "m1 - m2:\n" << (m1 - m2);
    cout << "m1 * 10:\n" << (m1 * 10);

    cout << "m1 * m2 :\n" << (m1 * m2);

    TDynamicVector<int> v3(3);
    v3[0] = 1; v3[1] = 1; v3[2] = 1;
    cout << "m1 * v3 (где v3 это {1, 1, 1}):\n" << (m1 * v3);

    return 0;
}
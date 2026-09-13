#include <iostream>
using namespace std;

class Complex {
private:
	double re;
	double im;
public:
	Complex(double, double);
	Complex(const Complex&);
	Complex operator +(const Complex&);
	Complex operator -(const Complex&);
	Complex operator *(const Complex&);
	Complex operator *(double);
	bool operator ==(const Complex&);
	const Complex operator =(const Complex&);
	friend std::ostream& operator << (std::ostream& out, const Complex& complex) {
		string sign;
		if (complex.im > 0) {
			out << complex.re << " + " << complex.im << "i" << endl;
		}
		else if (complex.im == 0) {
			out << complex.re << endl;
		}
		else {
			out << complex.re << " - " << abs(complex.im) << "i" << endl;
		}
		return out;
	}
};

Complex::Complex(double re, double im) {
	this->re = re;
	this->im = im;
}
Complex::Complex(const Complex& complex) {
	this->re = complex.re;
	this->im = complex.im;
}
Complex Complex::operator +(const Complex& complex) {
	this->re += complex.re;
	this->im += complex.im;
	return *this;
}

Complex Complex::operator -(const Complex& complex) {
	this->re -= complex.re;
	this->im -= complex.im;
	return *this;
}


Complex Complex::operator *(const Complex& complex) {
	this->re = this->re * complex.re - this->im * complex.im;
	this->im = this->im * complex.re + this->re * complex.im;
	return *this;
}

Complex Complex::operator *(double digit) {
	this->re *= digit;
	this->im *= digit;
	return *this;
}

bool Complex::operator ==(const Complex& complex) {
	return ((this->re == complex.re) && (this->im == complex.im));
}

const Complex Complex:: operator =(const Complex& complex) {
	this->re = complex.re;
	this->im = complex.im;
	return *this;
}

int main() {
	Complex a = Complex(1, 2);
	Complex b = Complex(3, -8);
	Complex c = a + b;
	cout << c;
}

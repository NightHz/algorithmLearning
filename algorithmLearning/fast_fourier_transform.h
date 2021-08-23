#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
struct Complex
{
	double r;
	double i;
	Complex(double _r = 0, double _i = 0) : r(_r), i(_i) {}
	Complex(const Complex& c) = default;
	Complex& operator=(const Complex& c) = default;
	Complex operator+(const Complex& c) const { return Complex(r + c.r, i + c.i); }
	Complex& operator+=(const Complex& c) { (*this) = (*this) + c; return *this; }
	Complex operator-(const Complex& c) const { return Complex(r - c.r, i - c.i); }
	Complex operator*(const Complex& c) const { return Complex(r * c.r - i * c.i, r * c.i + i * c.r); }
	Complex& operator*=(const Complex& c) { (*this) = (*this) * c; return *this; }
};
std::ostream& operator<<(std::ostream& o, const Complex& c)
{
	o << std::fixed << std::setprecision(2) << std::showpos << c.r << c.i << std::noshowpos << "i";
	o.unsetf(std::ios_base::floatfield);
	return o;
}

static const double PI = 3.141592653589793238463;
void DFT(const Complex* a, Complex* y, int n)
{
	for (int k = 0; k < n; k++)
	{
		Complex wnk(std::cos(2 * PI * k / n), std::sin(2 * PI * k / n));
		Complex w = 1;
		y[k] = 0;
		for (int j = 0; j < n; j++)
		{
			y[k] += a[j] * w;
			w *= wnk;
		}
	}
}
void DFT_inv(const Complex* y, Complex* a, int n)
{
	for (int j = 0; j < n; j++)
	{
		Complex wnj(std::cos(2 * PI * j / n), -std::sin(2 * PI * j / n));
		Complex w = 1;
		a[j] = 0;
		for (int k = 0; k < n; k++)
		{
			a[j] += y[k] * w;
			w *= wnj;
		}
		a[j] *= 1.0 / n;
	}
}

void FFT_recursive(const Complex* a, Complex* y, int n, int a_o = 1)
{
	if (n == 1)
		y[0] = a[0];
	else
	{
		int n_half = n / 2;
		FFT_recursive(a, y, n_half, a_o * 2);
		FFT_recursive(a + a_o, y + n_half, n_half, a_o * 2);
		Complex wn(std::cos(PI / n_half), std::sin(PI / n_half));
		Complex w = 1;
		for (int k = 0; k < n_half; k++)
		{
			Complex c1 = y[k];
			Complex c2 = w * y[k + n_half];
			y[k] = c1 + c2;
			y[k + n_half] = c1 - c2;
			w *= wn;
		}
	}
}
void FFT_inv_recursive(const Complex* y, Complex* a, int n, int y_o = 1)
{
	if (n == 1)
		a[0] = y[0];
	else
	{
		int n_half = n / 2;
		FFT_inv_recursive(y, a, n_half, y_o * 2);
		FFT_inv_recursive(y + y_o, a + n_half, n_half, y_o * 2);
		Complex wn(std::cos(PI / n_half), -std::sin(PI / n_half));
		Complex w = 1;
		for (int j = 0; j < n_half; j++)
		{
			Complex c1 = a[j];
			Complex c2 = w * a[j + n_half];
			a[j] = (c1 + c2) * 0.5;
			a[j + n_half] = (c1 - c2) * 0.5;
			w *= wn;
		}
	}
}
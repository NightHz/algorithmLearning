#pragma once
#include <iostream>
#include <vector>
#include <random>
struct Number
{
public:
	static const int Base = 10;// = 1 << 15; // 进制
	int op; // 符号位
private:
	std::vector<int> a; // 每一位的数值
	void align() // 将每一位对齐到有效范围
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] >= Base || a[i] <= -Base)
			{
				if (i == a.size() - 1)
					a.push_back(0);
				a[i + 1] += a[i] / Base;
				a[i] %= Base; // align to (-Base,Base)
			}
			if (a[i] < 0)
			{
				if (i != a.size() - 1)
				{
					a[i + 1] -= 1;
					a[i] += Base; // align to [0,Base)
				}
				else // i is highest bit
				{
					op *= -1;
					for (int& ai : a)
						ai *= -1;
					align(); // re-align
					return;
				}
			}
		}
		// delete extra 0
		int n = 0;
		for (int i = (int)a.size() - 1; i >= 0; i--)
		{
			if (a[i] == 0)
				n++;
			else
				break;
		}
		if (n > 0)
			a.erase(a.end() - n, a.end());
		if (a.size() == 0)
			a.push_back(0), op = 1; // set 0
	}
public:
	Number(int n0 = 0) : op(1), a(1, n0) { align(); }
	explicit Number(std::initializer_list<int> il) : op(1), a(il) { align(); }
	Number(const Number& n) = default;
	Number(Number&& n) = default;
	Number& operator=(const Number& n) = default;
	Number& operator=(Number&& n) = default;
	int size() const { return (int)a.size(); }
	int& operator[](int i)
	{
		if (i >= size())
			a.insert(a.end(), i + 1 - size(), 0);
		return a[i];
	}
	int operator[](int i) const { return (i < size() ? a[i] : 0); }
	bool operator==(const Number& n) const
	{
		if (op != n.op)
			return false;
		if (size() != n.size())
			return false;
		for (int i = (int)size() - 1; i >= 0; i--)
			if ((*this)[i] != n[i])
				return false;
		return true;
	}
	bool operator!=(const Number& n) const { return !((*this) == n); }
	bool operator<(const Number& n) const
	{
		if (op < n.op)
			return true;
		else if (op > n.op)
			return false;
		if (size() < n.size())
			return op > 0 ? true : false;
		else if (size() > n.size())
			return op > 0 ? false : true;
		for (int i = (int)size() - 1; i >= 0; i--)
			if ((*this)[i] < n[i])
				return op > 0 ? true : false;
			else if ((*this)[i] > n[i])
				return op > 0 ? false : true;
		return false;
	}
	bool operator>=(const Number& n) const { return !((*this) < n); }
	bool operator<=(const Number& n) const
	{
		if (op < n.op)
			return true;
		else if (op > n.op)
			return false;
		if (size() < n.size())
			return op > 0 ? true : false;
		else if (size() > n.size())
			return op > 0 ? false : true;
		for (int i = (int)size() - 1; i >= 0; i--)
			if ((*this)[i] < n[i])
				return op > 0 ? true : false;
			else if ((*this)[i] > n[i])
				return op > 0 ? false : true;
		return true;
	}
	bool operator>(const Number& n) const { return !((*this) <= n); }
	Number& operator+=(const Number& n)
	{
		int sz = size() >= n.size() ? size() : n.size();
		if (op * n.op > 0)
			for (int i = 0; i < sz; i++)
				(*this)[i] += n[i];
		else
			for (int i = 0; i < sz; i++)
				(*this)[i] -= n[i];
		align();
		return *this;
	}
	Number operator+(const Number& n) const { Number r = *this; r += n; return r; }
	Number& operator-=(const Number& n)
	{
		int sz = size() >= n.size() ? size() : n.size();
		if (op * n.op > 0)
			for (int i = 0; i < sz; i++)
				(*this)[i] -= n[i];
		else
			for (int i = 0; i < sz; i++)
				(*this)[i] += n[i];
		align();
		return *this;
	}
	Number operator-(const Number& n) const { Number r = *this; r -= n; return r; }
	Number operator<<(int i) const
	{
		Number r = *this;
		r.a.insert(r.a.begin(), i, 0);
		r.align();
		return r;
	}
	Number operator>>(int i) const
	{
		Number r = *this;
		i = (i < r.size() ? i : r.size());
		r.a.erase(r.a.begin(), r.a.begin() + i);
		r.align();
		return r;
	}
	Number& operator*=(int n0)
	{
		if (n0 < 0)
			op *= -1, n0 *= -1;
		if (n0 < Base)
		{
			for (int i = 0; i < size(); i++)
				(*this)[i] *= n0;
			align();
		}
		else
			(*this) *= Number(n0);
		return *this;
	}
	Number operator*(int n0) const { Number r = *this; r *= n0; return r; }
	Number operator*(const Number& n) const
	{
		Number r;
		for (int i = 0; i < n.size(); i++)
			r += (((*this) * n[i]) << i);
		if (n.op < 0 && r!=0)
			r.op *= -1;
		return r;
	}
	Number& operator*=(const Number& n) { (*this) = (*this) * n; return *this; }
	Number operator/(const Number& n) const
	{
		if (n.size() == 1 && n[0] == 0) // error: divide by 0
			return 0;
		if (size() == 1 && (*this)[0] == 0)
			return 0;
		Number r;
		Number remainder = (*this);
		remainder.op = 1;
		int bits = size() - n.size();
		for (; bits >= 0; bits--)
		{
			Number div = n << bits;
			div.op = 1;
			int r0 = 0;
			while (remainder >= div)
			{
				remainder -= div;
				r0++;
			}
			r += Number(r0) << bits;
		}
		if (op * n.op < 0 && r > 0)
			r.op = -1;
		return r;
	}
	Number& operator/=(const Number& n) { (*this) = (*this) / n; return *this; }
	Number operator%(const Number& n) const
	{
		if (n.size() == 1 && n[0] == 0) // error: divide by 0
			return 0;
		if (size() == 1 && (*this)[0] == 0)
			return n;
		int bits = size() - n.size();
		Number remainder = (*this);
		remainder.op = 1;
		for (; bits >= 0; bits--)
		{
			Number div = n << bits;
			div.op = 1;
			int r0 = 0;
			while (remainder >= div)
			{
				remainder -= div;
				r0++;
			}
		}
		if (op < 0 && remainder > 0)
			remainder.op = -1;
		return remainder;
	}
	Number& operator%=(const Number& n) { (*this) = (*this) % n; return *this; }
};
Number operator*(int n0, const Number& n) { Number r = n; r *= n0; return r; }
std::ostream& operator<<(std::ostream& o, const Number& n)
{
	o << "" << (n.op > 0 ? "" : "-");
	for (int i = (int)n.size() - 1; i >= 0; i--)
		o << "" << n[i];
	o << "";
	return o;
}

Number gcd(Number n1, Number n2)
{
	n1.op = n2.op = 1;
	while (true)
	{
		if (n1 != 0)
			n2 %= n1;
		else
			return n2;
		if (n2 != 0)
			n1 %= n2;
		else
			return n1;
	}
}

Number extended_euclid(Number n1, Number n2, Number& a, Number& b)
{
	if (n1.op < 0 || n2.op < 0 || n1 > n2)
	{
		int n1_op = n1.op;
		n1.op = 1;
		int n2_op = n2.op;
		n2.op = 1;
		Number d;
		if (n1 <= n2)
			d = extended_euclid(n1, n2, a, b);
		else
			d = extended_euclid(n2, n1, b, a);
		a.op *= n1_op;
		b.op *= n2_op;
		return d;
	}
	a = b = 0;
	if (n1 == 0)
	{
		a = 0;
		b = 1;
		return n2;
	}
	else
	{
		Number d = extended_euclid(n2 % n1, n1, b, a);
		a -= b * (n2 / n1);
		return d;
	}
}

Number modular_div(const Number& n1, const Number& n2, Number mod)
{
	mod.op = 1;
	Number a, b;
	Number d = extended_euclid(n2, mod, a, b);
	if (n1 % d == 0)
	{
		Number r = (n1 / d * a) % mod;
		if (a.op * n2.op < 0)
			if (r.op < 0)
				r += mod;
			else
				r -= mod;
		return r;
	}
	else
		return 0;
}

Number chinese_remainder(Number* mods, Number* remainders, int n)
{
	Number mod = 1;
	for (int i = 0; i < n; i++)
		mod *= mods[i];
	Number r = 0;
	for (int i = 0; i < n; i++)
	{
		Number m = mod / mods[i];
		r = (r + remainders[i] * m * modular_div(1, m, mods[i])) % mod;
	}
	return r;
}

Number modular_power(const Number& a, const Number& p, const Number& mod)
{
	Number r = 1;
	for (int i = p.size() - 1; i >= 0; i--)
	{
		Number r0 = r;
		for (int j = 9; j > 0; j--)
			r = (r * r0) % mod;
		for (int j = p[i]; j > 0; j--)
			r = (r * a) % mod;
	}
	return r;
}

Number random_number(int size)
{
	static std::default_random_engine rand_e((unsigned int)time(0));
	static std::uniform_int_distribution<> rand0(1, 9);
	static std::uniform_int_distribution<> rand(0, 9);
	Number n;
	n[size - 1] = rand0(rand_e);
	for (int i = size - 2; i >= 0; i--)
		n[i] = rand(rand_e);
	return n;
}

bool is_prime(const Number& n, int s = 10)
{
	static auto witness = [](const Number& a, const Number& n) -> bool
	{
		if (modular_power(a, n - 1, n) != 1)
			return true;
		return false;
	};
	for (int i = 0; i < s; i++)
	{
		Number a = random_number(n.size() - 1);
		if (witness(a, n))
			return false;
	}
	return true;
}

Number generate_prime(int size) // so slow
{
	while (true)
	{
		Number p = random_number(size);
		if (is_prime(p))
			return p;
	}
}

bool RSA_create(Number& n, Number& e, Number& d, const Number& p = generate_prime(10), const Number& q = generate_prime(10))
{
	n = p * q;
	Number phi_n = (p - 1) * (q - 1);
	for (e = 1001; e < phi_n; e += 2)
		if (gcd(e, phi_n) == 1)
			break;
	if (e >= phi_n)
		return false;
	d = modular_div(1, e, phi_n);
	return true;
}

Number RSA_encrypt(const Number& msg, const Number& e, const Number& n)
{
	return modular_power(msg, e, n);
}

Number RSA_decrypt(const Number& msg, const Number& d, const Number& n)
{
	return modular_power(msg, d, n);
}
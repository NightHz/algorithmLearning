#pragma once
#include "matrix.h"
#include <iostream>
struct LPSize
{
	int equ_n;
	int var_n;
	LPSize(int _equ_n, int _var_n) : equ_n(_equ_n), var_n(_var_n) {}
};
struct LPStandard
{
public:
	const LPSize size;
	Matrix C; // z = max(CX)
	Matrix A, B; // AX<=B
	Matrix X;
	bool optimal;
	LPStandard(LPSize _size) : size(_size), C(_size.var_n, 1), A(_size.equ_n, _size.var_n), B(_size.equ_n, 1),
		X(_size.var_n, 1), optimal(false) {}
	~LPStandard() {}
	void print()
	{
		using std::cout;
		using std::endl;
		cout << "z=max("; for (int i = 0; i < size.var_n; i++) cout << (i == 0 ? "" : " + ") << C[i] << " x" << i; cout << ")" << endl;
		for (int j = 0; j < size.equ_n; j++)
		{
			for (int i = 0; i < size.var_n; i++) cout << (i == 0 ? "" : " + ") << A(j, i) << " x" << i; cout << " <= " << B[j] << endl;
		}
		for (int i = 0; i < size.var_n; i++) cout << (i == 0 ? "" : ", ") << "x" << i; cout << " >= 0" << endl;
	}
};
struct LPAugmented
{
public:
	const LPSize size;
	Matrix Base;
	double v;
	Matrix C; // z = max(v+CX)
	Matrix A, B; // X'=B-AX
	bool feasible;
	bool unbounded;
	LPAugmented(LPSize _size) : size(_size),
		Base(_size.equ_n, 1), v(0), C(_size.equ_n + _size.var_n, 1),
		A(_size.equ_n, _size.equ_n + _size.var_n), B(_size.equ_n, 1), feasible(false), unbounded(false) {}
	LPAugmented(LPStandard lp_s) : LPAugmented(lp_s.size)
	{
		for (int i = 0; i < size.equ_n; i++)
			Base[i] = i + size.var_n;
		for (int i = 0; i < size.var_n; i++)
			C[i] = lp_s.C[i];
		for (int i = 0; i < size.equ_n; i++)
			for (int j = 0; j < size.var_n; j++)
				A(i, j) = lp_s.A(i, j);
		B = lp_s.B;
	}
	~LPAugmented() {}
	void print()
	{
		using std::cout;
		using std::endl;
		cout << "z=max(" << v; for (int i = 0; i < C.rows; i++) cout << " + " << C[i] << " x" << i; cout << ")" << endl;
		for (int j = 0; j < size.equ_n; j++)
		{
			cout << "x" << Base[j] << " = " << B[j]; for (int i = 0; i < A.columns; i++) cout << " - " << A(j, i) << " x" << i; cout << endl;
		}
		for (int i = 0; i < C.rows; i++) cout << (i == 0 ? "" : ", ") << "x" << i; cout << " >= 0" << endl;
	}
};

void LP_pivot(LPAugmented& lp_a, int i_equ, int i_x) // ת��
{
	// ���÷��̵Ļ���������÷ǻ�����������
	lp_a.A(i_equ, (int)lp_a.Base[i_equ]) = 1; // ��������ϵ����1
	double xi_coef = lp_a.A(i_equ, i_x);
	lp_a.A(i_equ, i_x) = 0; // �ǻ�������ϵ����0
	lp_a.Base[i_equ] = i_x;
	for (int i = 0; i < lp_a.A.columns; i++)
		lp_a.A(i_equ, i) /= xi_coef;
	lp_a.B[i_equ] /= xi_coef;
	// �滻�������̵ķǻ�������
	for (int i = 0; i < lp_a.A.rows; i++)
	{
		xi_coef = lp_a.A(i, i_x);
		for (int j = 0; j < lp_a.A.columns; j++)
			lp_a.A(i, j) -= xi_coef * lp_a.A(i_equ, j);
		lp_a.B[i] -= xi_coef * lp_a.B[i_equ];
		lp_a.A(i, i_x) = 0;
	}
	xi_coef = lp_a.C[i_x];
	for (int j = 0; j < lp_a.A.columns; j++)
		lp_a.C[j] -= xi_coef * lp_a.A(i_equ, j);
	lp_a.v += xi_coef * lp_a.B[i_equ];
	lp_a.C[i_x] = 0;
}

// �������㷨-����
void LP_simplex_main(LPAugmented& lp_a)
{
	while (true)
	{
		// �ҵ�ϵ��Ϊ���ķǻ�������
		int i_x;
		for (i_x = 0; i_x < lp_a.C.rows; i_x++)
			if (lp_a.C[i_x] > 0) // ϵ��Ϊ��
				break;
		if (i_x == lp_a.C.rows)
		{
			lp_a.unbounded = false;
			return;
		}
		// �ҵ��������ķ���
		int i_equ = -1;
		double max_limit = 0;
		for (int i = 0; i < lp_a.A.rows; i++)
		{
			if (lp_a.A(i, i_x) > 0) // xi�ڵ�i�����̵�ϵ��>0
			{
				double limit = lp_a.B(i, 0) / lp_a.A(i, i_x); // ����xi�����ֵ
				if (i_equ == -1 || limit < max_limit)
					i_equ = i, max_limit = limit;
			}
		}
		if (i_equ == -1)
		{
			lp_a.unbounded = true;
			return;
		}
		// ת��
		LP_pivot(lp_a, i_equ, i_x);
	}
}
// �������㷨-��ʼ�ж�
LPAugmented LP_simplex_init(const LPStandard& lp_s)
{
	// ���Գ�ʼ������
	LPAugmented lp_a(lp_s);
	int i = 0;
	for (i = 0; i < lp_s.B.rows; i++)
		if (lp_s.B[i] < 0)
			break;
	if (i == lp_s.B.rows) // ��ʼ�������ǿ��е�
	{
		lp_a.feasible = true;
		return lp_a;
	}
	// ���츨�����Թ滮 z=max(-x)
	LPAugmented lp_a2(LPSize(lp_a.size.equ_n, lp_a.size.var_n + 1));
	int i_x = lp_a2.A.columns - 1;
	lp_a2.C[i_x] = -1;
	lp_a2.Base = lp_a.Base;
	lp_a2.B = lp_a.B;
	for (int j = 0; j < lp_a.size.equ_n; j++)
	{
		for (int i = 0; i < lp_a.A.columns; i++)
			lp_a2.A(j, i) = lp_a.A(j, i);
		lp_a2.A(j, i_x) = -1;
	}
	// ѡ��ֵ���Ļ��������������������л�����
	int i_equ = 0;
	double b_min = lp_a2.B[0];
	for (int j = 1; j < lp_a2.size.equ_n; j++)
		if (lp_a2.B[j] < b_min)
			i_equ=j,b_min= lp_a2.B[j];
	LP_pivot(lp_a2, i_equ, i_x);
	// ��⸨�����Թ滮
	lp_a2.feasible = true;
	LP_simplex_main(lp_a2);
	// �ø������Թ滮�������ɳ��͹�������ɳ���
	if(lp_a2.v<0)
	{
		lp_a.feasible = false;
		return lp_a;
	}
	for (int j = 0; j < lp_a2.size.equ_n; j++)
		if (lp_a2.Base[j] == i_x) // x�ǻ�����������Ҫ�������
		{
			for (int i = 0; i < lp_a2.A.columns; i++)
				if (lp_a2.A(j, i) > 0)
				{
					LP_pivot(lp_a2, j, i);
					break;
				}
			break;
		}
	for (int j = 0; j < lp_a.size.equ_n; j++) // �����ɳ���
	{
		for (int i = 0; i < lp_a.A.columns; i++)
			lp_a.A(j, i) = lp_a2.A(j, i);
	}
	lp_a.B = lp_a2.B;
	lp_a.Base = lp_a2.Base;
	for (int j = 0; j < lp_a.size.equ_n; j++)
		if (lp_a.C[(int)lp_a.Base[j]] != 0) // �滻��������
		{
			double coef = lp_a.C[(int)lp_a.Base[j]];
			lp_a.C[(int)lp_a.Base[j]] = 0;
			for (int i = 0; i < lp_a.A.columns; i++)
				lp_a.C[i] -= coef * lp_a.A(j, i);
			lp_a.v += coef * lp_a.B[j];
		}
	lp_a.feasible = true;
	return lp_a;
}
// �������㷨
LPAugmented LP_simplex(LPStandard& lp_s)
{
	LPAugmented lp_a = LP_simplex_init(lp_s);
	if (!lp_a.feasible)
	{
		lp_s.optimal = false;
		return lp_a;
	}
	LP_simplex_main(lp_a);
	if (lp_a.unbounded)
	{
		lp_s.optimal = false;
		return lp_a;
	}
	else
	{
		Matrix x(lp_a.C.rows, 1);
		for (int i = 0; i < lp_a.size.equ_n; i++)
			x[(int)lp_a.Base[i]] = lp_a.B[i];
		for (int i = 0; i < lp_s.size.var_n; i++)
			lp_s.X[i] = x[i];
		lp_s.optimal = true;
		return lp_a;
	}
}
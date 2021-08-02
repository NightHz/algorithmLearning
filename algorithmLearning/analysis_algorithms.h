#pragma once
// 分治策略：最大子数组问题
void find_maximum_subarray(const int *p, int n, int &il, int &ir, int &s)
{
	if (n <= 1)
		il = 0, ir = 0;
	else
	{
		int ln = n / 2;
		int rn = n - ln;
		int lil, lir, ls, ril, rir, rs;
		find_maximum_subarray(p, ln, lil, lir, ls);
		find_maximum_subarray(p + ln, rn, ril, rir, rs);
		// crossing mid
		int i, s2;
		for (il = ln - 1, s = p[il], i = il - 1, s2 = s; i >= 0; i--)
		{
			s2 += p[i];
			if (s2 > s)
				il = i, s = s2;
		}
		for (ir = ln, s = s + p[ir], i = ir + 1, s2 = s; i < n; i++)
		{
			s2 += p[i];
			if (s2 > s)
				ir = i, s = s2;
		}
		// judge
		if (ls >= rs && ls >= s)
			il = lil, ir = lir, s = ls;
		else if (rs >= ls && rs >= s)
			il = ril + ln, ir = rir + ln, s = rs;
	}
}

// 动态规划：切割钢条
int cut_rod_recursion(const int *p, int p_n, int n)
{
	if (p_n <= 0 || n <= 0)
		return 0;
	int q = p[0] + cut_rod_recursion(p, p_n, n - 1);
	for (int i = 1; i < p_n && i < n; i++)
	{
		int q2 = p[i] + cut_rod_recursion(p, p_n, n - i - 1);
		q = q2 > q ? q2 : q;
	}
	return q;
}
int cut_rod(const int *p, int p_n, int n)
{
	if (p_n <= 0 || n <= 0)
		return 0;
	int *r = new int[n + 1];
	r[0] = 0;
	for (int j = 1; j <= n; j++)
	{
		int q = p[0] + r[j - 1];
		for (int i = 1; i < p_n && i < j; i++)
		{
			int q2 = p[i] + r[j - i - 1];
			q = q2 > q ? q2 : q;
		}
		r[j] = q;
	}
	int q = r[n];
	delete[] r;
	return q;
}

// 动态规划：最长公共子序列(LCS)
int LCS_length_recursion(const char *p1, int p1_n, const char *p2, int p2_n)
{
	if (p1_n <= 0 || p2_n <= 0)
		return 0;
	if (p1[p1_n - 1] == p2[p2_n - 1])
		return 1 + LCS_length_recursion(p1, p1_n - 1, p2, p2_n - 1);
	else
	{
		int l1 = LCS_length_recursion(p1, p1_n - 1, p2, p2_n);
		int l2 = LCS_length_recursion(p1, p1_n, p2, p2_n - 1);
		return l2 > l1 ? l2 : l1;
	}
}
int LCS_length(const char *p1, int p1_n, const char *p2, int p2_n)
{
	if (p1_n <= 0 || p2_n <= 0)
		return 0;
	int *l = new int[(p1_n + 1)*(p2_n + 1)]{ 0 };
	for (int i = 1; i <= p1_n; i++)
		for (int j = 1; j <= p2_n; j++)
		{
			if (p1[i - 1] == p2[j - 1])
				l[(i)*(p2_n + 1) + (j)] = 1 + l[(i - 1)*(p2_n + 1) + (j - 1)];
			else
			{
				int l1 = l[(i - 1)*(p2_n + 1) + (j)];
				int l2 = l[(i)*(p2_n + 1) + (j - 1)];
				l[(i)*(p2_n + 1) + (j)] = l2 > l1 ? l2 : l1;
			}
		}
	return l[(p1_n + 1)*(p2_n + 1) - 1];
}

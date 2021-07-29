#pragma once
// 插入排序
template <typename T>
void sort_insertion(T *p, int n)
{
	for (int i = 1; i < n; i++)
	{
		T key = p[i];
		int j;
		for (j = i - 1; j >= 0 && key < p[j]; j--)
			p[j + 1] = p[j];
		p[j + 1] = key;
	}
}

// 归并排序
template <typename T>
void sort_merge(T *p, int n)
{
	if (n > 1)
	{
		int nl = n / 2;
		int nr = n - nl;
		sort_merge(p, nl);
		sort_merge(p + nl, nr);
		// merge
		int *l = new T[nl];
		int *r = new T[nr];
		for (int i = 0; i < nl; i++)
			l[i] = p[i];
		for (int i = 0; i < nr; i++)
			r[i] = p[nl + i];
		for (int i = 0, il = 0, ir = 0; i < n; i++)
		{
			if (il >= nl)
			{
				p[i] = r[ir];
				ir++;
			}
			else if (ir >= nr || !(r[ir] < l[il]))
			{
				p[i] = l[il];
				il++;
			}
			else
			{
				p[i] = r[ir];
				ir++;
			}
		}
		delete[] l;
		delete[] r;
	}
}

// 快速排序
template <typename T>
void sort_quick(T *p, int n)
{
	if (n > 1)
	{
		T mid = p[n - 1];
		//int random_i = rand() % n;
		//mid = p[random_i];
		//p[random_i] = p[n - 1];
		int i, j;
		for (i = 0, j = 0; j < n - 1;)
		{
			if (mid < p[j])
				j++;
			else
			{
				T t = p[i];
				p[i] = p[j];
				p[j] = t;
				i++, j++;
			}
		}
		p[n - 1] = p[i];
		p[i] = mid;
		sort_quick(p, i);
		sort_quick(p + i + 1, n - i - 1);
	}
}

// 计数排序
template <typename T, typename F = int (*)(T)>
void sort_counting(T *p, int n, int min, int max, F f = [](T t) -> int {return (int)t; })
{
	T *p2 = new T[n];
	for (int i = 0; i < n; i++)
		p2[i] = p[i];
	int k = max - min + 1;
	int *count = new int[k] { 0 };
	for (int i = 0; i < n; i++)
		count[f(p[i]) - min]++;
	for (int i = 0; i < k - 1; i++)
		count[i + 1] += count[i];
	for (int i = n - 1; i >= 0; i--)
		p[--count[f(p2[i]) - min]] = p2[i];
	delete[] p2;
	delete[] count;
}

// 基数排序
template <typename T, typename F = int(*)(T)>
void sort_radix(T *p, int n, int hex_digit_n, F f = [](T t) -> int {return (int)t; })
{
	for (int i = 0; i < hex_digit_n; i++)
		sort_counting(p, n, 0, 15, [i, f](T e) -> int { return (f(e) >> (i << 2)) & 0xf; });
}

// 桶排序
template <typename T, typename F = double(*)(T)>
void sort_bucket(T *p, int n, F f = [](T t) -> double {return (double)t; })
{
	T *p2 = new T[n];
	for (int i = 0; i < n; i++)
		p2[i] = p[i];
	int *count = new int[n] { 0 };
	for (int i = 0; i < n; i++)
		count[(int)(f(p[i]) * n)]++;
	for (int i = 0; i < n - 1; i++)
		count[i + 1] += count[i];
	for (int i = n - 1; i >= 0; i--)
		p[--count[(int)(f(p2[i]) * n)]] = p2[i];
	for (int i = 0; i < n - 1; i++)
		if (count[i + 1] - count[i] >= 2)
			sort_insertion(p + count[i], count[i + 1] - count[i]);
	delete[] p2;
	delete[] count;
}

// 一般选择
template <typename T>
T select_Xth(T *p, int n, int x)
{
	if (n == 1)
		return p[0];
	else
	{
		T mid = p[n - 1];
		//int random_i = rand() % n;
		//mid = p[random_i];
		//p[random_i] = p[n - 1];
		int i, j;
		for (i = 0, j = 0; j < n - 1;)
		{
			if (mid < p[j])
				j++;
			else
			{
				T t = p[i];
				p[i] = p[j];
				p[j] = t;
				i++, j++;
			}
		}
		p[n - 1] = p[i];
		p[i] = mid;
		if (x == i + 1)
			return mid;
		else if (x < i + 1)
			return select_Xth(p, i, x);
		else
			return select_Xth(p + i + 1, n - i - 1, x - i - 1);
	}
}

// 一般选择v2
double select_Xth_v2(double *p, int n, int x)
{
	if (n == 1)
		return p[0];
	else
	{
		// step 1 分成5组
		int group_n = (n + 4) / 5;
		double *p2 = new double[group_n];
		// step 2 各自排序取中位数
		int i;
		for (i = 0; i < n - 5; i += 5)
		{
			sort_insertion(p + i, 5);
			p2[i / 5] = (p + i)[2];
		}
		sort_insertion(p + i, n - i);
		p2[i / 5] = (p + i)[(n - i - 1) / 2];
		// step 3 递归求中位数的中位数
		double mid = select_Xth_v2(p2, group_n, (group_n + 1) / 2);
		// step 4 以新中位数为界，划分数组
		for (i = 0; i < n; i++)
			if (p[i] == mid)
			{
				p[i] = p[n - 1];
				break;
			}
		int j;
		for (i = 0, j = 0; j < n - 1;)
		{
			if (mid < p[j])
				j++;
			else
			{
				double t = p[i];
				p[i] = p[j];
				p[j] = t;
				i++, j++;
			}
		}
		p[n - 1] = p[i];
		p[i] = mid;
		// step 5 递归求子集的中位数
		if (x == i + 1)
			return mid;
		else if (x < i + 1)
			return select_Xth_v2(p, i, x);
		else
			return select_Xth_v2(p + i + 1, n - i - 1, x - i - 1);
	}
}
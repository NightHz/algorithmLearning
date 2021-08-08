#pragma once
#include <limits>
double constexpr constexprSqrtNewtonRaphson(double x, double curr, double prev)
{
	return curr == prev
		? curr
		: constexprSqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
}
double constexpr constexprSqrt(double x)
{
	return x >= 0 && x < std::numeric_limits<double>::infinity()
		? constexprSqrtNewtonRaphson(x, x, 0)
		: std::numeric_limits<double>::quiet_NaN();
}

template <int _u>
class ProtoVEB // 原型 van Emde Boas 结构
{
private:
	static const int u = _u;
	static const int sqrtu = (int)constexprSqrt(u);
	ProtoVEB<sqrtu> summary;
	ProtoVEB<sqrtu> cluster[sqrtu];

	static int high(int x) { return x / sqrtu; }
	static int low(int x) { return x % sqrtu; }
	static int index(int h, int l) { return h * sqrtu + l; }

public:
	ProtoVEB() {}
	ProtoVEB(ProtoVEB& vEB) = delete;
	ProtoVEB& operator=(ProtoVEB& vEB) = delete;
	~ProtoVEB() {}

	bool is_member(int x)
	{
		return cluster[high(x)].is_member(low(x));
	}
	int minimum()
	{
		int min_clus = summary.minimum();
		if (min_clus >= 0)
			return index(min_clus, cluster[min_clus].minimum());
		else
			return -1;
	}
	int successor(int x)
	{
		int low_succ = cluster[high(x)].successor(low(x));
		if (low_succ >= 0)
			return index(high(x), low_succ);
		int succ_clus = summary.successor(high(x));
		if (succ_clus >= 0)
			return index(succ_clus, cluster[succ_clus].minimum());
		else
			return -1;
	}
	void insert(int x)
	{
		cluster[high(x)].insert(low(x));
		summary.insert(high(x));
	}
	void remove(int x)
	{
		cluster[high(x)].remove(low(x));
		summary.remove(high(x));
	}
};
template <>
class ProtoVEB<2>
{
private:
	static const int u = 2;
	unsigned short a[2];
public:
	ProtoVEB() : a{ 0,0 } {}
	ProtoVEB(ProtoVEB& vEB) = delete;
	ProtoVEB& operator=(ProtoVEB& vEB) = delete;
	~ProtoVEB() {}
	bool is_member(int x) { return a[x] != 0; }
	int minimum() { if (a[0] != 0) return 0; else if (a[1] != 0) return 1; else return -1; }
	int successor(int x) { if (x == 0 && a[1] != 0) return 1; else return -1; }
	void insert(int x) { a[x]++; }
	void remove(int x) { if (a[x] != 0) a[x]--; }
};
template <> class ProtoVEB<3> { ProtoVEB() = delete; };



template <int _u>
class VEBTree // van Emde Boas 树
{
private:
	static const int u = _u;
	static const int sqrtu = (int)constexprSqrt(u);
	static const int clus_size = sqrtu >= 2 ? sqrtu : 2;
	static const int clus_numb = (u - 1) / clus_size + 1;
	VEBTree<clus_numb> summary; // 只进行一次insert
	VEBTree<clus_size> cluster[clus_numb]; // 允许多次insert
	int min; // min不存入cluster[] 作为优先缓存
	int max;

	static int high(int x) { return x / clus_size; }
	static int low(int x) { return x % clus_size; }
	static int index(int h, int l) { return h * clus_size + l; }

public:
	VEBTree() :min(-1), max(-1) {}
	VEBTree(VEBTree& vEB) = delete;
	VEBTree& operator=(VEBTree& vEB) = delete;
	~VEBTree() {}

	bool is_empty() { return min == -1; }
	bool is_member(int x)
	{
		if (x == min || x == max) return true;
		else return cluster[high(x)].is_member(low(x));
	}
	int minimum() { return min; }
	int maximum() { return max; }
	int successor(int x)
	{
		if (x < min)
			return min;
		if (low(x) < cluster[high(x)].maximum()) // 对应簇含有比它大的元素
			return index(high(x), cluster[high(x)].successor(low(x)));
		int succ_clus = summary.successor(high(x));
		if (succ_clus >= 0)
			return index(succ_clus, cluster[succ_clus].minimum());
		else
			return -1;
	}
	void insert(int x)
	{
		if (is_empty())
			min = max = x;
		else if (x < min) // update min
		{
			insert(min);
			min = x;
		}
		else // insert to cluster
		{
			if (cluster[high(x)].is_empty()) // 添加了第一个元素
			{
				cluster[high(x)].insert(low(x)); // 常量时间
				summary.insert(high(x));
			}
			else
				cluster[high(x)].insert(low(x));
			if (x > max) // update max
				max = x;
		}
	}
	void remove(int x)
	{
		if (is_empty())
			return;
		if (x == min) // compute new min
		{
			int min_clus = summary.minimum();
			if (min_clus >= 0)
			{
				x = index(min_clus, cluster[min_clus].minimum()); // maybe x==min
				min = x; // update min
			}
			else // 簇中没有元素时
			{
				min = max = -1;
				return;
			}
		}
		cluster[high(x)].remove(low(x)); // remove from cluster
		if (cluster[high(x)].is_empty()) // 移除了最后一个元素
		{
			summary.remove(high(x));
			int max_clus = summary.maximum(); // update max
			if (max_clus >= 0)
				max = index(max_clus, cluster[max_clus].maximum());
			else
				max = min;
		}
		else
		{
			if (x == max) // update max
				max = index(high(x), cluster[high(x)].maximum());
		}
	}
};
template <>
class VEBTree<2> // 最底层使用计数保存，允许重复插入
{
private:
	static const int u = 2;
	char a[2];
public:
	VEBTree() : a{ 0,0 } {}
	VEBTree(VEBTree& vEB) = delete;
	VEBTree& operator=(VEBTree& vEB) = delete;
	~VEBTree() {}
	bool is_empty() { return (a[0] == 0 && a[1] == 0); }
	bool is_member(int x) { return a[x] != 0; }
	int minimum() { if (a[0] != 0) return 0; else if (a[1] != 0) return 1; else return -1; }
	int maximum() { if (a[1] != 0) return 1; else if (a[0] != 0) return 0; else return -1; }
	int successor(int x) { if (x == 0 && a[1] != 0) return 1; else return -1; }
	void insert(int x) { a[x]++; }
	void remove(int x) { if (a[x] != 0) a[x]--; }
};

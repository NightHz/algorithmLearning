#pragma once
template <typename T>
class Heap // 最小堆
{
private:
	T *p; // 存储指针
	const int max_n; // 申请的最大空间
	int n; // 当前堆大小

	inline int parent(int i) { return (i - 1) / 2; } // 父节点
	inline int left(int i) { return 2 * i + 1; } // 左侧子节点
	inline int right(int i) { return 2 * i + 2; } // 右侧子节点

	void heapify_up(int i) // 向上堆化
	{
		while (i != 0) // i不为根节点
		{
			if (p[i] < p[parent(i)]) // 当前节点小于父节点
			{
				T t = p[parent(i)]; // 交换
				p[parent(i)] = p[i];
				p[i] = t;
				i = parent(i); // 移动到父节点继续维护
			}
			else
				break; // 停止维护
		}
	}
	void heapify_down(int i) // 向下堆化
	{
		while (left(i) < n) // i存在左侧子节点
		{
			int min_i = i;
			if (p[left(i)] < p[i]) // 左侧子节点小于当前节点
				min_i = left(i);
			if (right(i) < n && p[right(i)] < p[min_i]) // 右侧子节点小于最小节点
				min_i = right(i);
			if (min_i != i) // 最小节点不为当前节点
			{
				T t = p[i]; // 交换
				p[i] = p[min_i];
				p[min_i] = t;
				i = min_i; // 移动到最小节点继续维护
			}
			else
				break; // 停止维护
		}
	}

public:
	using element_type = T;

	Heap(int max_size = 80) : max_n(max_size), p(new T[max_size]), n(0) {}
	Heap(Heap &h) = delete; // 禁止拷贝
	Heap& operator=(Heap &h) = delete;
	~Heap() { delete[] p; }

	int size() { return n; }
	int max_size() { return max_n; }
	T get_by_pos(int i) { return p[i]; }

	void clear() { n = 0; } // 清空
	void build_heap(T *es, int _n) // 建堆
	{
		if (n != 0)
			return;
		for (int i = 0; i < _n; i++)
			insert(es[i]);
	}
	void build_heap_v2(T *es, int _n) // 建堆_v2
	{
		if (n != 0)
			return;
		if (_n > max_n)
			return;
		for (int i = 0; i < _n; i++)
			p[i] = es[i];
		n = _n;
		for (int i = n - 1; i >= 0; i--)
			heapify_down(i);
	}
	void sort_to_array(T *es) // 堆排序
	{
		for (int i = 0; n > 0; i++)
			es[i] = extract_min();
	}

	void insert(T e) // 插入
	{
		if (n == max_n)
			return;
		n++;
		p[n - 1] = e;
		heapify_up(n - 1);
	}
	T extract_min() // 抽出最小
	{
		if (n == 0)
			return T();
		T e = p[0];
		p[0] = p[n - 1];
		n--;
		heapify_down(0);
		return e;
	}
};
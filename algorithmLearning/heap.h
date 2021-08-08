#pragma once
template <typename T>
class Heap // ��С��
{
private:
	T *p; // �洢ָ��
	const int max_n; // ��������ռ�
	int n; // ��ǰ�Ѵ�С

	inline int parent(int i) { return (i - 1) / 2; } // ���ڵ�
	inline int left(int i) { return 2 * i + 1; } // ����ӽڵ�
	inline int right(int i) { return 2 * i + 2; } // �Ҳ��ӽڵ�

	void heapify_up(int i) // ���϶ѻ�
	{
		while (i != 0) // i��Ϊ���ڵ�
		{
			if (p[i] < p[parent(i)]) // ��ǰ�ڵ�С�ڸ��ڵ�
			{
				T t = p[parent(i)]; // ����
				p[parent(i)] = p[i];
				p[i] = t;
				i = parent(i); // �ƶ������ڵ����ά��
			}
			else
				break; // ֹͣά��
		}
	}
	void heapify_down(int i) // ���¶ѻ�
	{
		while (left(i) < n) // i��������ӽڵ�
		{
			int min_i = i;
			if (p[left(i)] < p[i]) // ����ӽڵ�С�ڵ�ǰ�ڵ�
				min_i = left(i);
			if (right(i) < n && p[right(i)] < p[min_i]) // �Ҳ��ӽڵ�С����С�ڵ�
				min_i = right(i);
			if (min_i != i) // ��С�ڵ㲻Ϊ��ǰ�ڵ�
			{
				T t = p[i]; // ����
				p[i] = p[min_i];
				p[min_i] = t;
				i = min_i; // �ƶ�����С�ڵ����ά��
			}
			else
				break; // ֹͣά��
		}
	}

public:
	using element_type = T;

	Heap(int max_size = 80) : max_n(max_size), p(new T[max_size]), n(0) {}
	Heap(Heap &h) = delete; // ��ֹ����
	Heap& operator=(Heap &h) = delete;
	~Heap() { delete[] p; }

	int size() { return n; }
	int max_size() { return max_n; }
	T get_by_pos(int i) { return p[i]; }

	void clear() { n = 0; } // ���
	void build_heap(T *es, int _n) // ����
	{
		if (n != 0)
			return;
		for (int i = 0; i < _n; i++)
			insert(es[i]);
	}
	void build_heap_v2(T *es, int _n) // ����_v2
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
	void sort_to_array(T *es) // ������
	{
		for (int i = 0; n > 0; i++)
			es[i] = extract_min();
	}

	void insert(T e) // ����
	{
		if (n == max_n)
			return;
		n++;
		p[n - 1] = e;
		heapify_up(n - 1);
	}
	T extract_min() // �����С
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
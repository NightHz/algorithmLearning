#pragma once
class Stack // ջ
{
private:
	double *p; // �洢ָ��
	const int max_n; // ��������ռ�
	int top; // ��ǰջ��

public:
	using element_type = double;

	Stack(int max_size = 80) : max_n(max_size), p(new double[max_size]), top(0) {}
	Stack(Stack &s) = delete; // ��ֹ����
	Stack& operator=(Stack &s) = delete;
	~Stack() { delete[] p; }

	int size() { return top; }
	int max_size() { return max_n; }
	void clear() { top = 0; }

	void push(double d) // ѹ��
	{
		if (top == max_n)
			return;
		p[top++] = d;
	}
	double pop() // ����
	{
		if (top == 0)
			return double();
		return p[--top];
	}
};

template <typename T = double>
class Queue // ����
{
private:
	T* p; // �洢ָ��
	const int max_n; // ��������ռ�
	int head; // ��ͷ
	int tail; // ��β
	bool is_full; // �Ƿ�Ϊ������

public:
	using element_type = T;

	Queue(int max_size = 80) : max_n(max_size), p(new T[max_size]), head(0), tail(0), is_full(false) {}
	Queue(Queue &q) = delete; // ��ֹ����
	Queue& operator=(Queue &q) = delete;
	~Queue() { delete[] p; }

	int size() { return is_full ? max_n : (tail - head + max_n) % max_n; }
	int max_size() { return max_n; }
	void clear() { tail = head; is_full = false; }

	void enqueue(T d) // ���
	{
		if (is_full)
			return;
		p[tail++] = d;
		tail %= max_n;
		is_full = (tail == head ? true : false);
	}
	T dequeue() // ����
	{
		if (!is_full && tail == head)
			return T();
		T result = p[head];
		head++;
		head %= max_n;
		is_full = false;
		return result;
	}
};

class LinkedList // ����
{
private:
	struct Unit
	{
		int key; // �ؼ���
		double value; // Ԫ�ص�ֵ
		Unit* prev; // ǰһ����Ԫ
		Unit* next; // ��һ����Ԫ
	};
	Unit *nil; // �ڱ�

public:
	using key_type = int;
	using element_type = double;

	LinkedList() : nil(new Unit()) { nil->prev = nil->next = nil; }
	LinkedList(LinkedList &l) = delete; // ��ֹ����
	LinkedList& operator=(LinkedList &l) = delete;
	~LinkedList() { clear(); delete nil; }

	double operator[](int k) { return search(k); }
	void clear() { while (nil->next != nil) remove(nil->next->key); }

	double search(int k) // ����
	{
		for (Unit *p = nil->next; p != nil; p = p->next)
			if (p->key == k)
				return p->value;
		return double();
	}
	void insert(int k, double e) // ����
	{
		Unit *p = new Unit();
		p->key = k;
		p->value = e;
		p->prev = nil->prev;
		p->next = nil;
		p->prev->next = p;
		p->next->prev = p;
	}
	double remove(int k) // ɾ��
	{
		for (Unit *p = nil->next; p != nil; p = p->next)
			if (p->key == k)
			{
				p->prev->next = p->next;
				p->next->prev = p->prev;
				double result = p->value;
				delete p;
				return result;
			}
		return double();
	}
};
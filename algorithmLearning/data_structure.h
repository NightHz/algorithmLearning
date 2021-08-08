#pragma once
class Stack // 栈
{
private:
	double *p; // 存储指针
	const int max_n; // 申请的最大空间
	int top; // 当前栈顶

public:
	using element_type = double;

	Stack(int max_size = 80) : max_n(max_size), p(new double[max_size]), top(0) {}
	Stack(Stack &s) = delete; // 禁止拷贝
	Stack& operator=(Stack &s) = delete;
	~Stack() { delete[] p; }

	int size() { return top; }
	int max_size() { return max_n; }
	void clear() { top = 0; }

	void push(double d) // 压入
	{
		if (top == max_n)
			return;
		p[top++] = d;
	}
	double pop() // 弹出
	{
		if (top == 0)
			return double();
		return p[--top];
	}
};

template <typename T = double>
class Queue // 队列
{
private:
	T* p; // 存储指针
	const int max_n; // 申请的最大空间
	int head; // 队头
	int tail; // 队尾
	bool is_full; // 是否为满队列

public:
	using element_type = T;

	Queue(int max_size = 80) : max_n(max_size), p(new T[max_size]), head(0), tail(0), is_full(false) {}
	Queue(Queue &q) = delete; // 禁止拷贝
	Queue& operator=(Queue &q) = delete;
	~Queue() { delete[] p; }

	int size() { return is_full ? max_n : (tail - head + max_n) % max_n; }
	int max_size() { return max_n; }
	void clear() { tail = head; is_full = false; }

	void enqueue(T d) // 入队
	{
		if (is_full)
			return;
		p[tail++] = d;
		tail %= max_n;
		is_full = (tail == head ? true : false);
	}
	T dequeue() // 出队
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

class LinkedList // 链表
{
private:
	struct Unit
	{
		int key; // 关键字
		double value; // 元素的值
		Unit* prev; // 前一个单元
		Unit* next; // 后一个单元
	};
	Unit *nil; // 哨兵

public:
	using key_type = int;
	using element_type = double;

	LinkedList() : nil(new Unit()) { nil->prev = nil->next = nil; }
	LinkedList(LinkedList &l) = delete; // 禁止拷贝
	LinkedList& operator=(LinkedList &l) = delete;
	~LinkedList() { clear(); delete nil; }

	double operator[](int k) { return search(k); }
	void clear() { while (nil->next != nil) remove(nil->next->key); }

	double search(int k) // 搜索
	{
		for (Unit *p = nil->next; p != nil; p = p->next)
			if (p->key == k)
				return p->value;
		return double();
	}
	void insert(int k, double e) // 插入
	{
		Unit *p = new Unit();
		p->key = k;
		p->value = e;
		p->prev = nil->prev;
		p->next = nil;
		p->prev->next = p;
		p->next->prev = p;
	}
	double remove(int k) // 删除
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
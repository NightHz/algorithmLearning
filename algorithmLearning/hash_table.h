#pragma once
#include "data_structure.h"
class ChainedHashTable // 链式散列表
{
private:
	LinkedList *lists; // 链表
	const int n; // 链表数量
public:
	int hash(int k) // 散列函数
	{
		k = k < 0 ? -k : k;
		//return k % n;
		const double A = 0.6180339887;
		return (int)(((k*A) - (int)(k*A))*n);
	}

public:
	using key_type = int;
	using element_type = double;

	ChainedHashTable(int _n = 10) : lists(new LinkedList[_n]), n(_n) {}
	ChainedHashTable(ChainedHashTable &h) = delete; // 禁止拷贝
	~ChainedHashTable() { delete[] lists; }

	double operator[](int k) { return search(k); }
	void clear() { for (int i = 0; i < n; i++) lists[i].clear(); }

	double search(int k) // 搜索
	{
		return lists[hash(k)].search(k);
	}
	void insert(int k, double e) // 插入
	{
		lists[hash(k)].insert(k, e);
	}
	double remove(int k) // 删除
	{
		return lists[hash(k)].remove(k);
	}
};

class HashTable // 散列表（开放寻址法）
{
private:
	struct Unit
	{
		static const int NIL = -1;
		int key;
		double value;
	};
	Unit *table; // 表
	const int n; // 数量
public:
	int hash(int k, int i) // 散列函数
	{
		k = k < 0 ? -k : k;
		const double A = 0.6180339887;
		int hash_k = (int)(((k*A) - (int)(k*A))*n);
		int hash2_k = k % n;
		return (hash_k + i * hash2_k) % n;
	}

public:
	using key_type = int;
	using element_type = double;

	HashTable(int _n = 13) : table(new Unit[_n]), n(_n) { clear(); }
	HashTable(HashTable &h) = delete; // 禁止拷贝
	~HashTable() { delete[] table; }

	double operator[](int k) { return search(k); }
	void clear() { for (int i = 0; i < n; i++) table[i].key = Unit::NIL; }

	double search(int k) // 搜索
	{
		for (int i = 0; i < n; i++)
		{
			int j = hash(k, i);
			if (table[j].key == Unit::NIL)
				return double();
			else if (table[j].key == k)
				return table[j].value;
		}
		return double();
	}
	void insert(int k, double e) // 插入
	{
		for (int i = 0; i < n; i++)
		{
			int j = hash(k, i);
			if (table[j].key == Unit::NIL)
			{
				table[j].key = k;
				table[j].value = e;
				return;
			}
		}
	}
};
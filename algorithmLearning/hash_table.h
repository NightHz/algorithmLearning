#pragma once
#include "data_structure.h"
class ChainedHashTable // ��ʽɢ�б�
{
private:
	LinkedList *lists; // ����
	const int n; // ��������
public:
	int hash(int k) // ɢ�к���
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
	ChainedHashTable(ChainedHashTable &h) = delete; // ��ֹ����
	~ChainedHashTable() { delete[] lists; }

	double operator[](int k) { return search(k); }
	void clear() { for (int i = 0; i < n; i++) lists[i].clear(); }

	double search(int k) // ����
	{
		return lists[hash(k)].search(k);
	}
	void insert(int k, double e) // ����
	{
		lists[hash(k)].insert(k, e);
	}
	double remove(int k) // ɾ��
	{
		return lists[hash(k)].remove(k);
	}
};

class HashTable // ɢ�б�����Ѱַ����
{
private:
	struct Unit
	{
		static const int NIL = -1;
		int key;
		double value;
	};
	Unit *table; // ��
	const int n; // ����
public:
	int hash(int k, int i) // ɢ�к���
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
	HashTable(HashTable &h) = delete; // ��ֹ����
	~HashTable() { delete[] table; }

	double operator[](int k) { return search(k); }
	void clear() { for (int i = 0; i < n; i++) table[i].key = Unit::NIL; }

	double search(int k) // ����
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
	void insert(int k, double e) // ����
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
#pragma once
template <typename T>
class DisjointSet // 不相交集合
{
private:
	DisjointSet* p;
	int rank;
public:
	DisjointSet() : p(this), rank(0) {}
	DisjointSet(const DisjointSet& s) : DisjointSet() {}
	DisjointSet& operator=(const DisjointSet& s) { return *this; }
	DisjointSet* find_set()
	{
		if (p != this)
			p = p->find_set();
		return p;
	}
	static void combine(T& x, T& y)
	{
		DisjointSet* set1 = x.find_set();
		DisjointSet* set2 = y.find_set();
		if (set1->rank > set2->rank)
			set2->p = set1;
		else
		{
			set1->p = set2;
			if (set1->rank == set2->rank)
				set2->rank++;
		}
	}
};
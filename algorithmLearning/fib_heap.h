#pragma once
#include <cmath>
class FibHeap // 斐波那契堆
{
private:
public:
	struct Unit
	{
		double v;
		int k;
		Unit* parent;
		Unit* left;
		Unit* right;
		int degree; // 孩子数量
		Unit* child;
		bool mark; // 成为孩子后是否失去过孩子
	};
	Unit* root; // 根可以有兄弟
	int n; // 节点数量
private:
	void clear(Unit* u)
	{
		if (u != nullptr)
		{
			Unit* next = u;
			Unit* del;
			do
			{
				clear(next->child);
				del = next;
				next = next->right;
				delete del;
			} while (next != u);
		}
	}
	int max_degree() // 可能的最大度数 < 5log_10 n
	{
		return (int)(5 * log10(n));
	}
	void consolidate() // 链接根节点
	{
		int dn = max_degree();
		Unit** d = new Unit * [dn + 1];
		for (int i = 0; i <= dn; i++)
			d[i] = nullptr;
		Unit* u = root;
		while (true)
		{
			if (d[u->degree] == nullptr)
			{
				d[u->degree] = u;
				u = u->right;
			}
			else if (d[u->degree] == u)
				break;
			else // 找到两个同度的根节点
			{
				Unit* u2 = d[u->degree];
				if (u2->k < u->k) // 将u2换到u之后，确保不跳到前面
				{
					u2->left->right = u2->right;
					u2->right->left = u2->left;
					u2->left = u;
					u2->right = u->right;
					u2->left->right = u2;
					u2->right->left = u2;
					u = u2;
					u2 = u->left;
				}
				d[u->degree] = nullptr;
				u2->left->right = u2->right;
				u2->right->left = u2->left;
				if (u->child == nullptr)
				{
					u->child = u2;
					u2->left = u2;
					u2->right = u2;
				}
				else
				{
					u2->left = u->child->left;
					u2->right = u->child;
					u2->left->right = u2;
					u2->right->left = u2;
				}
				u2->parent = u;
				u2->mark = false;
				u->degree++;
			}
		}
		for (int i = 0; i <= dn; i++) // 更新root
		{
			if (d[i] != nullptr && d[i]->k <= root->k)
				root = d[i];
		}
		delete d;
	}
	void cut(Unit* c) // 切断孩子
	{
		Unit* p = c->parent;
		if (c->right == c)
		{
			p->child = nullptr;
			p->degree--;
		}
		else
		{
			c->right->left = c->left;
			c->left->right = c->right;
			p->child = c->right;
			p->degree--;
		}
		c->left = root->left;
		c->right = root;
		c->left->right = c;
		c->right->left = c;
		c->parent = nullptr;
		c->mark = false;
		if (p->parent != nullptr)
		{
			if (p->mark)
				cut(p); // 级联切断
			else
				p->mark = true;
		}
	}

public:
	using key_type = int;
	using element_type = double;

	FibHeap() : root(nullptr), n(0) {}
	FibHeap(FibHeap& h) = delete;
	~FibHeap() { clear(); }

	void clear() { clear(root); }

	double* insert(int key, double value) // 插入
	{
		Unit* u = new Unit;
		u->k = key;
		u->v = value;
		u->parent = nullptr;
		u->degree = 0;
		u->child = nullptr;
		u->mark = false;
		if (root == nullptr)
		{
			root = u;
			root->left = root->right = root;
		}
		else
		{
			u->left = root->left;
			u->right = root;
			u->left->right = u;
			u->right->left = u;
			if (u->k < root->k)
				root = u;
		}
		n++;
		return (double*)u;
	}
	void combine(FibHeap& h) // 合并堆
	{
		if (root == nullptr)
			root = h.root;
		else if (h.root != nullptr)
		{
			Unit* last = root->left;
			last->right = h.root;
			root->left = h.root->left;
			h.root->left->right = root;
			h.root->left = last;
			if (h.root->k < root->k)
				root = h.root;
		}
		n += h.n;
		h.root = nullptr;
		h.n = 0;
	}
	double* minimum() // 获得最小
	{
		return (double*)root;
	}
	double extract_min() // 抽出最小
	{
		if (root == nullptr)
			return double();
		else
		{
			double v = root->v;
			if (root->child != nullptr) // 将root的孩子合并到根
			{
				Unit* last = root->left;
				last->right = root->child;
				root->left = root->child->left;
				root->child->left->right = root;
				root->child->left = last;
				Unit* c = root->child;
				do
				{
					c->parent = nullptr;
					c = c->right;
				} while (c != root->child);
				root->degree = 0;
				root->child = nullptr;
			}
			if (root->right == root) // 只有root一个
			{
				delete root;
				root = nullptr;
				n--;
			}
			else // 删除root
			{
				root->left->right = root->right;
				root->right->left = root->left;
				Unit* u = root;
				root = root->right;
				delete u;
				n--;
				consolidate();
			}
			return v;
		}
	}
	void decrease_key(double* p, int new_key) // 降低关键字
	{
		Unit* u = (Unit*)p;
		if (u->k <= new_key)
			return;
		u->k = new_key;
		if (u->parent != nullptr && u->k < u->parent->k)
			cut(u); // 将u切下合并到根
		if (u->k < root->k)
			root = u;
	}
	double remove(double* p) // 删除
	{
		int key_min = root->k - 1;
		decrease_key(p, key_min);
		return extract_min();
	}
};
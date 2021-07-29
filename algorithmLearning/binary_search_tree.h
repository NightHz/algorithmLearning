#pragma once
struct DefaultBinarySearchTreeUnit
{
	double e;
	DefaultBinarySearchTreeUnit *parent;
	DefaultBinarySearchTreeUnit *left;
	DefaultBinarySearchTreeUnit *right;
};
template <typename Unit = DefaultBinarySearchTreeUnit>
class BinarySearchTree // 二叉搜索树
{
protected:
	Unit *root;
	Unit * const nil; // 哨兵

	void clear(Unit *u)
	{
		if (u != nil)
		{
			clear(u->left);
			clear(u->right);
			delete u;
			u = nil;
		}
	}
	void copy_to_array(double *&p, Unit *u)
	{
		if (u != nil)
		{
			copy_to_array(p, u->left);
			*(p++) = u->e;
			copy_to_array(p, u->right);
		}
	}
	int get_height(Unit *u)
	{
		if (u == nil)
			return 0;
		else
		{
			int h1 = get_height(u->left);
			int h2 = get_height(u->right);
			if (h1 > h2)
				return h1 + 1;
			else
				return h2 + 1;
		}
	}
	Unit* get_by_pos(int depth, int number, Unit *u) // (0,0)=u (1,0)=u->left (1,1)=u->right
	{
		if (depth <= 0 || u == nil)
			return u;
		int n = 1 << (depth - 1);
		if (number < n)
			return get_by_pos(depth - 1, number, u->left);
		else
			return get_by_pos(depth - 1, number - n, u->right);
	}

	Unit* search(double e, Unit *u) // 搜索
	{
		while (u != nil)
		{
			if (u->e == e)
				return u;
			else if (e < u->e)
				u = u->left;
			else
				u = u->right;
		}
		return nil;
	}
	Unit* minimum(Unit *u) // 最小值
	{
		if (u == nil)
			return u;
		while (u->left != nil)
			u = u->left;
		return u;
	}
	Unit* maximum(Unit *u) // 最大值
	{
		if (u == nil)
			return u;
		while (u->right != nil)
			u = u->right;
		return u;
	}
	Unit* successor(Unit *u) // 后继
	{
		if (u == nil)
			return u;
		if (u->right != nil)
			return minimum(u->right);
		for (Unit *p = u->parent; p != nil; u = p, p = u->parent)
		{
			if (u == p->left)
				return p;
		}
		return nil;
	}
	Unit* predecessor(Unit *u) // 前驱
	{
		if (u == nil)
			return u;
		if (u->left != nil)
			return maximum(u->left);
		for (Unit *p = u->parent; p != nil; u = p, p = u->parent)
		{
			if (u == p->right)
				return p;
		}
		return nil;
	}
	void replace(Unit *old_u, Unit *new_u) // 替换子树
	{
		if (old_u == nil)
			return;
		if (old_u == root)
		{
			root = new_u;
		}
		else
		{
			if (old_u->parent->left == old_u)
				old_u->parent->left = new_u;
			else
				old_u->parent->right = new_u;
		}
		new_u->parent = old_u->parent; // set nil->parent is allowed
	}

public:
	using element_type = double;

	BinarySearchTree() : root(nullptr), nil(new Unit) { root = nil; nil->e = double(); }
	BinarySearchTree(BinarySearchTree &t) = delete;
	~BinarySearchTree() { clear(); delete nil; }

	void clear() { clear(root); }
	void copy_to_array(double *es) { copy_to_array(es, root); }
	int get_height() { return get_height(root); }
	double get_by_pos(int depth, int number) { return get_by_pos(depth, number, root)->e; }

	double search(double e) { return search(e, root)->e; }
	double minimum() { return minimum(root)->e; }
	double maximum() { return maximum(root)->e; }
	double successor(double e) { return successor(search(e, root))->e; }
	double predecessor(double e) { return predecessor(search(e, root))->e; }

	void insert(double e) // 插入
	{
		Unit *u = new Unit;
		u->e = e;
		u->parent = nil;
		u->left = nil;
		u->right = nil;
		if (root == nil)
			root = u;
		else
		{
			Unit *p = nil, *c = root;
			while (c != nil) // 二叉搜索空节点
			{
				p = c;
				c = (e < p->e ? p->left : p->right);
			}
			if (e < p->e)
				p->left = u;
			else
				p->right = u;
			u->parent = p;
		}
	}
	double remove(double e) // 删除
	{
		Unit *u = search(e, root);
		if (u == nil)
			return u->e;
		if (u->right == nil) // u没有右子节点
			replace(u, u->left);
		else if (u->left == nil) // u没有左子节点
			replace(u, u->right);
		else // u有两个子节点
		{
			Unit *u2;
			static int loop = 0;
			if (((++loop) %= 2) == 0)
			{
				u2 = minimum(u->right); // 找到后继，后继没有左子节点
				replace(u2, u2->right); // 删除后继
			}
			else
			{
				u2 = maximum(u->left); // 找到前驱，前驱没有右子节点
				replace(u2, u2->left); // 删除前驱
			}
			u2->left = u->left; // 移动子节点
			u2->right = u->right;
			u2->left->parent = u2->right->parent = u2;
			replace(u, u2); // 换入u2
		}
		double e2 = u->e;
		delete u;
		return e2;
	}
};
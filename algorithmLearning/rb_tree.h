#pragma once
#include "binary_search_tree.h"
struct RBTreeUnit
{
	static const char R = 'R'; // RED
	static const char B = 'B'; // BLACK
	char color;
	double e;
	RBTreeUnit *parent;
	RBTreeUnit *left;
	RBTreeUnit *right;
};
class RBTree : public BinarySearchTree<RBTreeUnit> // 红黑树
{
	// 性质1 根为黑色
	// 性质2 红节点的子节点为黑色（或没有子节点）
	// 性质3 每条向下路径包含相同数量的黑节点
private:
	using Unit = RBTreeUnit;

	int get_black_height(Unit *u)
	{
		int bh = 0;
		while (u != nil)
		{
			if (u->color == Unit::B)
				bh++;
			u = u->left;
		}
		return bh;
	}
	void left_rotate(Unit *u) // 左旋
	{
		if (u->right == nil)
			return;
		Unit *u2 = u->right;
		u->right = u2->left;
		u->right->parent = u; // set nil->parent is allowed
		replace(u, u2);
		u2->left = u;
		u->parent = u2;
	}
	void right_rotate(Unit *u) // 右旋
	{
		if (u->left == nil)
			return;
		Unit *u2 = u->left;
		u->left = u2->right;
		u->left->parent = u; // set nil->parent is allowed
		replace(u, u2);
		u2->right = u;
		u->parent = u2;
	}
	void rotate(Unit *&p, Unit *&c) // 旋转
	{
		if (p->left == c)
			right_rotate(p);
		else if (p->right == c)
			left_rotate(p);
		c = p;
		p = c->parent;
	}
	void rotate_swap(Unit *&p, Unit *&c) // 旋转并交换颜色，可看成将子节点扭到另一侧
	{
		char color = c->color;
		c->color = p->color;
		p->color = color;
		rotate(p, c);
	}

public:
	RBTree() : BinarySearchTree() { nil->color = Unit::B; }
	RBTree(RBTree &t) = delete; // 禁止拷贝
	~RBTree() {}

	int get_black_height() { return get_black_height(root); }
	char get_color_by_pos(int depth, int number) { return get_by_pos(depth, number, root)->color; }

	void insert(double e) // 插入
	{
		Unit *u = new Unit;
		u->color = Unit::R; // 添加红色不破坏性质3
		u->e = e;
		u->parent = nil;
		u->left = nil;
		u->right = nil;
		if (root == nil)
			root = u;
		else
		{
			Unit *p = nil, *c = root;
			while (c != nil)
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
		// 维护性质1和性质2
		// 保持u是红色，子节点是黑节点
		while (true)
		{
			if (u == root) // case 1: 来到了根节点，破坏性质1
			{
				root->color = Unit::B;
				return;
			}
			else if (u->parent->color == Unit::B) // case 2: 父节点是黑色，没破坏性质
				return;
			else // case 3: 父节点是红色，破坏性质2
			{
				Unit *p = u->parent; // 父节点
				Unit *gp = p->parent; // 祖父节点
				if (gp->left->color == Unit::R && gp->right->color == Unit::R) // case 3-1: 祖父两个孩子都是红色
				{
					gp->color = Unit::R; // 交换祖父和祖父孩子的颜色
					gp->left->color = Unit::B;
					gp->right->color = Unit::B;
					u = gp; // 向上移动2层，继续循环
					continue;
				}
				else // case 3-2: 叔是黑色，那么只有两个红色u,p
				{
					if ((u == p->left && p == gp->right) || (u == p->right && p == gp->left)) // u在旋转的中间
						rotate_swap(p, u); // 将u扭到另一侧
					rotate_swap(gp, p); // 将p扭到另一侧，u自然上升成gp的孩子
					return;
				}
			}
		}
	}
	double remove(double e) // 删除
	{
		Unit *u = search(e, root);
		if (u == nil)
			return u->e;
		char remove_color; // 保存被删除的颜色
		Unit *u_remove; // 保存被删除颜色的子树
		if (u->right == nil) // u没有右子节点
		{
			remove_color = u->color;
			u_remove = u->left;
			replace(u, u->left); // 如果u_remove是nil，replace会让nil->parent暂存u->parent，且黑色保证u必有兄弟
		}
		else if (u->left == nil) // u没有左子节点
		{
			remove_color = u->color;
			u_remove = u->right;
			replace(u, u->right);
		}
		else // u有两个子节点
		{
			Unit *u2;
			static int loop = 0;
			if (((++loop) %= 2) == 0)
			{
				u2 = minimum(u->right); // 找到后继，后继没有左子节点
				remove_color = u2->color;
				u_remove = u2->right;
				replace(u2, u2->right); // 删除后继
			}
			else
			{
				u2 = maximum(u->left); // 找到前驱，前驱没有右子节点
				remove_color = u2->color;
				u_remove = u2->left;
				replace(u2, u2->left); // 删除前驱
			}
			u2->left = u->left; // 移动子节点
			u2->right = u->right;
			u2->left->parent = u2->right->parent = u2;
			replace(u, u2); // 换入u2
			u2->color = u->color; // 顶替颜色
		}
		double e2 = u->e;
		delete u;
		u = u_remove; // 简写
		if (remove_color == Unit::B) // 删除了黑色，u子树少了一个黑色
		{
			// 维护性质，保持u子树少了一个黑色
			while (true)
			{
				if (u == root) // case 1: 来到了根节点，根节点少了也没关系
				{
					root->color = Unit::B;
					return e2;
				}
				else if (u->color == Unit::R) // case 2: u是红色
				{
					u->color = Unit::B; // 设置子树根节点，使子树黑色+1
					return e2;
				}
				else // case 3: u是黑色
				{
					Unit *p = u->parent; // 父节点
					Unit *bro = (u == p->left ? p->right : p->left); // 兄弟节点
					if (bro->color == Unit::R) // case 3-1: 兄弟是红色，父节点是黑色
					{
						rotate_swap(p, bro); // 将bro扭到u这侧，u自然下降成bro的孩子，u的新兄弟是黑色
						continue;
					}
					else if (bro->left->color == Unit::B && bro->right->color == Unit::B) // case 3-2: 兄弟是黑色，有两个黑色孩子
					{
						bro->color = Unit::R; // 使兄弟子树也少一个黑色
						u = p;
						continue;
					}
					else // case 3-3: 兄弟是黑色，至少有一个红色孩子
					{
						Unit *bro_c = (bro == p->left ? bro->left : bro->right); // 兄弟的兄弟侧孩子
						Unit *bro_c2 = (bro == p->left ? bro->right : bro->left); // 兄弟的中间侧孩子
						if (bro_c->color == Unit::B) // 红色孩子不在兄弟侧
						{
							rotate_swap(bro, bro_c2); // 将红色孩子扭到兄弟侧
							bro_c = bro_c2;
						}
						rotate_swap(p, bro); // 把bro扭到u这侧，u这侧黑色+1
						bro_c->color = Unit::B; // 兄弟侧失去了bro，通过设置红色孩子维持黑高
						return e2;
					}
				}
			}
		}
		return e2;
	}
};
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
class RBTree : public BinarySearchTree<RBTreeUnit> // �����
{
	// ����1 ��Ϊ��ɫ
	// ����2 ��ڵ���ӽڵ�Ϊ��ɫ����û���ӽڵ㣩
	// ����3 ÿ������·��������ͬ�����ĺڽڵ�
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
	void left_rotate(Unit *u) // ����
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
	void right_rotate(Unit *u) // ����
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
	void rotate(Unit *&p, Unit *&c) // ��ת
	{
		if (p->left == c)
			right_rotate(p);
		else if (p->right == c)
			left_rotate(p);
		c = p;
		p = c->parent;
	}
	void rotate_swap(Unit *&p, Unit *&c) // ��ת��������ɫ���ɿ��ɽ��ӽڵ�Ť����һ��
	{
		char color = c->color;
		c->color = p->color;
		p->color = color;
		rotate(p, c);
	}

public:
	RBTree() : BinarySearchTree() { nil->color = Unit::B; }
	RBTree(RBTree &t) = delete; // ��ֹ����
	~RBTree() {}

	int get_black_height() { return get_black_height(root); }
	char get_color_by_pos(int depth, int number) { return get_by_pos(depth, number, root)->color; }

	void insert(double e) // ����
	{
		Unit *u = new Unit;
		u->color = Unit::R; // ��Ӻ�ɫ���ƻ�����3
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
		// ά������1������2
		// ����u�Ǻ�ɫ���ӽڵ��Ǻڽڵ�
		while (true)
		{
			if (u == root) // case 1: �����˸��ڵ㣬�ƻ�����1
			{
				root->color = Unit::B;
				return;
			}
			else if (u->parent->color == Unit::B) // case 2: ���ڵ��Ǻ�ɫ��û�ƻ�����
				return;
			else // case 3: ���ڵ��Ǻ�ɫ���ƻ�����2
			{
				Unit *p = u->parent; // ���ڵ�
				Unit *gp = p->parent; // �游�ڵ�
				if (gp->left->color == Unit::R && gp->right->color == Unit::R) // case 3-1: �游�������Ӷ��Ǻ�ɫ
				{
					gp->color = Unit::R; // �����游���游���ӵ���ɫ
					gp->left->color = Unit::B;
					gp->right->color = Unit::B;
					u = gp; // �����ƶ�2�㣬����ѭ��
					continue;
				}
				else // case 3-2: ���Ǻ�ɫ����ôֻ��������ɫu,p
				{
					if ((u == p->left && p == gp->right) || (u == p->right && p == gp->left)) // u����ת���м�
						rotate_swap(p, u); // ��uŤ����һ��
					rotate_swap(gp, p); // ��pŤ����һ�࣬u��Ȼ������gp�ĺ���
					return;
				}
			}
		}
	}
	double remove(double e) // ɾ��
	{
		Unit *u = search(e, root);
		if (u == nil)
			return u->e;
		char remove_color; // ���汻ɾ������ɫ
		Unit *u_remove; // ���汻ɾ����ɫ������
		if (u->right == nil) // uû�����ӽڵ�
		{
			remove_color = u->color;
			u_remove = u->left;
			replace(u, u->left); // ���u_remove��nil��replace����nil->parent�ݴ�u->parent���Һ�ɫ��֤u�����ֵ�
		}
		else if (u->left == nil) // uû�����ӽڵ�
		{
			remove_color = u->color;
			u_remove = u->right;
			replace(u, u->right);
		}
		else // u�������ӽڵ�
		{
			Unit *u2;
			static int loop = 0;
			if (((++loop) %= 2) == 0)
			{
				u2 = minimum(u->right); // �ҵ���̣����û�����ӽڵ�
				remove_color = u2->color;
				u_remove = u2->right;
				replace(u2, u2->right); // ɾ�����
			}
			else
			{
				u2 = maximum(u->left); // �ҵ�ǰ����ǰ��û�����ӽڵ�
				remove_color = u2->color;
				u_remove = u2->left;
				replace(u2, u2->left); // ɾ��ǰ��
			}
			u2->left = u->left; // �ƶ��ӽڵ�
			u2->right = u->right;
			u2->left->parent = u2->right->parent = u2;
			replace(u, u2); // ����u2
			u2->color = u->color; // ������ɫ
		}
		double e2 = u->e;
		delete u;
		u = u_remove; // ��д
		if (remove_color == Unit::B) // ɾ���˺�ɫ��u��������һ����ɫ
		{
			// ά�����ʣ�����u��������һ����ɫ
			while (true)
			{
				if (u == root) // case 1: �����˸��ڵ㣬���ڵ�����Ҳû��ϵ
				{
					root->color = Unit::B;
					return e2;
				}
				else if (u->color == Unit::R) // case 2: u�Ǻ�ɫ
				{
					u->color = Unit::B; // �����������ڵ㣬ʹ������ɫ+1
					return e2;
				}
				else // case 3: u�Ǻ�ɫ
				{
					Unit *p = u->parent; // ���ڵ�
					Unit *bro = (u == p->left ? p->right : p->left); // �ֵܽڵ�
					if (bro->color == Unit::R) // case 3-1: �ֵ��Ǻ�ɫ�����ڵ��Ǻ�ɫ
					{
						rotate_swap(p, bro); // ��broŤ��u��࣬u��Ȼ�½���bro�ĺ��ӣ�u�����ֵ��Ǻ�ɫ
						continue;
					}
					else if (bro->left->color == Unit::B && bro->right->color == Unit::B) // case 3-2: �ֵ��Ǻ�ɫ����������ɫ����
					{
						bro->color = Unit::R; // ʹ�ֵ�����Ҳ��һ����ɫ
						u = p;
						continue;
					}
					else // case 3-3: �ֵ��Ǻ�ɫ��������һ����ɫ����
					{
						Unit *bro_c = (bro == p->left ? bro->left : bro->right); // �ֵܵ��ֵܲຢ��
						Unit *bro_c2 = (bro == p->left ? bro->right : bro->left); // �ֵܵ��м�ຢ��
						if (bro_c->color == Unit::B) // ��ɫ���Ӳ����ֵܲ�
						{
							rotate_swap(bro, bro_c2); // ����ɫ����Ť���ֵܲ�
							bro_c = bro_c2;
						}
						rotate_swap(p, bro); // ��broŤ��u��࣬u����ɫ+1
						bro_c->color = Unit::B; // �ֵܲ�ʧȥ��bro��ͨ�����ú�ɫ����ά�ֺڸ�
						return e2;
					}
				}
			}
		}
		return e2;
	}
};
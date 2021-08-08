#pragma once
class BTree // B树
{
private:
public:
	struct Unit
	{
		static const int t = 3; // 给定最小度数
		bool leaf; // 是否为叶
		int n; // 关键字数量
		int k[2 * t - 1]; // 关键字
		Unit* c[2 * t];
	};
	Unit* root;
private:
	void clear(Unit* u)
	{
		if (u != nullptr)
		{
			if (!u->leaf)
			{
				for (int i = 0; i < u->n; i++)
					clear(u->c[i]);
				clear(u->c[u->n]);
			}
			delete u;
		}
	}

	void left_move_key(Unit* u, int i)
	{
		for (i++; i < u->n; i++)
			u->k[i - 1] = u->k[i];
	}
	void right_move_key(Unit* u, int i)
	{
		for (int j = u->n; j > i; j--)
			u->k[j] = u->k[j - 1];
	}
	void left_move_child(Unit* u, int i)
	{
		for (i++; i <= u->n; i++)
			u->c[i - 1] = u->c[i];
	}
	void right_move_child(Unit* u, int i)
	{
		for (int j = u->n; j >= i; j--)
			u->c[j+1] = u->c[j];
	}
	void split_child(Unit* p, int c_i) // 分裂子节点
	{
		Unit* c1 = p->c[c_i];
		if (c1->n != 2 * c1->t - 1)
			return;
		Unit* c2 = new Unit;
		c2->leaf = c1->leaf;
		c1->n = c1->t - 1;
		c2->n = c2->t - 1;
		for (int i = 0; i < c2->n; i++) // 复制子节点关键字
			c2->k[i] = c1->k[c1->n + 1 + i];
		if (!c1->leaf)
			for (int i = 0; i <= c2->n; i++) // 复制子节点子节点
				c2->c[i] = c1->c[c1->n + 1 + i];
		right_move_key(p, c_i); // 在父节点中空出位置
		right_move_child(p, c_i + 1);
		p->k[c_i] = c1->k[c1->n]; // 添加关键字
		p->c[c_i + 1] = c2; // 添加子节点
		p->n++;
	}
	void combine_child(Unit* p, int k_i) // 合并子节点
	{
		Unit* c1 = p->c[k_i];
		Unit* c2 = p->c[k_i + 1];
		if (c1->n != c1->t - 1 || c2->n != c2->t - 1 || c1->leaf != c2->leaf)
			return;
		for (int i = 0; i < c2->n; i++) // 复制子节点关键字
			c1->k[c1->n + 1 + i] = c2->k[i];
		if (!c1->leaf)
			for (int i = 0; i <= c2->n; i++) // 复制子节点子节点
				c1->c[c1->n + 1 + i] = c2->c[i];
		c1->k[c1->n] = p->k[k_i]; // 添加关键字
		c1->n = 2 * c1->t - 1;
		left_move_key(p, k_i); // 在父节点中删除
		left_move_child(p, k_i + 1);
		p->n--;
		delete c2;
	}
	int increase_to_t(Unit* p, int c_i) // 将子节点元素个数增加到t
	{
		Unit* c = p->c[c_i];
		if (c->n != Unit::t - 1)
			return c_i;
		if (c_i > 0 && p->c[c_i - 1]->n > Unit::t - 1) // 从左兄弟移一个元素
		{
			Unit* c2 = p->c[c_i - 1];
			right_move_key(c, 0);
			if (!c->leaf)
				right_move_child(c, 0);
			c->k[0] = c2->k[c2->n - 1];
			if (!c->leaf)
				c->c[0] = c2->c[c2->n];
			c->n++;
			c2->n--;
		}
		else if (c_i < p->n && p->c[c_i + 1]->n > Unit::t - 1) // 从右兄弟移一个元素
		{
			Unit* c2 = p->c[c_i + 1];
			c->k[c->n] = c2->k[0];
			if (!c->leaf)
				c->c[c->n + 1] = c2->c[0];
			left_move_key(c2, 0);
			if (!c2->leaf)
				left_move_child(c2, 0);
			c->n++;
			c2->n--;
		}
		else if (c_i > 0) // 合并左兄弟
			combine_child(p, --c_i);
		else // 合并右兄弟
			combine_child(p, c_i);
		return c_i;
	}

public:
	BTree() : root(new Unit) { root->leaf = true; root->n = 0; }
	BTree(BTree& t) = delete;
	BTree& operator=(BTree& t) = delete;
	~BTree() { clear(); }

	void clear() { clear(root); }
	int get_height()
	{
		int h = 1;
		for (Unit* u = root; !u->leaf; h++)
			u = u->c[0];
		return h;
	}

	int search(int key) // 搜索
	{
		Unit* u = root;
		while (true)
		{
			int i;
			for (i = 0; i < u->n; i++)
				if (key <= u->k[i])
					break;
			if (i < u->n && key == u->k[i])
				return u->k[i];
			else if (u->leaf)
				return int();
			else
				u = u->c[i];
		}
	}
	void insert(int key) // 插入
	{
		if (root->n == 2 * Unit::t - 1) // 保证根不满
		{
			Unit* u = new Unit;
			u->leaf = false;
			u->n = 0;
			u->c[0] = root;
			root = u;
		}
		Unit* u = root;
		while (true)
		{
			if (u->leaf)
			{
				int i;
				for (i = u->n - 1; i >= 0; i--)
				{
					if (u->k[i] <= key)
						break;
					else
						u->k[i + 1] = u->k[i];
				}
				u->k[i + 1] = key;
				u->n++;
				return;
			}
			else
			{
				int i;
				for (i = 0; i < u->n; i++)
					if (key < u->k[i])
						break;
				if (u->c[i]->n == 2 * Unit::t - 1) // 子节点满
					split_child(u, i);
				u = u->c[i];
			}
		}
	}
	int remove(int key) // 删除
	{
		Unit* u = root;
		int i;
		int k;
		while (true) // 找到要删除的节点
		{
			for (i = 0; i < u->n; i++)
				if (key <= u->k[i])
					break;
			if (i < u->n && key == u->k[i])
			{
				k = u->k[i];
				break; // find remove
			}
			else if (u->leaf)
				return int();
			else if (u->c[i]->n == Unit::t - 1) // 子节点不够t
				i = increase_to_t(u, i);
			u = u->c[i];
		}
		while (true) // 维护删除节点的子树
		{
			if (u->leaf)
			{
				for (i++; i < u->n; i++)
					u->k[i - 1] = u->k[i];
				u->n--;
				break;
			}
			else if (u->c[i]->n == Unit::t - 1 && u->c[i + 1]->n == Unit::t - 1) // 合并节点
			{
				combine_child(u, i);
				u = u->c[i];
				i = Unit::t - 1;
			}
			else if (u->c[i]->n > Unit::t - 1) // 找左子树的最大
			{
				Unit* u2 = u->c[i];
				while (!u2->leaf)
				{
					if(u2->c[u2->n]->n == Unit::t - 1)
						increase_to_t(u2, u2->n);
					u2 = u2->c[u2->n];
				}
				u->k[i] = u2->k[u2->n - 1];
				u2->n--;
				break;
			}
			else // 找右子树的最小
			{
				Unit* u2 = u->c[i + 1];
				while (!u2->leaf)
				{
					if (u2->c[0]->n == Unit::t - 1)
						increase_to_t(u2, 0);
					u2 = u2->c[0];
				}
				u->k[i] = u2->k[0];
				for (int i = 1; i < u2->n; i++)
					u2->k[i - 1] = u2->k[i];
				u2->n--;
				break;
			}
		}
		if (root->n == 0) // 维护根节点
		{
			Unit* u = root;
			root = root->c[0];
			delete u;
		}
		return k;
	}
};
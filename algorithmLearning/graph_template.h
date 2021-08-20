#pragma once
#include <vector>
struct Vertex
{
	int i; // ������
	Vertex() : i(-1) {}
};
struct Edge
{
	int i; // �����
	int j; // �յ���
	Edge() : i(-1), j(-1) {}
};

template <typename V, typename E, bool D>
class GraphT // ͼ��ʾ
{
private:
	struct EdgeU // �ߵ�Ԫ������Ԫ
	{
		E e; // ����Ϣ
		EdgeU* next;
		EdgeU(const E& _e) : e(_e) {}
	};
	struct VertexU // ���㵥Ԫ
	{
		V v;  // ������Ϣ
		EdgeU* first; // ����Ϣ��������ͷ
		EdgeU* last; // ����β
		int edge_n;    // ������
		VertexU(const V& _v) : v(_v) {}
	};
	static const bool directed = D; // ����ͼor����ͼ
	std::vector<VertexU> vvu; // ���㵥Ԫ����
	int edge_n; // ��������

	// �������һЩ����
	void add_edge_to_vu(VertexU& vu, int j, const E& e)
	{
		EdgeU* eu = new EdgeU(e);
		eu->e.i = vu.v.i;
		eu->e.j = j;
		eu->next = nullptr;
		if (vu.first == nullptr)
			vu.first = eu;
		else
			vu.last->next = eu;
		vu.last = eu;
		vu.edge_n++;
	}
	bool remove_edge_from_vu(VertexU& vu, int j)
	{
		EdgeU* prev = nullptr, * eu;
		for (eu = vu.first; eu != nullptr; prev = eu, eu = eu->next)
			if (eu->e.j == j)
				break;
		if (eu == nullptr) // �����ڸñ�
			return false;
		if (eu == vu.first)
			vu.first = eu->next;
		else
			prev->next = eu->next;
		if (vu.last == eu)
			vu.last = prev;
		vu.edge_n--;
		delete eu;
		return true;
	}
	void clear_edge_of_vu(VertexU& vu)
	{
		EdgeU* eu = vu.first;
		EdgeU* next;
		while (eu != nullptr)
		{
			next = eu->next;
			delete eu;
			eu = next;
		}
		vu.first = vu.last = nullptr;
		vu.edge_n = 0;
	}

public:
	// ������Ϣ
	using vertex_type = V;
	using edge_type = E;

	// ��������
	GraphT() : edge_n(0) {}
	GraphT(const GraphT& g) = delete;
	GraphT& operator=(const GraphT& g) = delete;
	~GraphT() { clear(); }
	void clear()
	{
		for (VertexU& vu : vvu)
			clear_edge_of_vu(vu);
		vvu.clear();
		edge_n = 0;
	}

	// ������Ϣ
	bool is_directed() const { return directed; }

	// ������Ϣ
	int get_vertex_n() const { return (int)vvu.size(); }
	int get_edge_n() const { return edge_n; }
	int get_edge_n(int i) const { return exist_vertex(i) ? vvu[i].edge_n : 0; }
	int get_edge_n(const V& v) const { return get_edge_n(v.i); }

	// ���������Ϣ
	bool exist_vertex(int i) const { return i < get_vertex_n() && i >= 0; }
	bool exist_edge(int i) const { return exist_vertex(i) && vvu[i].first != nullptr; }
	bool exist_edge(const V& v) const { return exist_edge(v.i); }
	bool exist_edge(int i, int j) const
	{
		if (!exist_vertex(i) || !exist_vertex(j))
			return false;
		EdgeU* eu = vvu[i].first;
		for (; eu != nullptr; eu = eu->next)
			if (eu->e.j == j)
				return true;
		return false;
	}
	bool exist_edge(const V& v, const V& u) const { return exist_edge(v.i, u.i); }
	V& v(int i) { return vvu[i].v; } // ��ֱ���޸Ķ��㸽�����ݣ���ֹ���Ƕ�����i
	E& e(int i, int j) // ����ͼͨ��ɾ��������޸ı߸������ݣ�����ͼ��ֱ���޸ı߸�������
	{
		EdgeU* eu = vvu[i].first;
		for (; true; eu = eu->next)
			if (eu->e.j == j)
				return eu->e;
	}
	E& e(const V& v, const V& u) { return e(v.i, u.i); }

	// �������
	class vertex_iterator : public std::vector<VertexU>::iterator
	{
	public:
		vertex_iterator(const typename std::vector<VertexU>::iterator& it) : std::vector<VertexU>::iterator(it) {}
		V& operator*() const { return std::vector<VertexU>::iterator::operator*().v; }
		V* operator->() const { return &std::vector<VertexU>::iterator::operator->()->v; }
	};
	vertex_iterator begin_vertex() { return vvu.begin(); }
	vertex_iterator end_vertex() { return vvu.end(); }

	// ����߱���
	class edge_iterator
	{
		friend class GraphT;
	private:
		EdgeU* eu;
	public:
		E& operator*() const { return eu->e; }
		E* operator->() const { return &eu->e; }
		edge_iterator& operator++()
		{
			if (eu != nullptr)
				eu = eu->next;
			return (*this);
		}
		const edge_iterator operator++(int) { const edge_iterator it = (*this); ++(*this); return it; }
		bool operator==(const edge_iterator& it) const { return eu == it.eu; }
		bool operator!=(const edge_iterator& it) const { return !((*this) == it); }
	};
	edge_iterator begin_edge(int i)
	{
		edge_iterator ib;
		ib.eu = exist_vertex(i) ? vvu[i].first : nullptr;
		return ib;
	}
	edge_iterator end_edge(int i)
	{
		edge_iterator ie;
		ie.eu = nullptr;
		return ie;
	}
	edge_iterator begin_edge(const V& v) { return begin_edge(v.i); }
	edge_iterator end_edge(const V& v) { return end_edge(v.i); }

	// ȫ���߱���
	class all_edge_iterator
	{
		friend class GraphT;
	private:
		GraphT* p_g;
		EdgeU* eu;
		bool is_valid()
		{
			if (!p_g->is_directed() && eu != nullptr) // ����ͼ����ȫ����ֻ����һ��
			{
				if (eu->e.i >= eu->e.j) // ��Ч�ı�
					return false;
			}
			return true;
		}
	public:
		E& operator*() const { return eu->e; }
		E* operator->() const { return &eu->e; }
		all_edge_iterator& operator++()
		{
			do
			{
				int vertex_i = eu->e.i;
				if (eu != nullptr)
					eu = eu->next;
				if (eu == nullptr) // ��ǰ����߱������
				{
					for (int next_i = vertex_i + 1; p_g->exist_vertex(next_i); next_i++)
						if (p_g->exist_edge(next_i)) // �ҵ���һ�����бߵĶ���
						{
							eu = p_g->vvu[next_i].first;
							break;
						}
				}
			} while (!is_valid());
			return (*this);
		}
		const all_edge_iterator operator++(int) { const all_edge_iterator it = (*this); ++(*this); return it; }
		bool operator==(const all_edge_iterator& it) const { return eu == it.eu; }
		bool operator!=(const all_edge_iterator& it) const { return !((*this) == it); }
	};
	all_edge_iterator begin_edge()
	{
		all_edge_iterator ib;
		ib.p_g = this;
		ib.eu = nullptr;
		for (int i = 0; exist_vertex(i); i++)
			if (exist_edge(i)) // �ҵ���һ�����бߵĶ���
			{
				ib.eu = vvu[i].first;
				break;
			}
		return ib;
	}
	all_edge_iterator end_edge()
	{
		all_edge_iterator ie;
		ie.p_g = this;
		ie.eu = nullptr;
		return ie;
	}

	// �����ɾ���������
	GraphT& add_vertex(const V& v)
	{
		VertexU vu(v);
		vu.v.i = (int)vvu.size();
		vu.first = vu.last = nullptr;
		vu.edge_n = 0;
		vvu.push_back(vu);
		return (*this);
	}
	GraphT& add_edge(int i, int j, const E& e)
	{
		if (!exist_vertex(i) || !exist_vertex(j))
			return (*this);
		add_edge_to_vu(vvu[i], j, e);
		if (!is_directed() && i != j)
			add_edge_to_vu(vvu[j], i, e);
		edge_n++;
		return (*this);
	}
	GraphT& add_edge(const V& v, const V& u, const E& e) { return add_edge(v.i, u.i, e); }
	GraphT& remove_edge(int i, int j)
	{
		if (!exist_vertex(i) || !exist_vertex(j))
			return (*this);
		if (remove_edge_from_vu(vvu[i], j))
		{
			if (!is_directed() && i != j)
				remove_edge_from_vu(vvu[j], i);
			edge_n--;
		}
		return (*this);
	}
	GraphT& remove_edge(const V& v, const V& u) { return remove_edge(v.i, u.i); }
	GraphT& remove_vertex(int i)
	{
		if (!exist_vertex(i))
			return (*this);
		edge_n -= get_edge_n(i);
		clear_edge_of_vu(vvu[i]);
		if (is_directed())
			for (VertexU& vu : vvu)
				remove_edge(vu.v.i, i);
		else
			for (VertexU& vu : vvu)
				remove_edge_from_vu(vu, i);
		for (int j = i + 1; j < vvu.size(); j++)
			vvu[j - 1] = vvu[j];
		vvu.pop_back();
		for (VertexU& vu : vvu)
		{
			if (vu.v.i > i)
				vu.v.i--;
			for (EdgeU* eu = vu.first; eu != nullptr; eu = eu->next)
			{
				if (eu->e.i > i)
					eu->e.i--;
				if (eu->e.j > i)
					eu->e.j--;
			}
		}
		return (*this);
	}
	GraphT& remove_vertex(const V& v) { return remove_vertex(v.i); }
};
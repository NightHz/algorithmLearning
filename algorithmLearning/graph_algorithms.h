#pragma once
#include "graph.h"
#include "data_structure.h"
#include "sort.h"
#include "heap.h"
// breadth first search 广度优先搜索
template <typename E, bool D>
void BFS_init(GraphT<VertexBFS, E, D>& g, int i)
{
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
	{
		it->c = it->WHITE;
		it->d = -1;
		it->p = nullptr;
	}
	VertexBFS& v = g.v(i);
	v.c = v.GRAY;
	v.d = 0;
	v.p = nullptr;
}
template <typename E, bool D>
void BFS(GraphT<VertexBFS, E, D>& g, int i)
{
	BFS_init(g, i);
	Queue<int> q;
	q.enqueue(i);
	while (q.size() > 0)
	{
		int i = q.dequeue();
		VertexBFS& v = g.v(i);
		for (auto it = g.begin_edge(i); it != g.end_edge(i); it++)
		{
			VertexBFS& u = g.v(it->j);
			if (u.c == u.WHITE)
			{
				u.c = u.GRAY;
				u.d = v.d + 1;
				u.p = &v;
				q.enqueue(u.i);
			}
		}
		v.c = v.BLACK;
	}
}

// depth first search 深度优先搜索
void DFS_init(GraphDFS& g)
{
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
	{
		it->c = it->WHITE;
		it->d = -1;
		it->f = -1;
		it->p = nullptr;
	}
}
void DFS_visit(GraphDFS& g, VertexDFS& v, int &time)
{
	v.d = time++;
	v.c = v.GRAY;
	for (auto it = g.begin_edge(v); it != g.end_edge(v); it++)
	{
		VertexDFS& u = g.v(it->j);
		if (u.c == u.WHITE)
		{
			u.p = &v;
			DFS_visit(g, u, time);
		}
	}
	v.c = v.BLACK;
	v.f = time++;
}
void DFS(GraphDFS& g)
{
	DFS_init(g);
	int time = 1;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
	{
		if (it->c == it->WHITE)
		{
			it->p = nullptr;
			DFS_visit(g, *it, time);
		}
	}
}
// 拓扑排序
template <typename V, typename E>
void topological_sort(GraphT<V, E, true>& g, int* p) // p应该足够大，保存结果
{
	if (!g.is_directed())
		return;
	int v_n = g.get_vertex_n();									
	GraphDFS g_DFS;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		g_DFS.add_vertex(VertexDFS());
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		g_DFS.add_edge(it->i, it->j, Edge());
	DFS(g_DFS);
	VertexDFS* vs = new VertexDFS[v_n];
	for (int i = 0; i < v_n; i++)
		vs[i] = g_DFS.v(i);
	sort_quick(vs, g_DFS.get_vertex_n());
	for (int i = 0; i < v_n; i++)
		p[i] = vs[i].i;
	delete[] vs;
}
// 强连通分量
void strongly_connected_components(GraphD& g, GraphD& r) // r是空图，保存结果
{
	if (!g.is_directed())
		return;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		r.add_vertex(Vertex());
	int v_n = g.get_vertex_n();
	int* topo_sort = new int[v_n];
	topological_sort(g, topo_sort);
	GraphDFS g_t_DFS; // transpose 转置
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		g_t_DFS.add_vertex(VertexDFS());
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		g_t_DFS.add_edge(it->j, it->i, Edge());
	DFS_init(g_t_DFS);
	int time = 1;
	for (int i = 0; i < v_n; i++) // 使用 topo_sort 顺序 DFS
	{
		VertexDFS& v = g_t_DFS.v(topo_sort[i]);
		if (v.c == v.WHITE)
		{
			v.p = nullptr;
			DFS_visit(g_t_DFS, v, time);
		}
		VertexDFS* root = &v;
		while (root->p != nullptr)
			root = root->p;
		r.add_edge(root->i, v.i, Edge());
	}
	delete[] topo_sort;
}

// minimum spanning tree 最小生成树
void MST_kruskal(GraphW &g, GraphW &r) // r是空图，保存结果
{
	if (g.is_directed())
		return;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		r.add_vertex(Vertex());
	int v_n = g.get_vertex_n();
	int e_n = g.get_edge_n();
	EdgeW* es = new EdgeW[e_n];
	int i = 0;
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		es[i++] = *it;
	sort_quick(es, e_n); // 边排序
	struct VertexSet : DisjointSet<VertexSet> {};
	VertexSet* vs = new VertexSet[v_n];
	for (i = 0; i < e_n; i++)
	{
		EdgeW& e = es[i];
		if (vs[e.i].find_set() != vs[e.j].find_set())
		{
			r.add_edge(e.i, e.j, e);
			VertexSet::combine(vs[e.i], vs[e.j]);
		}
	}
	delete[] vs;
	delete[] es;
}
void MST_prim(GraphW& g, GraphW& r) // r是空图，保存结果
{
	if (g.is_directed())
		return;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		r.add_vertex(Vertex());
	int v_n = g.get_vertex_n();
	struct VertexSet : DisjointSet<VertexSet> {};
	VertexSet* vs = new VertexSet[v_n];
	Heap<EdgeW> h;
	if (g.exist_vertex(0))
	{
		for (auto it = g.begin_edge(0); it != g.end_edge(0); it++)
			h.insert(*it);
	}
	while (h.size() > 0)
	{
		EdgeW e = h.extract_min();
		if (vs[e.i].find_set() != vs[e.j].find_set())
		{
			r.add_edge(e.i, e.j, e);
			VertexSet::combine(vs[e.i], vs[e.j]);
			for (auto it = g.begin_edge(e.j); it != g.end_edge(e.j); it++)
				if (vs[it->i].find_set() != vs[it->j].find_set())
					h.insert(*it);
		}
	}
	delete[] vs;
}

// shortest path problem 最短路径问题
void SP_init(GraphSP& g, int i)
{
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
	{
		it->d = INF;
		it->p = nullptr;
	}
	VertexSP& s = g.v(i);
	s.d = 0;
	s.p = nullptr;
}
void SP_relax(VertexSP& v, VertexSP& u, int w)
{
	if (u.d > v.d + w)
	{
		u.d = v.d + w;
		u.p = &v;
	}
}
bool SP_bellman_ford(GraphSP& g, int i)
{
	SP_init(g, i);
	int v_n = g.get_vertex_n();
	for (int i = 0; i < v_n - 1; i++)
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			SP_relax(g.v(it->i), g.v(it->j), it->w);
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		if (g.v(it->j).d > g.v(it->i).d + it->w)
			return false;
	return true;
}
void SP_directed_acyclic(GraphSP& g, int i) // 要求有向无环图
{
	if (!g.is_directed())
		return;
	int v_n = g.get_vertex_n();
	int* topo_sort = new int[v_n];
	topological_sort(g, topo_sort);
	SP_init(g, i);
	for (int i = 0; i < v_n; i++) // 使用 topo_sort 顺序松弛
	{
		VertexSP& v = g.v(topo_sort[i]);
		for (auto it = g.begin_edge(v); it != g.end_edge(v); it++)
			SP_relax(v, g.v(it->j), it->w);
	}                                                                                                                                  
	delete[] topo_sort;
}
void SP_dijkstra(GraphSP& g, int i) // 要求权重非负
{
	SP_init(g, i);
	Heap<VertexSP> h;
	h.insert(g.v(i));
	int loop_times = 0;
	while (h.size() > 0)
	{
		VertexSP min = h.extract_min();
		VertexSP& v = g.v(min.i);
		if (v.d < min.d) // 该点曾以更小的距离松弛过了
			continue;
		if (loop_times++ >= g.get_vertex_n())
			return; // 存在负权重边，会使得循环次数过多，或产生死循环
		for (auto it = g.begin_edge(v); it != g.end_edge(v); it++)
		{
			VertexSP& u = g.v(it->j);
			if (u.d > v.d + it->w) // SP_relax
			{
				u.d = v.d + it->w;
				u.p = &v;
				h.insert(u);
			}
		}
	}
}
// all pairs shortest paths
void APSP_relax(int& v, int& u, int w)
{
	if (v < INF && w < INF && u > v + w)
	{
		u = v + w;
	}
}
void APSP_extend(int* _l, int* _w, int* _l2, int n)
{
	auto l = [_l, n](int i, int j) -> int& {return _l[i * n + j]; };
	auto w = [_w, n](int i, int j) -> int& {return _w[i * n + j]; };
	auto l2 = [_l2, n](int i, int j) -> int& {return _l2[i * n + j]; };
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			l2(i, j) = INF;
			for (int k = 0; k < n; k++)
				APSP_relax(l(i, k), l2(i, j), w(k, j));
		}
}
void APSP_slow(int* _w, int* _d, int n)
{
	int* _l = new int[n * n];
	int* _l2 = new int[n * n];
	for (int i = 0; i < n * n; i++)
		_l[i] = _w[i];
	for (int m = 1; m < n - 1; m++)
	{
		APSP_extend(_l, _w, _l2, n);
		int* t = _l;
		_l = _l2;
		_l2 = t;
	}
	for (int i = 0; i < n * n; i++)
		_d[i] = _l[i];
	delete[] _l;
	delete[] _l2;
}
void APSP_faster(int* _w, int* _d, int n)
{
	int* _l = new int[n * n];
	int* _l2 = new int[n * n];
	for (int i = 0; i < n * n; i++)
		_l[i] = _w[i];
	for (int m = 1; m < n - 1; m *= 2)
	{
		APSP_extend(_l, _l, _l2, n);
		int* t = _l;
		_l = _l2;
		_l2 = t;
	}
	for (int i = 0; i < n * n; i++)
		_d[i] = _l[i];
	delete[] _l;
	delete[] _l2;
}
void APSP_floyd_warshall(int* _w, int* _d, int n)
{
	int* _d1 = new int[n * n];
	int* _d2 = new int[n * n];
	for (int i = 0; i < n * n; i++)
		_d1[i] = _w[i];
	for (int k = 0; k < n; k++)
	{
		auto d1 = [_d1, n](int i, int j) -> int& {return _d1[i * n + j]; };
		auto d2 = [_d2, n](int i, int j) -> int& {return _d2[i * n + j]; };
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d2(i, j) = d1(i, j), APSP_relax(d1(i, k), d2(i, j), d1(k, j));
		int* t = _d1;
		_d1 = _d2;
		_d2 = t;
	}
	for (int i = 0; i < n * n; i++)
		_d[i] = _d1[i];
	delete[] _d1;
	delete[] _d2;
}
bool APSP_johnson(GraphDW& g, int* _d)
{
	int n = g.get_vertex_n();
	auto d = [_d, n](int i, int j) -> int& {return _d[i * n + j]; };
	GraphSP g_add0_SP;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		g_add0_SP.add_vertex(VertexSP());
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		g_add0_SP.add_edge(it->i, it->j, EdgeW(it->w));
	g_add0_SP.add_vertex(VertexSP());
	for (int i = 0; i < n; i++)
		g_add0_SP.add_edge(n, i, EdgeW(0));
	if (!SP_bellman_ford(g_add0_SP, n)) // bellman ford 调整权重
		return false;
	GraphSP g_SP;
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		g_SP.add_vertex(VertexSP());
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		g_SP.add_edge(it->i, it->j, EdgeW(it->w + g_add0_SP.v(it->i).d - g_add0_SP.v(it->j).d));
	for (int i = 0; i < n; i++)
	{
		SP_dijkstra(g_SP, i); // dijkstra 计算最短路径
		for (int j = 0; j < n; j++)
			d(i, j) = g_SP.v(j).d + g_add0_SP.v(j).d - g_add0_SP.v(i).d;
	}
	return true;
}

// 最大流
void flow_init(GraphFlow& g)
{
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		it->f = 0;
}
void flow_edmonds_karp(GraphFlow& g, int s, int t)
{
	flow_init(g);
	while (true)
	{
		GraphT<VertexBFS, EdgeFlow, true> g_BFS; // 残存网络
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			g_BFS.add_vertex(VertexBFS());
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
		{
			if (it->f < it->c)
				g_BFS.add_edge(it->i, it->j, EdgeFlow(it->c - it->f));
			if (it->f > 0)
				g_BFS.add_edge(it->j, it->i, EdgeFlow(it->f));
		}
		BFS(g_BFS, s);
		if (g_BFS.v(t).p == nullptr) // 不存在增广路径
			return;
		int c = INF;
		for (VertexBFS* p = &g_BFS.v(t); p->p != nullptr; p = p->p) // 找到最小容量
		{
			int c2 = g_BFS.e(p->p->i, p->i).c;
			c = (c2 < c ? c2 : c);
		}
		for (VertexBFS* p = &g_BFS.v(t); p->p != nullptr; p = p->p) // 修改流
		{
			if (g.exist_edge(p->p->i, p->i))
				g.e(p->p->i, p->i).f += c;
			else
				g.e(p->i, p->p->i).f -= c;
		}
	}
}
void flow_push(GraphFlow& g, GraphFlow& g_f, int* e, int v, int u)
{
	EdgeFlow& edge = g_f.e(v, u);
	int c = (e[v] < edge.c ? e[v] : edge.c);
	if (g.exist_edge(v, u))
		g.e(v, u).f += c;
	else
		g.e(u, v).f -= c;
	edge.c -= c;
	g_f.e(u, v).c += c;
	e[v] -= c;
	e[u] += c;
}
int flow_relabel(GraphFlow& g, GraphFlow& g_f, int* h, int v)
{
	int h_min = INF;
	int u = -1;
	for (auto it = g_f.begin_edge(v); it != g_f.end_edge(v); it++)
	{
		if (it->c == 0)
			continue;
		if (h[it->j] < h_min)
			h_min = h[it->j], u = it->j;
	}
	h[v] = h_min + 1;
	return u;
}
void flow_push_relabel(GraphFlow& g, int s, int t)
{
	flow_init(g);
	int n = g.get_vertex_n();
	int* e = new int[n] {0};
	int* h = new int[n] {0};
	h[s] = n;
	for (auto it = g.begin_edge(s); it != g.end_edge(s); it++)
	{
		it->f = it->c;
		e[it->j] += it->f;
		e[s] -= it->f;
	}
	GraphFlow g_f; // 残存网络
	for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		g_f.add_vertex(Vertex());
	for (auto it = g.begin_edge(); it != g.end_edge(); it++)
	{
		g_f.add_edge(it->i, it->j, EdgeFlow(it->c - it->f));
		g_f.add_edge(it->j, it->i, EdgeFlow(it->f));
	}
	bool overflow = true;
	while (overflow)
	{
		overflow = false;
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
		{
			if (it->i == t)
				continue;
			while (e[it->i] > 0)
			{
				overflow = true;
				flow_push(g, g_f, e, it->i, flow_relabel(g, g_f, h, it->i));
			}
		}
	}
	delete[] e;
	delete[] h;
}
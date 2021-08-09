#pragma once
#include "graph_template.h"
#include "disjoint_set.h"
using Graph = GraphT<Vertex, Edge, false>; // 无向图
using GraphD = GraphT<Vertex, Edge, true>; // 有向图

struct EdgeW : Edge
{
	int w; // 权重
	EdgeW(int _w = 0) : w(_w) {}
	bool operator<(const EdgeW& e) { return w < e.w; } // 按边权重排序
};
using GraphW = GraphT<Vertex, EdgeW, false>; // 无向带权图
using GraphDW = GraphT<Vertex, EdgeW, true>; // 有向带权图

struct VertexBFS : Vertex
{
	static const int WHITE = 1; // 白色
	static const int GRAY = 2; // 灰色
	static const int BLACK = 3; // 黑色
	int c; // 颜色
	int d; // 对根节点的距离
	VertexBFS* p; // 父节点
	VertexBFS() {}
};
using GraphBFS = GraphT<VertexBFS, Edge, false>; // for BFS

struct VertexDFS : Vertex
{
	static const int WHITE = 1; // 白色
	static const int GRAY = 2; // 灰色
	static const int BLACK = 3; // 黑色
	int c; // 颜色
	int d; // 发现时间
	int f; // 完成时间
	VertexDFS* p; // 父节点
	VertexDFS() {}
	bool operator<(const VertexDFS& v) { return f > v.f; } // 拓扑排序的顺序
};
using GraphDFS = GraphT<VertexDFS, Edge, true>; // for DFS

static const int INF = 0xfffffff; // 无限大
struct VertexSP : Vertex
{
	int d; // 对源的距离
	VertexSP* p; // 父节点
	VertexSP() {}
	bool operator<(const VertexSP& v) { return d < v.d; } // 按距离排序
};
using GraphSP = GraphT<VertexSP, EdgeW, true>; // for SP

struct EdgeFlow : Edge
{
	int c; // 容量
	int f; // 流量
	EdgeFlow(int _c = 0) : c(_c) {}
};
using GraphFlow = GraphT<Vertex, EdgeFlow, true>; // 流网络
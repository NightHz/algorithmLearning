#pragma once
#include "graph_template.h"
#include "disjoint_set.h"
using Graph = GraphT<Vertex, Edge, false>; // ����ͼ
using GraphD = GraphT<Vertex, Edge, true>; // ����ͼ

struct EdgeW : Edge
{
	int w; // Ȩ��
	EdgeW(int _w = 0) : w(_w) {}
	bool operator<(const EdgeW& e) { return w < e.w; } // ����Ȩ������
};
using GraphW = GraphT<Vertex, EdgeW, false>; // �����Ȩͼ
using GraphDW = GraphT<Vertex, EdgeW, true>; // �����Ȩͼ

struct VertexBFS : Vertex
{
	static const int WHITE = 1; // ��ɫ
	static const int GRAY = 2; // ��ɫ
	static const int BLACK = 3; // ��ɫ
	int c; // ��ɫ
	int d; // �Ը��ڵ�ľ���
	VertexBFS* p; // ���ڵ�
	VertexBFS() {}
};
using GraphBFS = GraphT<VertexBFS, Edge, false>; // for BFS

struct VertexDFS : Vertex
{
	static const int WHITE = 1; // ��ɫ
	static const int GRAY = 2; // ��ɫ
	static const int BLACK = 3; // ��ɫ
	int c; // ��ɫ
	int d; // ����ʱ��
	int f; // ���ʱ��
	VertexDFS* p; // ���ڵ�
	VertexDFS() {}
	bool operator<(const VertexDFS& v) { return f > v.f; } // ���������˳��
};
using GraphDFS = GraphT<VertexDFS, Edge, true>; // for DFS

static const int INF = 0xfffffff; // ���޴�
struct VertexSP : Vertex
{
	int d; // ��Դ�ľ���
	VertexSP* p; // ���ڵ�
	VertexSP() {}
	bool operator<(const VertexSP& v) { return d < v.d; } // ����������
};
using GraphSP = GraphT<VertexSP, EdgeW, true>; // for SP

struct EdgeFlow : Edge
{
	int c; // ����
	int f; // ����
	EdgeFlow(int _c = 0) : c(_c) {}
};
using GraphFlow = GraphT<Vertex, EdgeFlow, true>; // ������
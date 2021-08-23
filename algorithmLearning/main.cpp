#include <iostream>
#include "sort.h"
#include "analysis_algorithms.h"
#include "heap.h"
#include "data_structure.h"
#include "hash_table.h"
#include "binary_search_tree.h"
#include "rb_tree.h"
#include <cstring>
#include "b_tree.h"
#include "fib_heap.h"
#include "veb_tree.h"
#include "graph.h"
#include "graph_algorithms.h"
#include "matrix.h"
#include "linear_programming.h"
#include "fast_fourier_transform.h"
#include <random>

using std::cin;
using std::cout;
using std::endl;
int main()
{
	cout << "algorithm learning..." << endl;
	// test sort_insertion
	{
		cout << "---- test sort_insertion ----" << endl;
		int n = 10;
		int p[] = { 4,7,3,6,9,1,0,4,6,4 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		sort_insertion(p, n);
		cout << "output: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test sort_merge
	{
		cout << "---- test sort_merge ----" << endl;
		int n = 10;
		int p[] = { 4,7,3,6,9,1,0,4,6,4 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		sort_merge(p, n);
		cout << "output: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test find_maximum_subarray
	{
		cout << "---- test find_maximum_subarray ----" << endl;
		int n = 16;
		int p[] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 }, il, ir, s;
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		find_maximum_subarray(p, n, il, ir, s);
		cout << "left: [" << il << "]" << p[il] << endl;
		cout << "right: [" << ir << "]" << p[ir] << endl;
		cout << "sum: " << s << endl;
	}
	// test Heap
	{
		cout << "---- test Heap ----" << endl;
		int n = 10;
		float p[] = { 4,7,3,6.1f,9,1,5,4.1f,6,0 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		Heap<float> h, h2;
		h.build_heap(p, n);
		h2.build_heap_v2(p, n);

		cout << "heap: " << endl;
		for (int i = 0, j = 2; i < h.size(); i++)
			cout << h.get_by_pos(i) << (i == j - 2 ? (j *= 2, '\n') : '\t');
		cout << endl;
		h.sort_to_array(p);
		cout << "sort_heap: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		cout << "heap2: " << endl;
		for (int i = 0, j = 2; i < h2.size(); i++)
			cout << h2.get_by_pos(i) << (i == j - 2 ? (j *= 2, '\n') : '\t');
		cout << endl;
		h2.sort_to_array(p);
		cout << "sort_heap2: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test sort_quick
	{
		cout << "---- test sort_quick ----" << endl;
		int n = 10;
		int p[] = { 4,7,3,6,9,1,0,4,6,4 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		sort_quick(p, n);
		cout << "output: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test sort_counting
	{
		cout << "---- test sort_counting ----" << endl;
		int n = 10;
		int p[] = { 40,70,30,60,90,10,0,50,80,40 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		sort_counting(p, n, 0, 100);
		cout << "output: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test sort_radix
	{
		cout << "---- test sort_radix ----" << endl;
		int n = 10;
		int p[] = { 40,70,30,60,90,10,0,50,80,40 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		sort_radix(p, n, 2);
		cout << "output: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test sort_bucket
	{
		cout << "---- test sort_bucket ----" << endl;
		int n = 10;
		double p[] = { 0.43,0.76,0.3,0.6,0.72,0.1,0,0.5,0.8,0.44 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		sort_bucket(p, n);
		cout << "output: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
	}
	// test select_Xth
	{
		cout << "---- test select_Xth ----" << endl;
		int n = 10;
		double p[] = { 0.43,0.76,0.3,0.6,0.72,0.1,0,0.5,0.8,0.44 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		cout << "2nd: " << select_Xth(p, n, 2) << endl;
		cout << "3rd: " << select_Xth(p, n, 3) << endl;
		cout << "9th: " << select_Xth(p, n, 9) << endl;
	}
	// test select_Xth_v2
	{
		cout << "---- test select_Xth_v2 ----" << endl;
		int n = 10;
		double p[] = { 0.43,0.76,0.3,0.6,0.72,0.1,0,0.5,0.8,0.44 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		cout << "2nd: " << select_Xth_v2(p, n, 2) << endl;
		cout << "3rd: " << select_Xth_v2(p, n, 3) << endl;
		cout << "9th: " << select_Xth_v2(p, n, 9) << endl;
	}

	// test Stack
	{
		cout << "---- test Stack ----" << endl;
		int n = 10;
		double p[] = { 4,7,3,6.1,9,1,5,4.1,6,0 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		Stack s;
		for (int i = 0; i < n; i++) s.push(p[i]);
		cout << "pop: ";
		while (s.size() > 0)
			cout << s.pop() << " ";
		cout << endl;
	}
	// test Queue
	{
		cout << "---- test Queue ----" << endl;
		int n = 10;
		double p[] = { 4,7,3,6.1,9,1,5,4.1,6,0 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		Queue<> q;
		for (int i = 0; i < n; i++) q.enqueue(p[i]);
		cout << "dequeue: ";
		while (q.size() > 0)
			cout << q.dequeue() << " ";
		cout << endl;
	}
	// test LinkedList
	{
		cout << "---- test LinkedList ----" << endl;
		int n = 10;
		int k[] = { 1,22,333,4,55,666,7,8,9,32 };
		double p[] = { 4,7,3,6.1,9,1,5,4.1,6,0 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << '[' << k[i] << ']' << p[i] << " "; cout << endl;

		LinkedList l;
		for (int i = 0; i < n; i++) l.insert(k[i], p[i]);
		for (int i = 0; i < n; i++)
			cout << "l[" << k[i] << "]=" << l[k[i]] << endl;
	}
	// test ChainedHashTable
	{
		cout << "---- test ChainedHashTable ----" << endl;
		int n = 10;
		int k[] = { 1,22,333,4,55,666,7,8,9,32 };
		double p[] = { 4,7,3,6.1,9,1,5,4.1,6,0 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << '[' << k[i] << ']' << p[i] << " "; cout << endl;

		ChainedHashTable h;
		for (int i = 0; i < n; i++) h.insert(k[i], p[i]);
		for (int i = 0; i < n; i++)
			cout << "hash("<<k[i]<<")="<<h.hash(k[i]) << "   l[" << k[i] << "]=" << h[k[i]] << endl;
	}
	// test HashTable
	{
		cout << "---- test HashTable ----" << endl;
		int n = 10;
		int k[] = { 1,22,333,4,55,666,7,8,9,32 };
		double p[] = { 4,7,3,6.1,9,1,5,4.1,6,0 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << '[' << k[i] << ']' << p[i] << " "; cout << endl;

		HashTable h;
		for (int i = 0; i < n; i++) h.insert(k[i], p[i]);
		for (int i = 0; i < n; i++)
			cout << "hash:" << h.hash(k[i], 0) << "," << h.hash(k[i], 1) << "," << h.hash(k[i], 2) << "   l[" << k[i] << "]=" << h[k[i]] << endl;
	}
	// test BinarySearchTree
	{
		cout << "---- test BinarySearchTree ----" << endl;
		const int n = 8;
		double p[] = { 4,7,3,9,1,5,6,2 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		BinarySearchTree<> t;
		int h;
		double p2[n];

		for (int i = 0; i < 5; i++) t.insert(p[i]);
		t.copy_to_array(p2);
		h = t.get_height();
		cout << "after insert x5: " << endl;
		for (int i = 0; i < 5; i++) cout << p2[i] << " "; cout << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_by_pos(i, j) << " ";
			cout << endl;
		}

		for (int i = 5; i < n; i++) t.insert(p[i]);
		t.copy_to_array(p2);
		h = t.get_height();
		cout << "finish insert: " << endl;
		for (int i = 0; i < n; i++) cout << p2[i] << " "; cout << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_by_pos(i, j) << " ";
			cout << endl;
		}

		cout << "search 5: " << t.search(5) << endl;
		cout << "minimum: " << t.minimum() << endl;
		cout << "maximum: " << t.maximum() << endl;
		cout << "successor(5): " << t.successor(5) << endl;
		cout << "predecessor(5): " << t.predecessor(5) << endl;

		t.remove(4);
		t.copy_to_array(p2);
		h = t.get_height();
		cout << "after remove 4: " << endl;
		for (int i = 0; i < n-1; i++) cout << p2[i] << " "; cout << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_by_pos(i, j) << " ";
			cout << endl;
		}

		t.remove(3);
		t.copy_to_array(p2);
		h = t.get_height();
		cout << "after remove 3: " << endl;
		for (int i = 0; i < n-2; i++) cout << p2[i] << " "; cout << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_by_pos(i, j) << " ";
			cout << endl;
		}

		t.remove(5);
		t.copy_to_array(p2);
		h = t.get_height();
		cout << "after remove 5: " << endl;
		for (int i = 0; i < n-3; i++) cout << p2[i] << " "; cout << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_by_pos(i, j) << " ";
			cout << endl;
		}
	}
	// test RBTree
	{
		cout << "---- test RBTree ----" << endl;
		const int n = 8;
		double p[] = { 1,2,3,5,6,7,4,8 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		RBTree t;
		int h;
		double p2[n];

		for (int i = 0; i < n; i++)
		{
			t.insert(p[i]);
			h = t.get_height();
			cout << "after insert " << p[i] << ": " << endl;
			for (int i2 = 0; i2 < h; i2++)
			{
				for (int j = 0; j < (1 << i2); j++)
					cout << t.get_color_by_pos(i2, j) << t.get_by_pos(i2, j) << " ";
				cout << endl;
			}
		}

		t.copy_to_array(p2);
		cout << "sort: "; for (int i = 0; i < n; i++) cout << p2[i] << " "; cout << endl;
		cout << "height: " << t.get_height() << endl;
		cout << "black height: " << t.get_black_height() << endl;
		cout << "search 5: " << t.search(3) << endl;
		cout << "minimum: " << t.minimum() << endl;
		cout << "maximum: " << t.maximum() << endl;
		cout << "successor(5): " << t.successor(3) << endl;
		cout << "predecessor(5): " << t.predecessor(3) << endl;

		t.remove(1);
		h = t.get_height();
		cout << "after remove 1: " << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_color_by_pos(i, j) << t.get_by_pos(i, j) << " ";
			cout << endl;
		}

		t.remove(4);
		h = t.get_height();
		cout << "after remove 4: " << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_color_by_pos(i, j) << t.get_by_pos(i, j) << " ";
			cout << endl;
		}

		t.remove(3);
		h = t.get_height();
		cout << "after remove 3: " << endl;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < (1 << i); j++)
				cout << t.get_color_by_pos(i, j) << t.get_by_pos(i, j) << " ";
			cout << endl;
		}
	}
	// test cut_rod
	{
		cout << "---- test cut_rod ----" << endl;
		int n = 10;
		int p[] = { 1,5,8,9,10,17,17,20,28,30 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		cout << "cut 10: " << cut_rod(p, n, 10) << endl;
		cout << "cut 11: " << cut_rod(p, n, 11) << endl;
		cout << "cut 27: " << cut_rod(p, n, 27) << endl;
		cout << "cut 36: " << cut_rod(p, n, 36) << endl;
	}
	// test LCS_length
	{
		cout << "---- test LCS_length ----" << endl;
		const char *p1 = "ABCBDAB";
		const char *p2 = "BDCABA";
		cout << "input: " << p1 << endl;
		cout << "       " << p2 << endl;
		cout << "len: " << LCS_length(p1, (int)strlen(p1), p2, (int)strlen(p2)) << endl;
		p1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
		p2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
		cout << "input: " << p1 << endl;
		cout << "       " << p2 << endl;
		cout << "len: " << LCS_length(p1, (int)strlen(p1), p2, (int)strlen(p2)) << endl;
	}
	// test BTree
	{
		cout << "---- test BTree ----" << endl;
		const int n = 25;
		int p[] = { 22,17,15,3,24,18,5,9,2,16,20,12,1,7,13,25,4,8,19,6,21,14,11,10,23 };
		const char* c = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << c[p[i]] << " "; cout << endl;

		BTree t;
		auto print_t = [c](BTree &t)
		{
			auto u = t.root;
			for (int i = 0; i < u->n; i++) cout << c[u->k[i]]; cout << " ";
			cout << endl;
			if (!u->leaf)
			{
				for (int i = 0; i <= u->n; i++)
				{
					auto u2 = u->c[i];
					for (int i2 = 0; i2 < u2->n; i2++)
						cout << c[u2->k[i2]];
					cout << " ";
				}
				cout << endl;
				if (!u->c[0]->leaf)
				{
					for (int i = 0; i <= u->n; i++)
					{
						auto u2 = u->c[i];
						for (int i2 = 0; i2 <= u2->n; i2++)
						{
							auto u3 = u2->c[i2];
							for (int i3 = 0; i3 < u3->n; i3++) cout << c[u3->k[i3]]; cout << " ";
						}
					}
					cout << endl;
				}
			}
		};
		for (int i = 0; i < n; i++)
		{
			t.insert(p[i]);
			cout << "after insert " << c[p[i]] << ": " << endl;
			print_t(t);
		}
		cout << "search " << c[20] << ": " << t.search(20) << endl;
		cout << "search " << c[2] << ": " << t.search(2) << endl;
		cout << "search " << c[28] << ": " << t.search(28) << endl;
		cout << "search " << c[15] << ": " << t.search(15) << endl;
		t.remove(12);
		cout << "after remove " << c[12] << ": " << endl;
		print_t(t);
		t.remove(17);
		cout << "after remove " << c[17] << ": " << endl;
		print_t(t);
		t.remove(19);
		cout << "after remove " << c[19] << ": " << endl;
		print_t(t);
	}
	// test FibHeap
	{
		cout << "---- test FibHeap ----" << endl;
		const int n = 25;
		int p[] = { 22,17,15,3,24,18,5,9,2,16,20,12,1,7,13,25,4,8,19,6,21,14,11,10,23 };
		const char* c = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << c[p[i]] << " "; cout << endl;

		auto print_h = [c](FibHeap& h)
		{
			Queue<FibHeap::Unit*> q;
			auto u = h.root;
			do
			{
				q.enqueue(u);
				u = u->right;
			} while (u != h.root);
			q.enqueue(nullptr);
			bool finish_row = false;
			while (true)
			{
				auto u = q.dequeue();
				if (u == nullptr)
				{
					if (finish_row)
						return;
					finish_row = true;
					cout << endl;
					q.enqueue(nullptr);
				}
				else
				{
					finish_row = false;
					cout << c[u->k] << "(" << u->degree << ")" << (u->mark ? "*" : "") << " ";
					if (u->child != nullptr)
					{
						auto c = u->child;
						do
						{
							q.enqueue(c);
							c = c->right;
						} while (c != u->child);
					}
				}
			}
		};

		FibHeap h, h2;
		double* v[n];
		int d;
		for (int i = 0; i < 14; i++)
			v[p[i] - 1] = h.insert(p[i], p[i]);
		for (int i = 14; i < n; i++)
			v[p[i] - 1] = h2.insert(p[i], p[i]);
		cout << "finish insert: " << endl;
		cout << "h: " << endl; print_h(h);
		cout << "h2: " << endl; print_h(h2);

		d = (int)h.extract_min(); v[d - 1] = h.insert(d, d);
		d = (int)h2.extract_min(); v[d - 1] = h2.insert(d, d);
		cout << "extract_min + insert: " << endl;
		cout << "h: " << endl; print_h(h);
		cout << "h2: " << endl; print_h(h2);

		h.combine(h2);
		cout << "combine: " << endl;
		print_h(h);

		d = (int)h.extract_min(); v[d - 1] = h.insert(d, d);
		cout << "extract_min + insert: " << endl;
		print_h(h);

		cout << "remove " << c[(int)h.remove(v[16])] << ": " << endl;
		print_h(h);

		cout << "remove " << c[(int)h.remove(v[12])] << ": " << endl;
		print_h(h);

		cout << "remove " << c[(int)h.remove(v[8])] << ": " << endl;
		print_h(h);

		cout << "remove " << c[(int)h.remove(v[4])] << ": " << endl;
		print_h(h);
	}
	// test ProtoVEB
	{
		cout << "---- test ProtoVEB ----" << endl;
		cout << "sizeof(ProtoVEB<256>): " << sizeof(ProtoVEB<256>) << endl;
		const int n = 11;
		int p[] = { 10,20,30,40,50,60,70,80,90,100,110 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		ProtoVEB<256> proto_vEB256;
		auto print_vEB = [&proto_vEB256, p, n]()
		{
			for (int i = 0; i < n; i++)
				if (proto_vEB256.is_member(p[i]))
					cout << p[i] << " ";
			cout << endl;
		};
		for (int i = 0; i < n; i++)
			proto_vEB256.insert(p[i]);
		cout << "finish insert: "; print_vEB();

		cout << "minimum: " << proto_vEB256.minimum() << endl;
		cout << "successor 30: " << proto_vEB256.successor(30) << endl;

		proto_vEB256.remove(30);
		cout << "remove 30: "; print_vEB();
	}
	// test VEBTree
	{
		cout << "---- test VEBTree ----" << endl;
		cout << "sizeof(VEBTree<15>): " << sizeof(VEBTree<15>) << endl;
		cout << "sizeof(VEBTree<16>): " << sizeof(VEBTree<16>) << endl;
		cout << "sizeof(VEBTree<127>): " << sizeof(VEBTree<127>) << endl;
		cout << "sizeof(VEBTree<128>): " << sizeof(VEBTree<128>) << endl;
		cout << "sizeof(VEBTree<255>): " << sizeof(VEBTree<255>) << endl;
		cout << "sizeof(VEBTree<256>): " << sizeof(VEBTree<256>) << endl;
		const int n = 11;
		int p[] = { 10,20,30,40,50,60,70,80,90,100,110 };
		cout << "input_n: " << n << endl;
		cout << "input: "; for (int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;

		VEBTree<127> vEB;
		auto print_vEB = [&vEB, p, n]()
		{
			cout << "(Exist:)";
			for (int i = 0; i < n; i++)
				if (vEB.is_member(p[i]))
					cout << p[i] << " ";
			cout << endl;
		};
		for (int i = 0; i < n; i++)
			vEB.insert(p[i]);
		cout << "finish insert: "; print_vEB();

		vEB.remove(10);
		vEB.remove(40);
		vEB.remove(50);
		vEB.remove(60);
		vEB.remove(110);
		cout << "finish remove: "; print_vEB();

		cout << "minimum: " << vEB.minimum() << endl;
		cout << "maximum: " << vEB.maximum() << endl;
		cout << "successor 30: " << vEB.successor(30) << endl;

		vEB.insert(50);
		vEB.insert(50);
		vEB.insert(50);
		cout << "insert 50 x3: "; print_vEB();

		vEB.remove(50);
		vEB.remove(50);
		cout << "remove 50 x2: "; print_vEB();

		vEB.remove(50);
		cout << "remove 50 x1: "; print_vEB();
	}
	// test Graph
	{
		cout << "---- test Graph ----" << endl;
		Graph g1;
		GraphW g2;
		g1.add_vertex(Vertex()); g1.add_edge(0, 0, Edge());
		g2.add_vertex(Vertex()); g2.add_edge(0, 0, EdgeW(20));
		cout << "Graph  : " << "0:" << g1.v(0).i << " (0,0):" << "(" << g1.e(0, 0).i << "," << g1.e(0, 0).j << ")" << endl;
		cout << "GraphW : " << "0:" << g2.v(0).i << " (0,0).w:" << g2.e(0, 0).w << endl;

		Graph g;
		for (int i = 0; i < 10; i++)
			g.add_vertex(Vertex());
		g.add_edge(0, 1, Edge());
		g.add_edge(0, 2, Edge());
		g.add_edge(0, 3, Edge());
		g.add_edge(1, 4, Edge());
		g.add_edge(2, 5, Edge());
		g.add_edge(2, 6, Edge());
		g.add_edge(4, 7, Edge());
		g.add_edge(6, 8, Edge());
		g.add_edge(7, 9, Edge());

		cout << "is_directed: " << (g.is_directed() ? "true" : "false") << endl;
		cout << "vertex_n: " << g.get_vertex_n() << endl;
		cout << "edge_n: " << g.get_edge_n() << endl;
		cout << "edge_n of 2: " << g.get_edge_n(2) << endl;
		cout << "exist_vertex 2: " << (g.exist_vertex(2) ? "true" : "false") << endl;
		cout << "exist_edge of 2: " << (g.exist_edge(2) ? "true" : "false") << endl;
		cout << "exist_edge of 2 and 4: " << (g.exist_edge(2, 4) ? "true" : "false") << endl;
		cout << "exist_edge of 2 and 5: " << (g.exist_edge(2, 5) ? "true" : "false") << endl;
		cout << "g.v(2).i: " << g.v(2).i << endl;
		cout << "g.e(2,5).i: " << g.e(2, 5).i << endl;
		cout << "g.e(2,5).j: " << g.e(2, 5).j << endl;

		cout << "traverse vertex:" << endl;
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			cout << it->i << " ";
		cout << endl;

		cout << "traverse edge:" << endl;
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;

		cout << "traverse edge of 2:" << endl;
		for (auto it = g.begin_edge(2); it != g.end_edge(2); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;

		g.remove_edge(2, 4);
		cout << "remove edge(2,4):" << endl;
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;

		g.remove_edge(2, 5);
		cout << "remove edge(2,5):" << endl;
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;

		g.remove_vertex(2);
		cout << "remove vertex 2:" << endl;
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			cout << it->i << " ";
		cout << endl;
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;
	}
	// test BFS
	{
		cout << "---- test BFS ----" << endl;
		GraphBFS g;
		for (int i = 0; i < 8; i++)
			g.add_vertex(VertexBFS());
		g.add_edge(4, 0, Edge());
		g.add_edge(0, 1, Edge());
		g.add_edge(1, 5, Edge());
		g.add_edge(5, 2, Edge());
		g.add_edge(5, 6, Edge());
		g.add_edge(2, 6, Edge());
		g.add_edge(2, 3, Edge());
		g.add_edge(6, 3, Edge());
		g.add_edge(6, 7, Edge());
		g.add_edge(3, 7, Edge());

		BFS(g, 1);
		cout << "Vertex: ";
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			cout << it->i << "(" << it->d << ") ";
		cout << endl;
		cout << "Edges: ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;
	}
	// test DFS
	{
		cout << "---- test DFS ----" << endl;
		GraphDFS g;
		for (int i = 0; i < 6; i++)
			g.add_vertex(VertexDFS());
		g.add_edge(0, 1, Edge());
		g.add_edge(0, 3, Edge());
		g.add_edge(3, 1, Edge());
		g.add_edge(1, 4, Edge());
		g.add_edge(4, 3, Edge());
		g.add_edge(2, 4, Edge());
		g.add_edge(2, 5, Edge());
		g.add_edge(5, 5, Edge());

		DFS(g);
		cout << "Vertex: ";
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			cout << it->i << "(" << it->d << "," << it->f << ") ";
		cout << endl;
		cout << "Edges: ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;
	}
	// test topological_sort
	{
		cout << "---- test topological_sort ----" << endl;
		const char* name[] = { "内裤","袜子","裤子","鞋","腰带","衬衣","领带","夹克","手表" };
		GraphD g;
		for (int i = 0; i < 9; i++)
			g.add_vertex(Vertex());
		g.add_edge(0, 2, Edge());
		g.add_edge(0, 3, Edge());
		g.add_edge(1, 3, Edge());
		g.add_edge(2, 3, Edge());
		g.add_edge(2, 4, Edge());
		g.add_edge(5, 4, Edge());
		g.add_edge(4, 7, Edge());
		g.add_edge(5, 6, Edge());
		g.add_edge(6, 7, Edge());

		int p[9];
		topological_sort(g, p);
		cout << "sort: ";
		for (int i = 0; i < 9; i++)
			cout << p[i] << "(" << name[p[i]] << ") ";
		cout << endl;
		cout << "Edges: ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;
	}
	// test strongly_connected_components
	{
		cout << "---- test strongly_connected_components ----" << endl;
		GraphD g;
		for (int i = 0; i < 8; i++)
			g.add_vertex(Vertex());
		g.add_edge(0, 1, Edge());
		g.add_edge(4, 0, Edge());
		g.add_edge(1, 4, Edge());
		g.add_edge(1, 5, Edge());
		g.add_edge(4, 5, Edge());
		g.add_edge(1, 2, Edge());
		g.add_edge(5, 6, Edge());
		g.add_edge(6, 5, Edge());
		g.add_edge(2, 6, Edge());
		g.add_edge(2, 3, Edge());
		g.add_edge(3, 2, Edge());
		g.add_edge(6, 7, Edge());
		g.add_edge(3, 7, Edge());
		g.add_edge(7, 7, Edge());

		GraphD r;
		strongly_connected_components(g, r);
		for (auto itv = r.begin_vertex(); itv != r.end_vertex(); itv++)
		{
			if (r.exist_edge(*itv))
			{
				for (auto it = r.begin_edge(*itv); it != r.end_edge(*itv); it++)
					cout << it->j << " ";
				cout << endl;
			}
		}
		cout << "Edges: ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ") ";
		cout << endl;
	}
	// test MST
	{
		cout << "---- test MST ----" << endl;
		GraphW g;
		for (int i = 0; i < 9; i++)
			g.add_vertex(Vertex());
		g.add_edge(0, 1, EdgeW(4));
		g.add_edge(1, 2, EdgeW(8));
		g.add_edge(2, 3, EdgeW(7));
		g.add_edge(3, 4, EdgeW(9));
		g.add_edge(4, 5, EdgeW(10));
		g.add_edge(5, 6, EdgeW(2));
		g.add_edge(6, 7, EdgeW(1));
		g.add_edge(7, 0, EdgeW(8));
		g.add_edge(1, 7, EdgeW(11));
		g.add_edge(2, 8, EdgeW(2));
		g.add_edge(7, 8, EdgeW(7));
		g.add_edge(6, 8, EdgeW(6));
		g.add_edge(2, 5, EdgeW(4));
		g.add_edge(3, 5, EdgeW(14));

		cout << "before Edges : ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->w << ") ";
		cout << endl;

		GraphW r1, r2;
		int sum_weight = 0;

		MST_kruskal(g, r1);
		sum_weight = 0;
		cout << "kruskal Edges: ";
		for (auto it = r1.begin_edge(); it != r1.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->w << ") ", sum_weight += it->w;
		cout << endl;
		cout << "sum weight: " << sum_weight << endl;

		MST_prim(g, r2);
		sum_weight = 0;
		cout << "prim Edges   : ";
		for (auto it = r2.begin_edge(); it != r2.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->w << ") ", sum_weight += it->w;
		cout << endl;
		cout << "sum weight: " << sum_weight << endl;
	}
	// test SP
	{
		cout << "---- test SP ----" << endl;
		GraphSP g;
		for (int i = 0; i < 5; i++)
			g.add_vertex(VertexSP());
		g.add_edge(0, 1, EdgeW(10));
		g.add_edge(0, 4, EdgeW(5));
		g.add_edge(1, 4, EdgeW(2));
		g.add_edge(4, 1, EdgeW(3));
		g.add_edge(1, 2, EdgeW(1));
		g.add_edge(4, 2, EdgeW(9));
		g.add_edge(4, 3, EdgeW(2));
		g.add_edge(2, 3, EdgeW(4));
		g.add_edge(3, 2, EdgeW(6));
		g.add_edge(3, 0, EdgeW(7));

		cout << "Edges : ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->w << ") ";
		cout << endl;

		if (SP_bellman_ford(g, 0))
		{
			cout << "bellman ford Vertex: ";
			for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
				cout << it->i << "(d=" << it->d << ",p_i=" << (it->p == nullptr ? -1 : it->p->i) << ") ";
			cout << endl;
		}

		SP_dijkstra(g, 0);
		cout << "dijkstra Vertex    : ";
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			cout << it->i << "(d=" << it->d << ",p_i=" << (it->p == nullptr ? -1 : it->p->i) << ") ";
		cout << endl;
	}
	// test SP_directed_acyclic
	{
		cout << "---- test SP_directed_acyclic ----" << endl;
		GraphSP g;
		for (int i = 0; i < 6; i++)
			g.add_vertex(VertexSP());
		g.add_edge(0, 1, EdgeW(5));
		g.add_edge(1, 2, EdgeW(2));
		g.add_edge(2, 3, EdgeW(7));
		g.add_edge(3, 4, EdgeW(-1));
		g.add_edge(4, 5, EdgeW(-2));
		g.add_edge(0, 2, EdgeW(3));
		g.add_edge(1, 3, EdgeW(6));
		g.add_edge(2, 4, EdgeW(4));
		g.add_edge(2, 5, EdgeW(2));
		g.add_edge(3, 5, EdgeW(1));

		cout << "Edges : ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->w << ") ";
		cout << endl;

		SP_directed_acyclic(g, 1);
		cout << "directed acyclic Vertex: ";
		for (auto it = g.begin_vertex(); it != g.end_vertex(); it++)
			cout << it->i << "(d=" << it->d << ",p_i=" << (it->p == nullptr ? -1 : it->p->i) << ") ";
		cout << endl;
	}
	// test APSP
	{
		cout << "---- test APSP ----" << endl;
		const int n = 5;
		int* _w = new int[n * n];
		int* _d = new int[n * n];
		auto w = [_w, n](int i, int j) -> int& {return _w[i * n + j]; };
		auto d = [_d, n](int i, int j) -> int& {return _d[i * n + j]; };
		for (int i = 0; i < n * n; i++)
			_w[i] = INF;
		w(0, 0) = 0;
		w(1, 1) = 0;
		w(2, 2) = 0;
		w(3, 3) = 0;
		w(4, 4) = 0;
		w(0, 1) = 3;
		w(2, 1) = 4;
		w(3, 2) = -5;
		w(4, 3) = 6;
		w(0, 4) = -4;
		w(0, 2) = 8;
		w(3, 0) = 2;
		w(1, 3) = 1;
		w(1, 4) = 7;

		cout << "weight : ";
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (w(i, j) < INF)
					cout << "w(" << i << "," << j << ")=" << w(i, j) << " ";
		cout << endl;

		for (int i = 0; i < n * n; i++)
			_d[i] = INF;
		APSP_slow(_w, _d, n);
		cout << "slow distance : " << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if (d(i, j) < INF)
					cout << "d(" << i << "," << j << ")=" << d(i, j) << " ";
				else
					cout << "d(" << i << "," << j << ")=" << "inf" << " ";
			cout << endl;
		}

		for (int i = 0; i < n * n; i++)
			_d[i] = INF;
		APSP_faster(_w, _d, n);
		cout << "faster distance : " << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if (d(i, j) < INF)
					cout << "d(" << i << "," << j << ")=" << d(i, j) << " ";
				else
					cout << "d(" << i << "," << j << ")=" << "inf" << " ";
			cout << endl;
		}

		for (int i = 0; i < n * n; i++)
			_d[i] = INF;
		APSP_floyd_warshall(_w, _d, n);
		cout << "floyd warshall distance : " << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if (d(i, j) < INF)
					cout << "d(" << i << "," << j << ")=" << d(i, j) << " ";
				else
					cout << "d(" << i << "," << j << ")=" << "inf" << " ";
			cout << endl;
		}

		delete[] _w;
		delete[] _d;
	}
	// test APSP_johnson
	{
		cout << "---- test APSP_johnson ----" << endl;
		GraphDW g;
		for (int i = 0; i < 5; i++)
			g.add_vertex(Vertex());
		g.add_edge(0, 0, EdgeW(0));
		g.add_edge(1, 1, EdgeW(0));
		g.add_edge(2, 2, EdgeW(0));
		g.add_edge(3, 3, EdgeW(0));
		g.add_edge(4, 4, EdgeW(0));
		g.add_edge(0, 1, EdgeW(3));
		g.add_edge(2, 1, EdgeW(4));
		g.add_edge(3, 2, EdgeW(-5));
		g.add_edge(4, 3, EdgeW(6));
		g.add_edge(0, 4, EdgeW(-4));
		g.add_edge(0, 2, EdgeW(8));
		g.add_edge(3, 0, EdgeW(2));
		g.add_edge(1, 3, EdgeW(1));
		g.add_edge(1, 4, EdgeW(7));
		const int n = 5;
		int* _d = new int[n * n];
		auto d = [_d, n](int i, int j) -> int& {return _d[i * n + j]; };

		cout << "weight : ";
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "w(" << it->i << "," << it->j << ")=" << it->w << " ";
		cout << endl;

		APSP_johnson(g, _d);
		cout << "johnson distance : " << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if (d(i, j) < INF)
					cout << "d(" << i << "," << j << ")=" << d(i, j) << " ";
				else
					cout << "d(" << i << "," << j << ")=" << "inf" << " ";
			cout << endl;
		}

		delete[] _d;
	}
	// test flow
	{
		cout << "---- test flow ----" << endl;
		GraphFlow g;
		for (int i = 0; i < 6; i++)
			g.add_vertex(Vertex());
		g.add_edge(0, 1, EdgeFlow(16));
		g.add_edge(0, 2, EdgeFlow(13));
		g.add_edge(2, 1, EdgeFlow(4));
		g.add_edge(1, 3, EdgeFlow(12));
		g.add_edge(2, 4, EdgeFlow(14));
		g.add_edge(3, 2, EdgeFlow(9));
		g.add_edge(4, 3, EdgeFlow(7));
		g.add_edge(3, 5, EdgeFlow(20));
		g.add_edge(4, 5, EdgeFlow(4));

		flow_edmonds_karp(g, 0, 5);
		int f = 0;
		for (auto it = g.begin_edge(0); it != g.end_edge(0); it++)
			f += it->f;
		cout << "edmonds karp max flow: " << f << endl;
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->f << "/" << it->c << ") ";
		cout << endl;

		flow_push_relabel(g, 0, 5);
		f = 0;
		for (auto it = g.begin_edge(0); it != g.end_edge(0); it++)
			f += it->f;
		cout << "push relabel max flow: " << f << endl;
		for (auto it = g.begin_edge(); it != g.end_edge(); it++)
			cout << "(" << it->i << "," << it->j << ")(" << it->f << "/" << it->c << ") ";
		cout << endl;
	}
	// test LP
	{
		cout << "---- test LP ----" << endl;
		LPStandard lp_s(LPSize(3, 3));
		lp_s.C << 3 << 1 << 2;
		lp_s.A << 1 << 1 << 3; lp_s.B << 30;
		lp_s.A << 2 << 2 << 5; lp_s.B << 24;
		lp_s.A << 4 << 1 << 2; lp_s.B << 36;
		cout << "..LP Standard:" << endl;
		lp_s.print();

		LPAugmented lp_a(lp_s);
		cout << "..LP Augmented:" << endl;
		lp_a.print();

		LPAugmented lp_a2 = lp_a;
		LP_pivot(lp_a2, 2, 0);
		cout << "..pivot 1 times:" << endl;
		lp_a2.print();

		LP_pivot(lp_a2, 2, 5);
		cout << "..pivot 2 times:" << endl;
		lp_a2.print();

		LPAugmented lp_a_init = LP_simplex_init(lp_s);
		cout << "..init: " << lp_a_init.feasible << endl;
		lp_a_init.print();

		LPAugmented lp_a_solve = LP_simplex(lp_s);
		cout << "..solve: "<<lp_s.optimal << endl;
		lp_a_solve.print();
		cout << "X = "; for (int i = 0; i < lp_s.X.rows; i++) cout << lp_s.X[i] << " "; cout << endl;
		cout << "z = " << lp_a_solve.v << endl;

		LPStandard lp_s2(LPSize(2, 2));
		lp_s2.C << 2 << -1;
		lp_s2.A << 2 << -1; lp_s2.B << 2;
		lp_s2.A << 1 << -5; lp_s2.B << -4;
		cout << "..LP Standard:" << endl;
		lp_s2.print();

		LPAugmented lp_a2_init = LP_simplex_init(lp_s2);
		cout << "..init: " << lp_a2_init.feasible << endl;
		lp_a2_init.print();

		LPAugmented lp_a2_solve = LP_simplex(lp_s2);
		cout << "..solve: " << lp_s2.optimal << endl;
		lp_a2_solve.print();
		cout << "X = "; for (int i = 0; i < lp_s2.X.rows; i++) cout << lp_s2.X[i] << " "; cout << endl;
		cout << "z = " << lp_a2_solve.v << endl;

		LPStandard lp_s3(LPSize(3, 2));
		lp_s3.C << 1 << 3;
		lp_s3.A << -1 << 1; lp_s3.B << -1;
		lp_s3.A << -1 << -1; lp_s3.B << -3;
		lp_s3.A << -1 << 4; lp_s3.B << 2;
		cout << "..LP Standard:" << endl;
		lp_s3.print();

		LPAugmented lp_a3_solve = LP_simplex(lp_s3);
		cout << "..solve: " << lp_s3.optimal << endl;
		lp_a3_solve.print();
		cout << "X = "; for (int i = 0; i < lp_s3.X.rows; i++) cout << lp_s3.X[i] << " "; cout << endl;
		cout << "z = " << lp_a3_solve.v << endl;

		LPStandard lp_s4(LPSize(3, 2));
		lp_s4.C << 1 << -2;
		lp_s4.A << 1 << 2; lp_s4.B << 4;
		lp_s4.A << -2 << -6; lp_s4.B << -12;
		lp_s4.A << 0 << 1; lp_s4.B << 1;
		cout << "..LP Standard:" << endl;
		lp_s4.print();

		LPAugmented lp_a4_solve = LP_simplex(lp_s4);
		cout << "..solve: " << lp_s4.optimal << endl;
		lp_a4_solve.print();
		cout << "X = "; for (int i = 0; i < lp_s4.X.rows; i++) cout << lp_s4.X[i] << " "; cout << endl;
		cout << "z = " << lp_a4_solve.v << endl;
	}
	// test FFT
	{
		cout << "---- test FFT ----" << endl;
		auto func = [](double x)
		{ return 1 + 2 * std::sin(2 * PI * x * 1) + 3 * std::sin(2 * PI * x * 2) + 4 * std::sin(2 * PI * x * 3); };
		const int n = 32;
		Complex f[n];
		Complex g[n];
		Complex f_[n];
		for (int i = 0; i < n; i++)
			f[i] = func((double)i / n);
		cout << "f:  "; for (int i = 0; i < n; i++) cout << f[i] << " "; cout << endl;

		cout << "DFT:" << endl;
		DFT(f, g, n);
		DFT_inv(g, f_, n);
		cout << "g:  "; for (int i = 0; i < n; i++) cout << g[i] << " "; cout << endl;
		cout << "f_: "; for (int i = 0; i < n; i++) cout << f_[i] << " "; cout << endl;

		cout << "FFT:" << endl;
		FFT_recursive(f, g, n);
		FFT_inv_recursive(g, f_, n);
		cout << "g:  "; for (int i = 0; i < n; i++) cout << g[i] << " "; cout << endl;
		cout << "f_: "; for (int i = 0; i < n; i++) cout << f_[i] << " "; cout << endl;

		Complex a0[4]{ 2,5,0,0 }; // 2+5x
		Complex b0[4]{ 4,3,0,0 }; // 4+3x
		Complex c0[4]; // =a0xb0=8+26x+15x^2
		Complex a1[4], b1[4], c1[4];
		FFT_recursive(a0, a1, 4);
		FFT_recursive(b0, b1, 4);
		for (int i = 0; i < 4; i++)
			c1[i] = a1[i] * b1[i];
		FFT_inv_recursive(c1, c0, 4);
		cout << "a0:  "; for (int i = 0; i < 4; i++) cout << a0[i] << " "; cout << endl;
		cout << "b0:  "; for (int i = 0; i < 4; i++) cout << b0[i] << " "; cout << endl;
		cout << "c0:  "; for (int i = 0; i < 4; i++) cout << c0[i] << " "; cout << endl;

		cout << "original:" << endl;
		cout << "f:  "; for (int i = 0; i < n; i++) cout << f[i] << " "; cout << endl;
		cout << "g:  "; for (int i = 0; i < n; i++) cout << g[i] << " "; cout << endl;

		const int n2 = n * 4;
		Complex f2[n2];
		Complex g2[n2];
		for (int i = 0; i < n2; i++)
			f2[i] = func((double)i / n);
		FFT_recursive(f2, g2, n2);
		cout << "repeat four times:" << endl;
		cout << "f2: "; for (int i = 0; i < n2; i++) cout << f2[i] << " "; cout << endl;
		cout << "g2: "; for (int i = 0; i < n2; i++) cout << g2[i] << " "; cout << endl;

		const int n3 = n2;
		Complex f3[n3];
		Complex g3[n3];
		for (int i = 0; i < n3; i++)
			f3[i] = func((double)i / n * 1.1);
		FFT_recursive(f3, g3, n3);
		cout << "repeat less than four times and unaligned border:" << endl;
		cout << "f3: "; for (int i = 0; i < n3; i++) cout << f3[i] << " "; cout << endl;
		cout << "g3: "; for (int i = 0; i < n3; i++) cout << g3[i] << " "; cout << endl;

		const int n4 = n2;
		Complex f4[n4];
		Complex g4[n4];
		std::default_random_engine rand_e((unsigned int)time(0));
		std::uniform_real_distribution<> rand(-0.5, 0.5);
		for (int i = 0; i < n4; i++)
			f4[i] = f2[i] + rand(rand_e);
		FFT_recursive(f4, g4, n4);
		cout << "repeat four times + noise:" << endl;
		cout << "f4: "; for (int i = 0; i < n4; i++) cout << f4[i] << " "; cout << endl;
		cout << "g4: "; for (int i = 0; i < n4; i++) cout << g4[i] << " "; cout << endl;

		const int n5 = n4;
		Complex f5[n5];
		Complex g5[n5];
		for (int i = 0; i < n5; i++)
			f5[i] = func((double)i / n * 1.1) + rand(rand_e);
		FFT_recursive(f5, g5, n5);
		cout << "repeat less than four times and unaligned border + noise:" << endl;
		cout << "f5: "; for (int i = 0; i < n5; i++) cout << f5[i] << " "; cout << endl;
		cout << "g5: "; for (int i = 0; i < n5; i++) cout << g5[i] << " "; cout << endl;

		auto func2 = [](double x) { return (x == 0 ? 1 : std::sin(2 * PI * x) / (2 * PI * x)); };
		const int n6 = 64;
		Complex f6[n6];
		Complex g6[n6];
		for (int i = 0; i < n6; i++)
			f6[i] = func2(4.0 * i / n6 - 2);
		FFT_recursive(f6, g6, n6);
		cout << "sin(x)/x [N=64,L=4]:" << endl;
		cout << "f6: "; for (int i = 0; i < n6; i++) cout << f6[i] << " "; cout << endl;
		cout << "g6: "; for (int i = 0; i < n6; i++) cout << g6[i] << " "; cout << endl;

		const int n7 = 128;
		Complex f7[n7];
		Complex g7[n7];
		for (int i = 0; i < n7; i++)
			f7[i] = func2(4.0 * i / n7 - 2);
		FFT_recursive(f7, g7, n7);
		cout << "sin(x)/x [N=128,L=4]:" << endl;
		cout << "f7: "; for (int i = 0; i < n7; i++) cout << f7[i] << " "; cout << endl;
		cout << "g7: "; for (int i = 0; i < n7; i++) cout << g7[i] << " "; cout << endl;

		const int n8 = 128;
		Complex f8[n8];
		Complex g8[n8];
		for (int i = 0; i < n8; i++)
			f8[i] = func2(8.0 * i / n8 - 4);
		FFT_recursive(f8, g8, n8);
		cout << "sin(x)/x [N=128,L=8]:" << endl;
		cout << "f8: "; for (int i = 0; i < n8; i++) cout << f8[i] << " "; cout << endl;
		cout << "g8: "; for (int i = 0; i < n8; i++) cout << g8[i] << " "; cout << endl;
	}

	return 0;
}

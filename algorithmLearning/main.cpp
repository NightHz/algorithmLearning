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

	return 1;
}

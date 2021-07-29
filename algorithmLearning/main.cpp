#include <iostream>
#include "sort.h"
#include "heap.h"
#include "data_structure.h"
#include "hash_table.h"
#include "binary_search_tree.h"
#include "rb_tree.h"

void find_maximum_subarray(const int *p, int n, int &il, int &ir, int &s)
{
	if (n <= 1)
		il = 0, ir = 0;
	else
	{
		int ln = n / 2;
		int rn = n - ln;
		int lil, lir, ls, ril, rir, rs;
		find_maximum_subarray(p, ln, lil, lir, ls);
		find_maximum_subarray(p + ln, rn, ril, rir, rs);
		// crossing mid
		int i, s2;
		for (il = ln - 1, s = p[il], i = il - 1,s2=s; i >= 0; i--)
		{
			s2 += p[i];
			if (s2 > s)
				il = i, s = s2;
		}
		for (ir = ln, s = s + p[ir], i = ir + 1, s2 = s; i < n; i++)
		{
			s2 += p[i];
			if (s2 > s)
				ir = i, s = s2;
		}
		// judge
		if (ls >= rs && ls >= s)
			il = lil, ir = lir, s = ls;
		else if (rs >= ls && rs >= s)
			il = ril+ln, ir = rir+ln, s = rs;
	}
}

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

		Queue q;
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

	return 1;
}

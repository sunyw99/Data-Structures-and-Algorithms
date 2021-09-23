/*#include <iostream>
#include "d_ary_heap.h"
using namespace std;

int main() {
	int a[] = {1,2,6,3,7,2,4,5,2,3,1,2,7,3,9};
	int i;
	int size = sizeof(a) / sizeof(int);
	cout << "Input: ";
	for (i = 0; i < size; i++)
		cout << a[i] << " " << flush;
	cout << endl;

	d_ary_heap* pqs = new d_ary_heap(5);
	for (i = 0; i < size; i++) pqs->enqueue(a[i]);

	cout << "Sort in ascending order: " << flush;
	for (i = 0; i < size; i++)
	{
		int val = pqs->dequeue_min();
		cout << val << " ";
	}
	cout << endl;

	delete pqs;
	return 0;
}*/
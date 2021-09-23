#ifndef D_ARY_HEAP_H
#define D_ARY_HEAP_H

#include <functional>
#include <vector>
#include <algorithm>

class d_ary_heap {
public:
	d_ary_heap(int d);
	~d_ary_heap() {}
	void enqueue(int k);
	int dequeue_min();
private:
	int d;
	std::vector<int> data;
	void swap(int& a, int& b);
	void perculateUp(int id);
	void perculateDown(int id);
};

d_ary_heap::d_ary_heap(int d) :d(d)
{
}

void d_ary_heap::swap(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void d_ary_heap::perculateUp(int id) {
	while (id > 0 && data[id] < data[(id - 1) / d]) {
		swap(data[(id - 1) / d], data[id]);
		id = (id - 1) / d;
	}
}

void d_ary_heap::perculateDown(int id) {
	int i, j, temp_min_at;
	for (j = d * (id + 1) - d + 1; j < data.size(); j = d * (id + 1) - d + 1) {
		temp_min_at = j;
		for (i = j + 1; i < j + d; i++) {
			if (i < data.size() && data[i] < data[temp_min_at]) temp_min_at = i;
		}
		j = temp_min_at;
		if (data[id] <= data[j]) break;
		swap(data[id], data[j]);
		id = j;
	}
}

void d_ary_heap::enqueue(int k) {
	data.push_back(k);
	perculateUp(data.size() - 1);
}

int d_ary_heap::dequeue_min() {
	int min;
	min = data[0];
	swap(data[0], data[data.size() - 1]);
	data.pop_back();
	perculateDown(0);
	return min;
}

#endif//D_ARY_HEAP_H
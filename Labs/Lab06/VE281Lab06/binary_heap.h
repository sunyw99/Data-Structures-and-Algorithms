#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <functional>
#include <vector>
#include <algorithm>

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap {
public:
	typedef unsigned size_type;
	~binary_heap() {}
	binary_heap(COMP comp = COMP());
	void enqueue(const TYPE& val);
	TYPE dequeue_min();
	const TYPE& get_min() const;
	size_type size() const;
	bool empty() const;
private:
	std::vector<TYPE> data;
	COMP compare;
private:
	void swap(TYPE& a, TYPE& b);
	void perculateUp(int id);
	void perculateDown(int id);
};

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::swap(TYPE& a, TYPE& b) {
	TYPE temp;
	temp = a;
	a = b;
	b = temp;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::perculateUp(int id) {
	while (id > 0 && compare(this->data[id], this->data[(id + 1) / 2 - 1])) {
		swap(this->data[(id + 1) / 2 - 1], this->data[id]);
		id = (id + 1) / 2 - 1;
	}
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::perculateDown(int id) {
	unsigned int j;
	for (j = 2 * (id + 1) - 1; j < this->data.size(); j = 2 * (id + 1) - 1) {
		if (j < this->data.size() - 1 && compare(this->data[j + 1], this->data[j])) j++;
		if (!compare(this->data[j], this->data[id])) break;
		swap(this->data[id], this->data[j]);
		id = j;
	}
}

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> ::binary_heap(COMP comp) {
	compare = comp;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> ::enqueue(const TYPE& val) {
	this->data.push_back(val);
	perculateUp(this->data.size() - 1);
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> ::dequeue_min() {
	TYPE min;
	min = this->data[0];
	swap(this->data[0], this->data[this->data.size() - 1]);
	this->data.pop_back();
	perculateDown(0);
	return min;
}

template<typename TYPE, typename COMP>
const TYPE& binary_heap<TYPE, COMP> ::get_min() const {
	return this->data[0];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> ::empty() const {
	return this->data.empty();
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> ::size() const {
	return this->data.size();
}

#endif //BINARY_HEAP_H
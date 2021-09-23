#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a 
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap : public priority_queue<TYPE, COMP> {
public:
	typedef unsigned size_type;

	// EFFECTS: Construct an empty heap with an optional comparison functor.
	//          See test_heap.cpp for more details on functor.
	// MODIFIES: this
	// RUNTIME: O(1)
	fib_heap(COMP comp = COMP());

	// EFFECTS: Deconstruct the heap with no memory leak.
	// MODIFIES: this
	// RUNTIME: O(n)
	~fib_heap();

	// EFFECTS: Add a new element to the heap.
	// MODIFIES: this
	// RUNTIME: O(1)
	virtual void enqueue(const TYPE& val);

	// EFFECTS: Remove and return the smallest element from the heap.
	// REQUIRES: The heap is not empty.
	// MODIFIES: this
	// RUNTIME: Amortized O(log(n))
	virtual TYPE dequeue_min();

	// EFFECTS: Return the smallest element of the heap.
	// REQUIRES: The heap is not empty.
	// RUNTIME: O(1)
	virtual const TYPE& get_min() const;

	// EFFECTS: Get the number of elements in the heap.
	// RUNTIME: O(1)
	virtual size_type size() const;

	// EFFECTS: Return true if the heap is empty.
	// RUNTIME: O(1)
	virtual bool empty() const;

private:
	// Note: compare is a functor object
	COMP compare;

private:
	struct node {
		TYPE key;
		node* parent;
		node* child;
		node* left;
		node* right;
		int rank;
	};
	int num;
	node* MinNode;

	void destruct();
	void Consolidate();
	void Link(node* y, node* x);
};

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::Link(node* y, node* x) {
	y->left->right = y->right;
	y->right->left = y->left;
	y->parent = x;
	if (x->child != NULL) {
		y->left = x->child;
		y->right = x->child->right;
		x->child->right->left = y;
		x->child->right = y;
	}
	else {
		y->left = y;
		y->right = y;
		x->child = y;
	}
	x->rank++;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::Consolidate() {
	int size = floor(log(this->num) / log(1.618)) + 1;
	node* A[size];
	node* start = this->MinNode;
	A[this->MinNode->rank] = this->MinNode;
	node* next = this->MinNode->right;
	int num_root = 1;
	for (int i = 0; i < size; i++) A[i] = NULL;
	while (next != start) {
		num_root++;
		next = next->right;
	}
	for (int i = 0; i < num_root; i++) {
		node* x = next;
		next = x->right;
		int d = x->rank;
		while (A[d] != NULL) {
			node* y = A[d];
			if (compare(y->key, x->key)) {
				node* temp = y;
				y = x;
				x = temp;
			}
			Link(y, x);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
	}
	this->MinNode = NULL;
	for (int i = 0; i < size; i++) {
		if (A[i] != NULL) {
			if (this->MinNode == NULL) {
				this->MinNode = A[i];
				this->MinNode->left = this->MinNode;
				this->MinNode->right = this->MinNode;
				this->MinNode->parent = NULL;
			}
			else {
				A[i]->left = this->MinNode;
				A[i]->right = this->MinNode->right;
				A[i]->parent = NULL;
				this->MinNode->right->left = A[i];
				this->MinNode->right = A[i];
				if (compare(A[i]->key, this->MinNode->key)) this->MinNode = A[i];
			}
		}
	}
}


template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> ::fib_heap(COMP comp) {
	compare = comp;
	num = 0;
	MinNode = NULL;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::enqueue(const TYPE& val) {
	node* x = new node;
	x->key = val;
	x->parent = NULL;
	x->child = NULL;
	x->rank = 0;

	if (this->MinNode == NULL) {
		x->left = x;
		x->right = x;
		this->MinNode = x;
	}
	else {
		x->left = this->MinNode;
		x->right = this->MinNode->right;
		this->MinNode->right->left = x;
		this->MinNode->right = x;
		if (compare(x->key, this->MinNode->key)) this->MinNode = x;
	}
	this->num++;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> ::dequeue_min() {
	TYPE min;
	min = this->MinNode->key;
	if (this->MinNode->child != NULL) {
		while (this->MinNode->child->right != this->MinNode->child) {
			node* temp1;
			temp1 = this->MinNode->child->right;
			this->MinNode->child->right->right->left = this->MinNode->child;
			this->MinNode->child->right = this->MinNode->child->right->right;
			temp1->left = this->MinNode;
			temp1->right = this->MinNode->right;
			temp1->parent = NULL;
			this->MinNode->right->left = temp1;
			this->MinNode->right = temp1;
		}
		node* temp2;
		temp2 = this->MinNode->child;
		temp2->left = this->MinNode;
		temp2->right = this->MinNode->right;
		temp2->parent = NULL;
		this->MinNode->right->left = temp2;
		this->MinNode->right = temp2;
		this->MinNode->child = NULL;
	}
	node* temp3 = this->MinNode;
	this->MinNode->left->right = this->MinNode->right;
	this->MinNode->right->left = this->MinNode->left;
	this->num--;
	if (this->num == 0) this->MinNode = NULL;
	else {
		node* newmin = this->MinNode->right;
		node* stay = newmin;
		node* find = newmin->right;
		while (find != stay) {
			if (compare(find->key, newmin->key)) newmin = find;
			find = find->right;
		}
		this->MinNode = newmin;
		Consolidate();
	}
	delete temp3;
	return min;
}


template<typename TYPE, typename COMP>
const TYPE& fib_heap<TYPE, COMP> ::get_min() const {
	return this->MinNode->key;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> ::empty() const {
	return (this->MinNode == NULL);
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> ::size() const {
	return this->num;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::destruct() {
	if (this->MinNode == NULL) return;
	bool hasRight = false, hasChild = false;
	node* current = this->MinNode;
	if (current->right != current) hasRight = true;
	if (current->child != NULL) hasChild = true;
	if (current->parent != NULL && current->parent->child == current) {
		if (current->right != current) {
			current->parent->child = current->right;
		}
		else current->parent->child = NULL;
	}
	if (current->right != current) {
		current->right->left = current->left;
		current->left->right = current->right;
	}
	if (hasRight) {
		this->MinNode = current->right;
		destruct();
	}
	if (hasChild) {
		this->MinNode = current->child;
		destruct();
	}
	delete current;
	return;
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> ::~fib_heap() {
	destruct();
}

#endif //FIB_HEAP_H

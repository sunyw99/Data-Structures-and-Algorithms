/*#include <iostream>
#include <string>
#include "binary_heap.h"
using namespace std;

struct compare_t
{
	bool operator()(int a, int b) const
	{
		return a > b;
	}
};

int main() {
	string input;
	int newInt, count, current_mean;
	float new_mean;
	binary_heap<int, compare_t>* data1 = new binary_heap<int, compare_t>;
	binary_heap<int>* data2 = new binary_heap<int>;
	cin >> input;
	newInt = stoi(input);
	data1->enqueue(newInt);
	count = 1;
	cout << "mean: " << newInt << " " << endl;
	while (cin >> input) {
		if (input == "q") break;
		newInt = stoi(input);
		if (count % 2 == 1) {
			current_mean = data1->dequeue_min();
			if (newInt < current_mean) {
				data1->enqueue(newInt);
				data2->enqueue(current_mean);
				new_mean = ((float)current_mean + (float)data1->get_min()) / 2;
			}
			else {
				data2->enqueue(newInt);
				data1->enqueue(current_mean);
				new_mean = ((float)data1->get_min() + (float)data2->get_min()) / 2;
			}
		}
		else {
			current_mean = data2->dequeue_min();
			if (newInt < current_mean) {
				data1->enqueue(newInt);
				data2->enqueue(current_mean);
				new_mean = data1->get_min();
			}
			else {
				data2->enqueue(newInt);
				data1->enqueue(current_mean);
				new_mean = data1->get_min();
			}
		}
		count++;
		cout << "mean: " << new_mean << " " << endl;
	}
	return 0;
}*/
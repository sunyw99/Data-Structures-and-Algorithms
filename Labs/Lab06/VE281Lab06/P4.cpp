#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

bool verifySquenceOfBST(vector<int> sequence)
{
	int root, i, j;
	vector<int> temp;
	vector<int> right;
	if (sequence.size() == 0 || sequence.size() == 1) return true;
	root = sequence[sequence.size() - 1];
	sequence.pop_back();
	i = sequence.size() - 1;
	while (i >= 0 && sequence[i] > root) {
		temp.push_back(sequence[i]);
		sequence.pop_back();
		i--;
	}
	for (j = temp.size() - 1; j >= 0; j--) right.push_back(temp[j]);
	while (i >= 0 && sequence[i] < root) i--;
	if (i != -1) return false;
	else return (verifySquenceOfBST(sequence) && verifySquenceOfBST(right));
}

int main() {
	vector<int> a;
	a.push_back(3);
	a.push_back(1);
	a.push_back(2);
	a.push_back(5);
	a.push_back(7);
	a.push_back(6);
	a.push_back(4);
	cout << verifySquenceOfBST(a);
}
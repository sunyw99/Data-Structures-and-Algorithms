#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>
using namespace std;

int main() {
	unsigned int i, j, width, height;
	srand48(time(0));
	cin >> width >> height;
	cout << width << endl;
	cout << height << endl;
	cout << 0 << " " << 0 << endl;
	cout << width - 1 << " " << height - 1 << endl;
	for (i = 0; i < height-1; i++) {
		for (j = 0; j < width - 1; j++) {
			cout << abs(mrand48() % 1000) << " ";
		}
		cout << mrand48() << endl;
	}
	return 0;
}
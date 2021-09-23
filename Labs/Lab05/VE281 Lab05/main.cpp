#include <iostream>
#include <fstream>
#include <getopt.h>
#include <ctime>
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"
using namespace std;

struct point {
	int location_x, location_y;
	unsigned int cellweight;
	unsigned int pathcost;
	bool Reached;
	point* predecessor;
};

struct compare_t
{
	bool operator()(point* a, point* b) const
	{
		if (a->pathcost == b->pathcost) {
			if (a->location_x == b->location_x) return a->location_y < b->location_y;
			else return a->location_x < b->location_x;
		}
		else return a->pathcost < b->pathcost;
	}
};

void trace_back_path(point *current) {
	if (current->predecessor == NULL) cout << "(" << current->location_x << ", " << current->location_y << ")" << endl;
	else {
		trace_back_path(current->predecessor);
		cout << "(" << current->location_x << ", " << current->location_y << ")" << endl;
	}
}

void print(point& start, point& end) {
	cout << "The shortest path from (" << start.location_x << ", " << start.location_y << ") to (" << end.location_x << ", " << end.location_y << ") is " << end.pathcost << "." << endl;
	cout << "Path:" << endl;
	point *end_p = &end;
	trace_back_path(end_p);
}

void findPath(priority_queue<point*, compare_t>* PQ, bool verbose) {
	int i, j, step = 0;
	int width, height, start_x, start_y, end_x, end_y;

	cin >> width >> height >> start_x >> start_y >> end_x >> end_y;
	point** W = new point*[height];
	for (i = 0; i < height; i++) {
		W[i] = new point[width];
		for (j = 0; j < width; j++) {
			cin >> W[i][j].cellweight;
			W[i][j].location_y = i;
			W[i][j].location_x = j;
			W[i][j].pathcost = 0;
			W[i][j].Reached = false;
			W[i][j].predecessor = NULL;
		}
	}
	W[start_y][start_x].pathcost = W[start_y][start_x].cellweight;
	W[start_y][start_x].Reached = true;
	PQ->enqueue(&W[start_y][start_x]);
	while (!PQ->empty()) {
		if (verbose) cout << "Step " << step << endl;
		step++;
		point* C = PQ->dequeue_min();
		if (verbose) cout << "Choose cell (" << C->location_x << ", " << C->location_y << ") with accumulated length " << C->pathcost << "." << endl;
		if (C->location_x + 1 < width && (!W[C->location_y][C->location_x + 1].Reached)) {
			point* N1 = &W[C->location_y][C->location_x + 1];
			N1->pathcost = C->pathcost + N1->cellweight;
			N1->Reached = true;
			N1->predecessor = C;
			if (N1->location_y == end_y && N1->location_x == end_x) {
				if (verbose) cout << "Cell (" << N1->location_x << ", " << N1->location_y << ") with accumulated length " << N1->pathcost << " is the ending point." << endl;
				cout << "The shortest path from (" << W[start_y][start_x].location_x << ", " << W[start_y][start_x].location_y << ") to (" << N1->location_x << ", " << N1->location_y << ") is " << N1->pathcost << "." << endl;
				cout << "Path:" << endl;
				trace_back_path(N1);
				return;
			}
			else if (verbose) {
				cout << "Cell (" << N1->location_x << ", " << N1->location_y << ") with accumulated length " << N1->pathcost << " is added into the queue." << endl;
				PQ->enqueue(N1);
			}
			else PQ->enqueue(N1);
		}
		if (C->location_y + 1 < height && (!W[C->location_y + 1][C->location_x].Reached)) {
			point* N2 = &W[C->location_y + 1][C->location_x];
			N2->pathcost = C->pathcost + N2->cellweight;
			N2->Reached = true;
			N2->predecessor = C;
			if (N2->location_y == end_y && N2->location_x == end_x) {
				if (verbose) cout << "Cell (" << N2->location_x << ", " << N2->location_y << ") with accumulated length " << N2->pathcost << " is the ending point." << endl;
				cout << "The shortest path from (" << W[start_y][start_x].location_x << ", " << W[start_y][start_x].location_y << ") to (" << N2->location_x << ", " << N2->location_y << ") is " << N2->pathcost << "." << endl;
				cout << "Path:" << endl;
				trace_back_path(N2);
				return;
			}
			else if (verbose) {
				cout << "Cell (" << N2->location_x << ", " << N2->location_y << ") with accumulated length " << N2->pathcost << " is added into the queue." << endl;
				PQ->enqueue(N2);
			}
			else PQ->enqueue(N2);
		}
		if (C->location_x > 0 && (!W[C->location_y][C->location_x - 1].Reached)) {
			point* N3 = &W[C->location_y][C->location_x - 1];
			N3->pathcost = C->pathcost + N3->cellweight;
			N3->Reached = true;
			N3->predecessor = C;
			if (N3->location_y == end_y && N3->location_x == end_x) {
				if (verbose) cout << "Cell (" << N3->location_x << ", " << N3->location_y << ") with accumulated length " << N3->pathcost << " is the ending point." << endl;
				cout << "The shortest path from (" << W[start_y][start_x].location_x << ", " << W[start_y][start_x].location_y << ") to (" << N3->location_x << ", " << N3->location_y << ") is " << N3->pathcost << "." << endl;
				cout << "Path:" << endl;
				trace_back_path(N3);
				return;
			}
			else if (verbose) {
				cout << "Cell (" << N3->location_x << ", " << N3->location_y << ") with accumulated length " << N3->pathcost << " is added into the queue." << endl;
				PQ->enqueue(N3);
			}
			else PQ->enqueue(N3);
		}
		if (C->location_y > 0 && (!W[C->location_y - 1][C->location_x].Reached)) {
			point* N4 = &W[C->location_y - 1][C->location_x];
			N4->pathcost = C->pathcost + N4->cellweight;
			N4->Reached = true;
			N4->predecessor = C;
			if (N4->location_y == end_y && N4->location_x == end_x) {
				if (verbose) cout << "Cell (" << N4->location_x << ", " << N4->location_y << ") with accumulated length " << N4->pathcost << " is the ending point." << endl;
				cout << "The shortest path from (" << W[start_y][start_x].location_x << ", " << W[start_y][start_x].location_y << ") to (" << N4->location_x << ", " << N4->location_y << ") is " << N4->pathcost << "." << endl;
				cout << "Path:" << endl;
				trace_back_path(N4);
				return;
			}
			else if (verbose) {
				cout << "Cell (" << N4->location_x << ", " << N4->location_y << ") with accumulated length " << N4->pathcost << " is added into the queue." << endl;
				PQ->enqueue(N4);
			}
			else PQ->enqueue(N4);
		}
	}
}

void create_unsorted(bool verbose) {
	priority_queue<point*, compare_t>* PQ = new unsorted_heap<point*, compare_t>;
	findPath(PQ, verbose);
	delete PQ;
}

void create_binary(bool verbose) {
	priority_queue<point*, compare_t>* PQ = new binary_heap<point*, compare_t>;
	findPath(PQ, verbose);
	delete PQ;
}

void create_fib(bool verbose) {
	priority_queue<point*, compare_t>* PQ = new fib_heap<point*, compare_t>;
	findPath(PQ, verbose);
	delete PQ;
}

int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	bool verbose = false;
	int c, type;
	while (1) {
		static struct option long_options[] = {
		{"verbose", no_argument, 0,'v'},
		{"implementation", required_argument, 0,'i'},
		{0,0,0,0}
		};
		int option_index = 0;
		c = getopt_long(argc, argv, "vi:", long_options, &option_index);
		if (c == -1) break;
		switch (c) {
			case 'v':
				verbose = true;
				break;
			case 'i':
				if (string(optarg) == "UNSORTED") type = 1;
				else if (string(optarg) == "BINARY") type = 2;
				else if (string(optarg) == "FIBONACCI") type = 3;
				break;
			default:
				abort();
		}
	}
	if (type == 1) {
		create_unsorted(verbose);
	}
	else if (type == 2) {
		create_binary(verbose);
	}
	else if (type == 3) {
		create_fib(verbose);
	}
	return 0;
}

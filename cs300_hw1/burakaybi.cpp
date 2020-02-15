#include "heap.h"
#include <fstream>
#include <algorithm>
using namespace std;
enum type{start, endd};
struct allInfo {
	int x;
	int label;
	type t;
	int length;
};

bool op(allInfo & first, allInfo & second) {
	/*
	true if:
		x is smaller
		x is same and they have the same side with left is longer
		ix is same and they are in different side with left is in left side
	false otherwise
	*/
	bool result = false;
	if (first.x < second.x) {
		result = true;
	}
	else {
		if (first.x > second.x) {
			result = false;
		}
		else {
			if (first.t == second.t) {
				if (first.length > second.length) {
					result = true;
				}
				else {
					result = false;
				}
			}
			else {
				if (first.t == start) {
					result = true;
				}
				else {
					result = false;
				}
			}
		}
	}
	return result;
}
vector<allInfo> everyVector;

void giveOutput(BinaryHeap<int> & heap) {
	/*
	Generates the output from the vector that contains all the information
	*/
	if (everyVector[0].x != 0) {
		cout << "0 0" << endl;
	}
	int maxx = -1;
	int lastX = -1;
	for (int i = 0; i < everyVector.size(); i++) {
		allInfo info = everyVector[i];
		if (info.t == start) {
			heap.insert(info.length, info.label);
		}
		else {
			heap.Remove(info.label);
		}
		if (heap.GetMax() != maxx) {
			if (info.x != lastX) {
				cout << info.x << " " << heap.GetMax() << endl;	//if the new x value is unique i.e bigger than previous one
			}
			maxx = heap.GetMax();
			lastX = info.x;
		}
	}
}

void fillVector() {
	/*
	Reads the input file and fills the vector with respect to the input file
	Then invokes the output function in order to solve the skyline problem and
	give output
	*/
	ifstream input("input.txt");
	string line;
	int row;
	getline(input, line);
	row = stoi(line);	//taking as int
	for (int i = 0; i < row; i++) {
		int xS, L, xE;
		input >> xS >> L >> xE;
		allInfo lhs;
		lhs.label = i;
		lhs.length = L;
		lhs.t = start;
		lhs.x = xS;
		allInfo rhs;
		rhs.label = i;
		rhs.length = L;
		rhs.t = endd;
		rhs.x = xE;
		everyVector.push_back(lhs);	//left hand side
		everyVector.push_back(rhs);	//right hand side
	}
	sort(everyVector.begin(), everyVector.end(), op);	//sorting is necessarry
	BinaryHeap<int> heap(row * 2);
	giveOutput(heap);
}

int main() {
	fillVector();
	return 0;
}
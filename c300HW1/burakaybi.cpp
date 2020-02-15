#include <iostream>
#include <fstream>
#include "Classes.h"
TwoDimTreeNode * read(string file) {
	/*
	Reads the file with given filename
	Returns a tree containing the rectangles in the file
	*/
	ifstream iff(file.c_str());
	int top, left, bottom, right;
	iff >> top >> left >> bottom >> right;
	TwoDimTreeNode * tree = new TwoDimTreeNode(top, left, bottom, right);
	while (true) {
		iff >> top;
		if (top > -1) {
			iff >> left >> bottom >> right;
			Rectangle add(top, left, bottom, right);
			tree->add(add);
		}
		else {
			return tree;
		}
	}
	return tree;

}
int main() {
	TwoDimTreeNode * tree = read("recdb.txt");
	vector<vector<int>> xy;
	int x, y;
	while (cin >> x >> y) {
		if (x == -1) {
			break;
		}
		else {
			vector<int> arr;
			arr.push_back(x);
			arr.push_back(y);
			xy.push_back(arr);
		}
	}
	for (int i = 0; i < xy.size(); i++) {
		tree->findAndPrint(xy[i][0], xy[i][1]);	//Just using the function of tree
	}
	return 0;
}
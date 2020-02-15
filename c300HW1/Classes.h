#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Rectangle {
public:
	void printRectangle();
	Rectangle(int top, int left, int bottom, int right);
	int ver();
	int hor();
private:
	int top;
	int left;
	int bottom;
	int right;
	friend class TwoDimTreeNode;
};

class TwoDimTreeNode {
public:
	string topLeft(int x, int y);
	string topRight(int x, int y);
	string bottomLeft(int x, int y);
	string bottomRight(int x, int y);
	TwoDimTreeNode * search(int x, int y, vector<Rectangle> & ver, vector<Rectangle> & hor);
	void findAndPrint(int x, int y);
	TwoDimTreeNode(int top, int left, int bottom, int right);
	void add(Rectangle & rectangle);
	bool testPoint(int x, int y);
	bool horizontalMatch(Rectangle & rectangle);
	bool verticalMatch(Rectangle & rectangle);
private:
	int size;
	Rectangle Extent;
	TwoDimTreeNode *TopLeft = nullptr;
	TwoDimTreeNode *TopRight = nullptr;
	TwoDimTreeNode *BottomLeft = nullptr;
	TwoDimTreeNode *BottomRight = nullptr;
	vector<Rectangle> Horizontal;
	vector<Rectangle> Vertical;
};
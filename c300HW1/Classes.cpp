#include "Classes.h"

void Rectangle::printRectangle()
{
	/*
	Prints the rectangle in the order of top, left, bottom, right
	*/
	cout << this->top << " " << this->left << " " << this->bottom << " " << this->right << endl;
}

Rectangle::Rectangle(int top, int left, int bottom, int right) {
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;
}

int Rectangle::ver() {
	/*
	Returns vertical center
	*/
	int a = bottom + top;
	return a / 2;
}

int Rectangle::hor() {
	/*
	Returns horizontal center
	*/
	int a = left + right;
	return a / 2;
}

string TwoDimTreeNode::topLeft(int x, int y)
{
	/*
	Checks whether given location is in given TopLeft
	*/
	string isMatch = "no";
	if (x <= Extent.hor()) {
		if (y <= Extent.ver()) {
			if (this->TopLeft == nullptr) {
				TopLeft = new TwoDimTreeNode(this->Extent.top, this->Extent.left, this->Extent.ver(), this->Extent.hor());
			}
			isMatch = "yes";
		}
	}
	return isMatch;
}

string TwoDimTreeNode::topRight(int x, int y)
{
	/*
	Checks whether given location is in given TopRight
	*/
	string isMatch = "no";
	if (x > Extent.hor()) {
		if (y <= Extent.ver()) {
			if (this->TopRight == nullptr) {
				TopRight = new TwoDimTreeNode(this->Extent.top, this->Extent.hor(), this->Extent.ver(), this->Extent.right);
			}
			isMatch = "yes";
		}
	}
	return isMatch;
}

string TwoDimTreeNode::bottomLeft(int x, int y)
{
	/*
	Checks whether given location is in given BottomLeft
	*/
	string isMatch = "no";
	if (x <= Extent.hor()) {
		if (y > Extent.ver()) {
			if (this->BottomLeft == nullptr) {
				BottomLeft = new TwoDimTreeNode(this->Extent.ver(), this->Extent.left, this->Extent.bottom, this->Extent.hor());
			}
			isMatch = "yes";
		}
	}
	return isMatch;
}

string TwoDimTreeNode::bottomRight(int x, int y)
{
	/*
	Checks whether given location is in given BottomRight
	*/
	string isMatch = "no";
	if (x > Extent.hor()) {
		if (y > Extent.ver()) {
			if (this->BottomRight == nullptr) {
				BottomRight = new TwoDimTreeNode(this->Extent.ver(), this->Extent.hor(), this->Extent.bottom, this->Extent.right);
			}
			isMatch = "yes";
		}
	}
	return isMatch;
}

TwoDimTreeNode * TwoDimTreeNode::search(int x, int y, vector<Rectangle> & ver, vector<Rectangle> & hor)
{
	/*
	Finds the tree node which the point x, y  belongs to
	*/
	vector<TwoDimTreeNode *> nodes;
	if ((TopLeft || TopRight || BottomLeft || BottomRight)) {
		nodes.push_back(TopLeft);
		nodes.push_back(TopRight);
		nodes.push_back(BottomLeft);
		nodes.push_back(BottomRight);
		for (int i = 0; i < nodes.size(); i++) {
			if (nodes[i] != nullptr) {
				if (nodes[i]->testPoint(x, y)) {
					for (int j = 0; j < nodes[i]->Vertical.size(); j++) {
						ver.push_back(nodes[i]->Vertical[j]);
					}
					for (int j = 0; j < nodes[i]->Horizontal.size(); j++) {
						hor.push_back(nodes[i]->Horizontal[j]);
					}
					return nodes[i]->search(x, y, ver, hor);
				}
			}
		}
	}
	return this;
	
}

void TwoDimTreeNode::findAndPrint(int x, int y)
{
	/*
	First checks the rectangles from the founded node which x, y belongs to
	Then, prints corresponding outputs from the founded node which x, y belongs to.
	
	*/
	vector<Rectangle> ver;
	vector<Rectangle> hor;
	TwoDimTreeNode * quadrant = search(x, y, ver, hor);
	vector<Rectangle> match;
	for (int i = 0; i < ver.size(); i++) {
		if (ver[i].left <= x && ver[i].right > x) {
			if (ver[i].top <= y && ver[i].bottom > y) {
				match.push_back(ver[i]);
			}
		}
	}
	for (int i = 0; i < hor.size(); i++) {
		if (hor[i].left <= x && hor[i].right > x) {
			if (hor[i].top <= y && hor[i].bottom > y) {
				match.push_back(hor[i]);
			}
		}
	}
	cout << x << " " << y << endl << match.size() << endl;
	for (int i = 0; i < match.size(); i++) {
		Rectangle rectangle = match[i];
		rectangle.printRectangle();
	}
}

TwoDimTreeNode::TwoDimTreeNode(int top, int left, int bottom, int right): Extent(Rectangle(top, left, bottom, right)){
	/*
	Calculates the size of the rectangle (not area)
	*/
	this->size = (right + bottom - left - top);
}

void TwoDimTreeNode::add(Rectangle & rectangle)
{
	/*
	Adding the rectangle to the tree recursively
	*/
	bool isMatch = false;
	if (horizontalMatch(rectangle)) {
		isMatch = true;
		bool addedBefore = false;
		for (int i = 0; i < Horizontal.size(); i++) {
			if (Horizontal[i].bottom == rectangle.bottom) {
				if (Horizontal[i].top == rectangle.top) {
					if (Horizontal[i].right == rectangle.right) {
						if (Horizontal[i].left == rectangle.left) {
							addedBefore = true;
						}
					}
				}
			}
		}
		if (!addedBefore) {
			Horizontal.push_back(rectangle);
		}
	}
	else if (verticalMatch(rectangle) && (!isMatch)) {
		bool addedBefore = false;
		for (int i = 0; i < Vertical.size(); i++) {
			if (Vertical[i].bottom == rectangle.bottom) {
				if (Vertical[i].top == rectangle.top) {
					if (Vertical[i].right == rectangle.right) {
						if (Vertical[i].left == rectangle.left) {
							addedBefore = true;
						}
					}
				}
			}
		}
		if (!addedBefore) {
			Horizontal.push_back(rectangle);
		}
	}

	else {
		if ((size / 4) > 0) {
			if (bottomRight(rectangle.right, rectangle.bottom) == "yes") {
				BottomRight->add(rectangle);
			}
			if (topRight(rectangle.right, rectangle.top) == "yes") {
				TopRight->add(rectangle);
			}
			if (topLeft(rectangle.left, rectangle.top) == "yes") {
				TopLeft->add(rectangle);
			}
			if (bottomLeft(rectangle.left, rectangle.bottom) == "yes") {
				BottomLeft->add(rectangle);
			}
		}
	}
}

bool TwoDimTreeNode::testPoint(int x, int y)
{
	/*
	Check whether the given point in the rectangle or not
	*/
	if (this->Extent.left <= x && this->Extent.right > x) {
		if (this->Extent.top <= y && this->Extent.bottom > y)
			return true;
	}
	return false;
}

bool TwoDimTreeNode::horizontalMatch(Rectangle & rectangle)
{
	/*
	Checks if the center crosses rectangle horizontally
	*/
	int x = this->Extent.hor();
	if (rectangle.left <= x && rectangle.right > x)
		return true;
	return false;
}

bool TwoDimTreeNode::verticalMatch(Rectangle & rectangle)
{
	/*
	Checks if the center crosses rectangle vertically
	*/
	int y = this->Extent.ver();
	if (rectangle.top <= y && rectangle.right > y) {
		return true;
	}
	return false;
}

#include <vector>
#include <string>
#include <iostream>
using namespace std;
template <class Comparable>
class BinaryHeap{
public:
	bool isEmpty() {
		if (currentSize == 0) {
			return true;
		}
		return false;
	}
	Comparable GetMax() {
		if (currentSize == 0) {
			return 0;
		}
		return valueList[1];
	}
	Comparable Remove(Comparable & label) {
		if (locationList[label]) {
			Comparable myValue = valueList[locationList[label]];
			valueList[locationList[label]] = valueList[currentSize];
			labelList[locationList[label]] = labelList[currentSize--];
			percolateDown(locationList[label]);
			locationList[label] = 0;
			return myValue;
		}
	}
	BinaryHeap(int capacity = 500) : valueList(capacity + 1), labelList(capacity + 1), locationList(capacity + 1) { currentSize = 0; };
	void insert(const Comparable & xVal, const Comparable & xVal2);
private:
	int currentSize;
	vector<Comparable> valueList;
	vector<Comparable> labelList;
	vector<Comparable> locationList;
	void percolateDown(int hole);
};
template <class Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & xVal, const Comparable & xVal2){
	int hole = ++currentSize;
	for (; hole > 1 && valueList[hole / 2] < xVal; hole /= 2) {
		valueList[hole] = valueList[hole / 2];
		labelList[hole] = labelList[hole / 2];
		locationList[labelList[hole]] = hole;
	}
	valueList[hole] = xVal;
	labelList[hole] = xVal2;
	locationList[xVal2] = hole;
}
template <class Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole){
	int child;
	Comparable tmp = valueList[hole];
	Comparable tmp2 = labelList[hole];
	for (; hole * 2 <= currentSize; hole = child){
		child = hole * 2;
		if (child != currentSize && valueList[child + 1] > valueList[child])
			child++;
		if (valueList[child] > tmp) {
			valueList[hole] = valueList[child];
			labelList[hole] = labelList[child];
			locationList[labelList[hole]] = hole;
		}
		else
			break;
	}
	valueList[hole] = tmp;
	labelList[hole] = tmp2;
	locationList[labelList[hole]] = hole;
}
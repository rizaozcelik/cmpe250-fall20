#ifndef BINARYMINHEAP_H
#define BINARYMINHEAP_H

#include <vector>
#include "Event.h"
using namespace std;

template<class Comparable>
class BinaryMinHeap
{
public:
    BinaryMinHeap();
    int getSize();
    bool isEmpty( );
    void push(Comparable&& x );
    void deleteMin(Comparable &x);
    vector<Comparable> getArray();
private:
    int currentSize;
    vector<Comparable> array;
    void percolateDown(int hole );
};
#endif

#include "BinaryMinHeap.h"

using namespace std;

template<class Comparable>
BinaryMinHeap<Comparable>::BinaryMinHeap() {
currentSize=0;
Comparable x;
array.push_back(x);
}
template<class Comparable>
bool BinaryMinHeap<Comparable>::isEmpty() {
    return currentSize==0;
}
template<class Comparable>
void BinaryMinHeap<Comparable>::push(Comparable&& x) {
    if(currentSize==array.size()-1)
        array.resize(array.size()*2);
        // Percolate up
    int hole = ++currentSize;
    for ( ; hole > 1 && x<array[ hole / 2 ]; hole /= 2 )
        array[ hole ] = move( array[ hole / 2 ] );
    array[ hole ] = move( x );
}
template<class Comparable>
void BinaryMinHeap<Comparable>::deleteMin(Comparable& min)
{
    min =move( array[ 1 ] );
    array[ 1 ] =move( array[ currentSize-- ] );
    percolateDown( 1 );
}
template<class Comparable>
void BinaryMinHeap<Comparable>:: percolateDown(int hole ) {
    int child;
    Comparable tmp =move(array[hole]);
    for (; hole*2 <= currentSize; hole = child) {
        child = hole*2;
        if(child != currentSize && array[child + 1] < array[child])
            ++child;
        if (array[child] < tmp)
            array[hole] = move(array[child]);
        else
            break;
    }
    array[hole] = move(tmp);
}
template<class Comparable>
int BinaryMinHeap<Comparable>::getSize() {
    return currentSize;
}

template<class Comparable>
vector<Comparable> BinaryMinHeap<Comparable>:: getArray() {
    return array;
}
template class BinaryMinHeap<Event>;
template class BinaryMinHeap<Person>;
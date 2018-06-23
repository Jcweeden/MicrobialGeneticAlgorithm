#ifndef _IHeapItem_
#define _IHeapItem_


class IHeapItem {
public:
int heapIndex;

public:

IHeapItem() {HeapIndex(0);}
void HeapIndex(int val) {heapIndex = val;}
int HeapIndex() { return heapIndex;}

};

#endif

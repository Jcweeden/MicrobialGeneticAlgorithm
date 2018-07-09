#ifndef _Heap_
#define _Heap_

#include "Node.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



class IHeapItem;

class Heap {

public:

std::vector<Node*> items;
//IHeapItem itemss[];
int itemsCount;

public:

  Heap();

  void addItem(Node* item);
  Node* removeFirstItem();
  void swapItems(Node* itemA, Node* itemB);

  void updateItem(Node* item);


  void setHeapSize(int count)
  {
    itemsCount = 0;
    items.resize(count);
    //std::vector<Node>items(count);
//itemss = new IHeapItem[itemsCount];
  }
  int getHeapSize() {return itemsCount; }

  bool isInHeap(Node* item);

  void sortUp(Node* item);
  void sortDown(Node* item);

  void clean();

  void print();

  void printer (std::vector<Node*> const & tree, unsigned index, unsigned mlength);
  void print_tree (std::vector<Node*> & tree);
};



#endif


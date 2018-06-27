#include "Heap.h"

Heap::Heap()
{
  //init items
  itemsCount = 0;
}

void Heap::clean()
{
  
  for(size_t i = 0; i <= itemsCount; i++)
  {
    items[i]->hCost = 0;
    items[i]->gCost = 0;
    items[i]->heapIndex = 0;
  }
  
  items.clear();
  itemsCount = 0;
  //std::cout << "heap->itemsSize after clear: " << items.size() << "\n";
}

void Heap::addItem(Node* item)
{ 
  item->heapIndex = itemsCount;
  items[itemsCount] = item; //items.push_back(item);
  sortUp(item);

  itemsCount++;
}

//remove from item from the heap and set final item in heap to its position
//then sort down to rearrange heap into correct order
Node* Heap::removeFirstItem()
{
  Node* firstItem = items[0];

  itemsCount--;

  //take item at end of heap and put into first place
  items[0] = items[itemsCount];
  items[0]->heapIndex = 0;

  //items.erase(items.begin() +items.size()-1); //items[items.size()-1];
  sortDown(items[0]);
  return firstItem;
}

//swap the locations in the heap of two nodes
void Heap::swapItems(Node* itemA, Node* itemB)
{
  //swap locations in array
  items[itemA->heapIndex] = itemB;
  items[itemB->heapIndex] = itemA;

  //swap heapIndexs for items
  int tempIndex = itemA->heapIndex;

  itemA->heapIndex = itemB->heapIndex;
  itemB->heapIndex = tempIndex;

}

void Heap::updateItem(Node* item)
{
  sortUp(item);
}

//check if node is in heap
bool Heap::isInHeap(Node* item)
{
  //check if item's heap index exists in the array
  if (items[item->heapIndex]/*->heapIndex*/ == item/*->heapIndex*/) //DUBIOUS
    // if (items[item->heapIndex]->heapIndex == item->heapIndex) //DUBIOUS
      return true;
    else
      return false;
}

//
void Heap::sortUp(Node* item)
{
  //get parent index of node item
  int parentIndex = (item->heapIndex-1)/2;

  //while still of a higher priority than the item's parent
  while (true)
  {
    Node* parentItem = items[parentIndex];

    //if item has a higher priority than parent
    //if (item->heapIndex > parentItem->heapIndex) //DUBIOUS
    if (item->compareTo(parentItem) > 0) //DUBIOUS
    {
      //swap the item's position in the heap with its parents
      swapItems(item, parentItem);
    }
    else
    {
      break; //no longer a higher priority than its parent
    }
      
    parentIndex = (item->heapIndex-1)/2;
  }
}

void Heap::sortDown(Node* item)
{
  while(true)
  {
    //get index of parent's two children
    int childIndexLeft = item->heapIndex * 2 + 1;
    int childIndexRight = item->heapIndex * 2 + 2;

    //temp variable
    int swapIndex = 0;

    //if has at least one child
    if (childIndexLeft < itemsCount)
    {
      //get child index left
      swapIndex = childIndexLeft;

      //if item has two children (child on right)
      if (childIndexRight < itemsCount)
      {
        //if child on right has higher priority than child on left
        //if (items[childIndexRight]->heapIndex > items[childIndexLeft]->heapIndex) //DUBIOUS
        if (items[childIndexRight]->compareTo(items[childIndexLeft]) < 0)
        { //right child has higher priority
          swapIndex = childIndexRight;
        }
      }
      //swap index is now equal to child with highest priority
      
      //check if parent has lower priority than highest priority child
      //if (item->heapIndex < items[swapIndex]->heapIndex)  //less DUBIOUS
      if (item->compareTo(items[swapIndex]) < 0)
      {
        //if so, then swap them
        swapItems(item, items[swapIndex]);
      }
      
      //else parent has higher priority, exit loop
      else return;

      
    }
    //parent has no children
    else return;
  }
}


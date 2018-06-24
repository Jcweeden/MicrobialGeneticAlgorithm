#include "Node.h"

Node::Node(Vector2D p_position, unsigned p_gridXIndex, unsigned p_gridYIndex, unsigned p_gridWidth, unsigned p_gridHeight/*, bool p_traversable*/)
    : position(p_position),
      gridXIndex(p_gridXIndex), gridYIndex(p_gridYIndex),
      gridWidth(p_gridWidth), gridHeight(p_gridHeight),
      traversable(true),
      parent(Vector2D(0,0)),
      gCost(0),
      hCost(0),
      heapIndex(0)
{
}

Node::Node()
    : position(Vector2D(0,0)),
      gridXIndex(0), gridYIndex(0),
      gridWidth(0), gridHeight(0),
      traversable(true),
      parent(Vector2D(0,0)),
      gCost(0),
      hCost(0),
      heapIndex(0)
{}

//compare fCosts of two nodes
//if the two nodes fCosts are equal then the node with the node's hCost will be compared
//returns -1 if node is higher, 1 if lower
int Node::compareTo(Node* nodeToCompare)
{
  if (fCost() < nodeToCompare->fCost())
  {
    return 1;
  }
  else if (fCost() > nodeToCompare->fCost())
  {
    return -1;
  } 
  else if (fCost() == nodeToCompare->fCost())
  {
    if (hCost < nodeToCompare->hCost)
    {
      return 1;
    } else if (hCost > nodeToCompare->hCost)
    {
      return -1;
    }
  }

  return 0; //else are equal for both fCost and hCost, return 0
}

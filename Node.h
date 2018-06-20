#ifndef _Node_
#define _Node_

#include "SDL2/SDL.h"
#include "Vector2D.h"

#include <vector>

//class Node;

class Node {

public:
  //the top left position of the node
  Vector2D position;

  //the index of the node in the Grid grid vector
  unsigned gridXIndex, gridYIndex;
  
  //the X width of the node
  unsigned gridWidth;
  //the Y height of the node
  unsigned gridHeight;
  
  //true if the node is not an obstactle, and is walkable
  bool traversable;

  int gCost;

  int hCost;

  //used when retracing back through the search path
  Vector2D parent;

public:

  //constructor
  Node(Vector2D p_position, unsigned p_gridXIndex, unsigned p_gridYIndex, unsigned p_gridWidth, unsigned p_gridHeight, bool p_traversable);

  Node();
  
  
  //return the total score for the node
  int fCost() {return gCost + hCost;}
};

#endif

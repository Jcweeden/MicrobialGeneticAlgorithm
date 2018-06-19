#ifndef _Node_
#define _Node_

#include "SDL2/SDL.h"
#include "Vector2D.h"

#include <vector>

class Node {

public:
  //the top left posiiton of the node
  Vector2D position;

  //the X length of the node
  unsigned gridX;
  //the Y length of the node
  unsigned gridY;
  
  //true if the node is not an obstactle, and is walkable
  bool traversable;

  int gCost;

  int hCost;

public:

  //constructor
  Node(Vector2D p_position, unsigned p_gridX, unsigned p_gridY, bool p_traversable);

  Node();
  
  
  //return the total score for the node
  int fCost() {return gCost + hCost;}
};

#endif

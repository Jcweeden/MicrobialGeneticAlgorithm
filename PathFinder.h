#ifndef _PathFinder_
#define _PathFinder_

#include "SDL2/SDL.h"

#include "Heap.h"
#include "Grid.h"
#include "Vector2D.h"
#include "Node.h"


#include <iostream>
#include <vector>

class PathFinder {

public:

  Grid* grid;

  //holds the current set of Nodes that forms the path of the selected Microbe
  std::vector<Node*> pathway;

  Heap heap;

public:

  PathFinder(/*Grid* p_grid*/);
  
  bool findPath(Vector2D startPosition, Vector2D targetPosition);

  int calcManhattanDistance(Node* nodeA, Node* nodeB);

  void retracePath(Node* start, Node* end);

  void setGrid(Grid* p_grid);

  void clean();
};

#endif

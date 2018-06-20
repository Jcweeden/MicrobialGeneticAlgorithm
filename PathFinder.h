#ifndef _PathFinder_
#define _PathFinder_

#include "SDL2/SDL.h"

#include "Grid.h"
#include "Vector2D.h"
#include "Node.h"


#include <iostream>
#include <vector>

class PathFinder {

public:

  Grid* grid;


public:

  PathFinder(/*Grid* p_grid*/);
  
  void findPath(Vector2D startPosition, Vector2D targetPosition);

  int calcManhattanDistance(Node* nodeA, Node* nodeB);

  void retracePath(Node* start, Node* end);


  void setGrid(Grid* p_grid);
};

#endif

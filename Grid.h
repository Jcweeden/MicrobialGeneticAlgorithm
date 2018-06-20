#ifndef _Grid_
#define _Grid_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 

#include "Game.h"
#include "Vector2D.h"
#include "Node.h"


#include <iostream>
#include <vector>

class Environment;

class Grid {

public:
  //the size of the grid
  Vector2D gridSize;

  //2D vector holding all nodes that form the grid
  std::vector<std::vector<Node*> > grid;
  
  float nodeRadius;
  //the width of a single node in px
  float nodeDiameter;

  //the count of how many nodes form the X and Y 
  unsigned nodeCountX, nodeCountY;

  //the coordinates of the selected microbe to track the movement of
  Vector2D selectedObjectPosition;

  //holds the current set of Nodes that form the path of the selected Microbe
  std::vector<Node*> pathway;

  
public:

  Grid();
  Grid(unsigned p_gridLengthX, unsigned p_gridLengthY, float p_nodeDiameter);
  
  void setupGrid();
  
  void drawGrid();

  void clean();

  Node* getNodeFromCoords(Vector2D worldPosition);

  void setObstacleNodesToUntraversable();

  std::vector<Node*> getNeighbouringNodes(Node* node);

};

#endif

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

  //draw options (drawn on-screen if true)
  bool drawGridEnabled, drawTerrainEnabled, drawPathEnabled;
public:

  //constructors
  Grid();
  Grid(unsigned p_gridLengthX, unsigned p_gridLengthY, float p_nodeDiameter);

  //creates and put the new nodes in the nodes array. calls setObstacleNodesToUntraversable()
  void setupGrid();

  //for each, if enabled, draws and displays the grid, traversable terrain, and current path of selected microbe
  void drawGrid();

  //deletes nodes in grid
  void clean();

  //handles button presses to enable drawing of grid, terrain, path
  void handleInput();

  //resets gCost, fCost, heapIndex, and parent for each node
  void resetGrid();

  //sets all nodes to traverable
  void resetTraverable();
  
  //return the node at the coordinates passed in
  Node* getNodeFromCoords(Vector2D worldPosition);

  //check each obstacle against the grid, setting those nodes in contact with an obstacle to untraversable
  void setObstacleNodesToUntraversable();

  //all traversable neighbours of the passed in node are returned, including those at diagonals
  std::vector<Node*> getNeighbouringNodes(Node* node);

  //DEBUG - prints out representation of the grid, showing fCost for each node
  void printNodeValues(Node* startPos, Node* targetPos);

};

#endif

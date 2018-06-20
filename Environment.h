#ifndef _Environment_
#define _Environment_

#include "SDL2/SDL.h"
#include "Vector2D.h"

//#include "GameObject.h"
#include "Microbe.h"
#include "FoodSource.h"
#include "Obstacle.h"
#include "Grid.h"
#include "PathFinder.h"

#include <iostream>
#include <string>
#include <vector>

class Microbe;
class FoodSource;
class Obstacle;
//class Grid;

class Environment {

public:
  
  //static instance variable
  static Environment* s_pInstance;

  //vector containing all active food sources
  std::vector<FoodSource*> foodSources;
  
  //vector containing all active agents
  std::vector<Microbe*> microbes;

  //vector containing all obstacles in the environment
  std::vector<Obstacle*> obstacles;
  
  //grid that holds the terrain for A* traversal of microbes
  Grid grid;

  //
  PathFinder pathFinder;
  
public:
  //create singleton instance
  static Environment* Instance();

  Environment();

  void setup(unsigned microbeCount, unsigned foodSourceCount, unsigned obstaclesCount,
             unsigned gridSizeX, unsigned gridSizeY, unsigned nodeDiameter);
  
  void draw();

  void update();

  void clean();

};

typedef Environment TheEnvironment;


#endif

#ifndef _Environment_
#define _Environment_

#include "SDL2/SDL.h"
#include "Vector2D.h"

#include "GameObject.h"
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
  
  //the index of the selected microbe whose path is drawn
  int selectedMicrobeIndex;

  //microbe counter - starts from one and is incremented to uniquely number each microbe (UI purposes only)
  unsigned microbeCounter;

  //set to the number of reproductions before the first microbe reached max fitness (UI purposes only)
  unsigned maxFitnessAchievedReproductions;

  //holds the time at which the first microbe achieved max fitness (UI purposes only)
  unsigned timeMaxFitnessAchieved;
  
public:
  //create singleton instance
  static Environment* Instance();

  Environment();

  void setup(unsigned microbeCount, unsigned foodSourceCount, unsigned obstaclesCount,
             unsigned gridSizeX, unsigned gridSizeY, unsigned nodeDiameter);
  
  void draw();

  void update();

  void clean();

  //check the position of mouse clicks, and if a microbe is clicked then set it as selected
  void handleInput();
};

typedef Environment TheEnvironment;


#endif

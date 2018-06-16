#ifndef _Environment_
#define _Environment_

#include "SDL2/SDL.h"
#include "Vector2D.h"

//#include "GameObject.h"
#include "Microbe.h"
#include "FoodSource.h"

#include <iostream>
#include <string>
#include <vector>

class Microbe;
class FoodSource;

class Environment {

public:
  
  //static instance variable
  static Environment* s_pInstance;

  //vector containing all active food sources
  std::vector<FoodSource*> foodSources;
  
  //vector containing all active agents
  std::vector<Microbe*> microbes;


public:
  //create singleton instance
  static Environment* Instance();

  Environment();
  Environment(int microbeCount, int foodSourceCount); //const

  void setup(int microbeCount, int foodSourceCount);
  
  void draw();

  void update();

  void clean();

};

typedef Environment TheEnvironment;


#endif

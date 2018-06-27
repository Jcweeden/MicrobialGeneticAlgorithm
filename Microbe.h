#ifndef _Microbe_
#define _Microbe_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 

#include "GameObject.h"
#include "Environment.h"
#include "PathFinder.h"

#include <iostream>
#include <string>

class GameObject;

class Microbe : public GameObject {
public:

  //starts at 10 and is decremented as the microbe increases in size and gets slower
  float speedMultiplier;

  //number of food consumed at this point in time - reset to 0 upon reproducing
  unsigned foodEaten;
  //number of food that must be eaten before reproducing
  const unsigned foodRequiredToMate = 500;

  //if the weaker partner during reproduction then 
  bool dying;

  float startingRadius;
  
  float childRadius;
  //amount to increase by per food = (startingRadius/foodRequiredToMate)

  //the remaining size the microbe has to shrink by
  float radiusToShrinkBy;

  int framesToNextPathfind;
  PathFinder pathFinder;

public:

  Microbe(); //const
    
  void draw();
  void update();
  void clean();

  void moveTowards(const Vector2D target);
  
  int locateNearestFoodSource();
  int locateNearestReproductivePartner();
  Vector2D generateRandomNearLocation();
  
  void consumedFoodSource();

  void produceChild();
  void completedReproduction();
  void deathFromReproduction();
  
  void setSpeedMultiplier(float p_speed) { speedMultiplier = p_speed;}

  //if not dying, and has consumed enough food to reproduce then return true
  bool isReadyToReproduce();
};

#endif

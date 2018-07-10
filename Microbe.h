#ifndef _Microbe_
#define _Microbe_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 

//#include "GameObject.h"
#include "Environment.h"
#include "PathFinder.h"
#include "MicrobialGA.h"

#include <iostream>
#include <string>

class GameObject;

class Microbe : public GameObject {
public:

  //the unique number of the microbe within the simulation (for UI purposes only)
  unsigned microbeID;
  
  //used within UI. the number represents the action currently being undertaken (e.g. searching for food)
  //0 - seeking food
  //1 - waiting for accessible food source
  //2 - seeking partner
  //3 - waiting for viable partner
  //4 - dying
  unsigned currentStatus;
  
  //the radius of the microbe upon spawning
  float startingRadius;
  
  //starts at 10 and is decremented as the microbe increases in size and gets slower
  float speedMultiplier;

  //number of food consumed at this point in time - reset to 0 upon reproducing
  unsigned foodEaten;
  
  //number of food that must be eaten before reproducing
  const unsigned foodRequiredToMate = 500;

  //the index of the foodSource that the microbe is currently heading towards
  int nearestFoodSource;
  
  //the number of children the microbe has produced
  unsigned childrenProduced;

  //the clock time when the microbe was spawned
  unsigned microbeSpawnTime;
  
  //if the weaker partner during reproduction then the microbe will be set to dying, and slowly shrink
  bool dying;

  //the radius of the unborn child the microbe is currently carrying. Used to draw the child circle
  float childRadius;
  //amount to increase by per food = (startingRadius/foodRequiredToMate)

  //the remaining size the microbe has to shrink by
  float radiusToShrinkBy;
  
  PathFinder pathFinder;
  
  //the pathfinding algorithm only runs every x amount of frames. This is the number of frames to elapse before determining a new path
  int framesToNextPathfind;

  MicrobialGA mga;

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

  void produceChild(const Microbe* losingParent);
  void completedReproduction();
  void deathFromReproduction();
  
  void setSpeedMultiplier(float p_speed) { speedMultiplier = p_speed;}

  //if not dying, and has consumed enough food to reproduce then return true
  bool isReadyToReproduce();
};

#endif

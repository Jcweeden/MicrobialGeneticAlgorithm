#ifndef _Microbe_
#define _Microbe_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 

//#include "GameObject.h"
#include "Environment.h"
#include "PathFinder.h"
#include "MicrobialGA.h"
#include "SoundMixer.h"

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

  //the index of the closest accessible reproductive partner that the microbe is currently heading towards
  int nearestPartnerIndex;
  
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

  //holds the grid that the microbe uses to navigate the environment, and produces a path given the mircobe's
  //location and a target location (e.g. foodSource or mate)
  PathFinder pathFinder;
  
  //the pathfinding algorithm only runs every x amount of frames. This is the number of frames to elapse before determining a new path
  int framesToNextPathfind;

  //holds the set of genes for the microbe
  MicrobialGA mga;

public:

  Microbe(); //constructor

  //draws the microbe and it's child (should it have eaten enough food)
  void draw();

  //determines the action of the microbe, depending on how much food it has eaten, and whether it is dying
  //calls appropriate functions to get a path to the nearest foodSource/partner as required, and applies forces
  //so that the microbe will move on this path
  void update();

  //cleans the class 
  void clean();

  //given a target location the microbe has the appropriates forces applied to propell it in that direction
  //generally passed the first node in the path found by pathfinder's A* route
  void moveTowards(const Vector2D target);

  /**
   //calculates a path to the closest accessible foodSource and returns the index of it
   1. calculates the distance between the microbe and each food source
   2. checks the closest foodSouce to see if there is a traversable path, if so stores the index of the closest food source and returns it,
   3. else iterates through foodsources until a viable path is found to the closest foodSource to the microbe. 
  **/
  int locateNearestFoodSource();

  
  int locateNearestReproductivePartner();

  //randomly generate a location near to the microbe's current position that is plus/minus 1/6 of the window size away for both width and height
  Vector2D generateRandomNearLocation();

  //increments foodEaten, reduces the microbe's speed, adds width to microbe and the child being drawn within it
  void consumedFoodSource();

  //called from the surviving parent. a child is produced with the losingParent's genes, and with one correct gene from the surviving parent copied over. There is then a 50% chance of mutating a random gene to a random new value in the child
  void produceChild(const Microbe* losingParent);

  //sets the child being drawn in the mircobe to shrink down, and resets foodEaten to 0
  void completedReproduction();

  //sets the microbe to begin shrinking, and stops it from further chasing food or mates
  void deathFromReproduction();
  
  void setSpeedMultiplier(float p_speed) { speedMultiplier = p_speed;}

  //if not dying, and has consumed enough food to reproduce then return true
  bool isReadyToReproduce();

  //passes the genes of the microbe to TheSoundMixer and plays them
  void playGenotypeSong();
};

#endif

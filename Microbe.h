#ifndef _Microbe_
#define _Microbe_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 
//#include "Vector2D.h"

#include "GameObject.h"
#include "Environment.h"
#include <iostream>
#include <string>

class GameObject;

class Microbe : public GameObject {
public:

  //number of food that must be eaten before reproducing
  static const unsigned foodRequiredToMate = 100;

  float speedMultiplier;
  
  unsigned foodEaten;

  bool dying;
  
public:

  Microbe(); //const
    
  void draw();
  void update();
  void clean();

  void moveTowards(const Vector2D target);
  int locateNearestFoodSource();
  void findNearestReproductivePartner();
  void consumedFoodSource();

  void setSpeedMultiplier(float p_speed) { speedMultiplier = p_speed;}
};

#endif

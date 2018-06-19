#ifndef _Obstacle_
#define _Obstacle_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 

#include "GameObject.h"
#include "Environment.h"
#include <iostream>
#include <string>

class GameObject;

class Obstacle : public GameObject {
public:


public:
  Obstacle(); //const
    
  void draw();
  void update();
  void clean();

};

#endif

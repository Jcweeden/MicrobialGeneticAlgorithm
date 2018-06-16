#ifndef _FoodSource_
#define _FoodSource_

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h" 
//#include "Vector2D.h"
#include "GameObject.h"

#include <iostream>
#include <string>

class GameObject;

class FoodSource : public GameObject {
public:


public:

  FoodSource(); //const

    
  void draw();
  void update();
  void clean();
};

#endif

#ifndef _Circle_
#define _Circle_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>
#include <string>

class Circle : public GameObject {
  
public:
  Circle(int p_x, int p_y, float p_radius, int p_mass, Uint8 p_colourR, Uint8 p_colourG, Uint8 p_colourB, Uint8 p_colourA);
  
  virtual void draw();
  virtual void update();
  virtual void clean();
  

  //calculate and return polygon area
  float getArea();

  //get/set for radius
  float getRadius() {return radius; };
  void setRadius(float val) {radius = val; }

  
protected:
  
  float radius;
  
  const float pi = 3.14159265359;
  
};

#endif

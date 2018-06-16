#include "Circle.h"
#include "SDL2/SDL2_gfxPrimitives.h" 


Circle::Circle(int p_x, int p_y, float p_radius, /* int p_rotation,*/ int p_mass, Uint8 p_colourR, Uint8 p_colourG, Uint8 p_colourB, Uint8 p_colourA) :
    GameObject( p_x,  p_y, p_radius, p_radius, p_colourR,p_colourG,p_colourB,p_colourA )
{
  radius = p_radius;
}

float Circle::getArea() {
  return pi * radius * radius;
}

void Circle::draw()
{  
  filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), radius, colourR, colourG, colourB, colourA);
}

void Circle::update()
{  
  GameObject::update();
}

void Circle::clean() {}

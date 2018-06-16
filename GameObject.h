#ifndef _GameObject_
#define _GameObject_

#include "SDL2/SDL.h"
#include "I_GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include <iostream>
#include <string>

//class I_GameObject;

class GameObject : public I_GameObject {

public:

  GameObject(int x, int y, int p_width, int p_height, Uint8 p_colourR, Uint8 p_colourG, Uint8 p_colourB, Uint8 p_colourA);

  
  virtual void draw();
  virtual void update();
  virtual void clean();


  Vector2D& getPosition() {return position; }  
  int getPositionX() {return position.getX(); }
  int getPositionY() {return position.getY(); }
  
  int getWidth() { return width; }
  int getHeight() { return height; }
  void setWidth(int val) { width = val; }
  void setHeight(int val) {height = val; }

  void physicsIntegration(); //applies all forces for the frame
  
  void setVelocity(float p_x, float p_y) {velocity = Vector2D(p_x, p_y);}

  void setAcceleration(float p_x, float p_y) {acceleration = Vector2D(p_x, p_y);}

  void setDamping(float val) { damping = val; }

  void setMass(const float mass); //sets inverse mass
  float getMass() { return ((float)1.0f)/inverseMass; }

  void addForce(const Vector2D &force);

  //removes all forces accumulated in a frame
  void clearAccumForces();

public:
  int width;
  int height;

  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;
  float damping;
  float inverseMass;

  Vector2D forceAccumulated; //sum of all forces to be applied in a frame. cleared after each update


  Uint32 colourR, colourG, colourB, colourA;  
};

#endif

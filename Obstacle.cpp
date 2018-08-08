#include "Obstacle.h"

Obstacle::Obstacle() :
    GameObject(
        rand() % (TheGame::Instance()->getWindowWidth()-30) + 15, //x
        rand() % (TheGame::Instance()->getWindowHeight()-30) + 15,//y
        rand() % 100 + 10,//width
        rand() % 100 + 10,    //height
        20,//r
        20,//g
        20,//b
        255 //a
               )
   
{
  if (getPosition().getX() + width > TheGame::Instance()->getWindowWidth())
    width = TheGame::Instance()->getWindowWidth() - getPosition().getX() - 1;

  if (getPosition().getY() + height  > TheGame::Instance()->getWindowHeight())
    height = TheGame::Instance()->getWindowHeight() - getPosition().getY() - 1;
}


void Obstacle::draw()
{
  //draw box itself
  boxRGBA(TheGame::Instance()->getRenderer(),
            getPositionX(), getPositionY(),
            getPositionX() + width, getPositionY() + height,
            255, 0, 0, 200);
  
  //outline of box
  rectangleRGBA(TheGame::Instance()->getRenderer(),
                getPositionX(), getPositionY(),
                getPositionX() + width, getPositionY() + height,
                0, 0, 0, 255);
}

void Obstacle::update()
{}

void Obstacle::clean()
{

}

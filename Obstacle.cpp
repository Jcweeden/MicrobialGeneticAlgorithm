#include "Obstacle.h"

Obstacle::Obstacle() :
    GameObject(
        rand() % (TheGame::Instance()->getWindowWidth()-30) + 15, //x
        rand() % (TheGame::Instance()->getWindowHeight()-30) + 15,//y
        rand() % 40 + 10,//width
        rand() % 40 + 10,    //height
        20,//r
        20,//g
        20,//b
        255 //a
               )
   
{
}


void Obstacle::draw()
{
  //draw box itself
  boxRGBA(TheGame::Instance()->getRenderer(),
            getPositionX(), getPositionY(),
            getPositionX() + width, getPositionY() + height,
            colourR, colourG, colourB, colourA);
  
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

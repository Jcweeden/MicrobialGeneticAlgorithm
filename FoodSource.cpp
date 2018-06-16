#include "FoodSource.h"
#include "Game.h"


FoodSource::FoodSource() :
    GameObject(
        rand() % TheGame::Instance()->getWindowWidth() +15,//x
        rand() % TheGame::Instance()->getWindowHeight()+15,//y
        10,//width
        10,//height
        rand() % 255,//r
        rand() % 255,//g
        rand() % 255,//b
        255 //a
               )
{
  
}

void FoodSource::draw()
{
  filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), width, 0, 0, 0, colourA);
  filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), width-2, colourR, colourG, colourB, colourA);

}

void FoodSource::update()
{
  
}

void FoodSource::clean()
{
  
}

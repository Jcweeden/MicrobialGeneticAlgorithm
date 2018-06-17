#include "Microbe.h"
//#include "Game.h"
#include <limits.h>


Microbe::Microbe() :
    GameObject(
        rand() % (TheGame::Instance()->getWindowWidth()-30) + 15,//x
        rand() % (TheGame::Instance()->getWindowHeight()-30) + 15,//y
        15,//width
        15,//height
        rand() % 225 + 30,//r
        rand() % 225 + 30,//g
        rand() % 225 + 30,//b
        rand() % 160 + 40//rand() % 255 //a
               ),
    foodEaten(0), dying(false), speedMultiplier(1.0f)
{
  //set acceleration
}

void Microbe::draw()
{/*
  std::cout << "drawing\n"
      << "\ngetPositionX(): " << getPositionX()
      << "\ngetPositionY(): " << getPositionY()
      << "\nwidth" << width
      << "\nheight" << height
      << "\ncolourR" << colourR
      << "\ncolourG" << colourG
      << "\ncolourB" << colourB
      << "\ncolourA" << colourA;
 */
                        //filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), width, 0, 0, 0, 255);
                        filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), width-2, colourR, colourG, colourB, colourA);
}

void Microbe::update()
{
  //std::cout << "updating \n";
  //if has eaten enough food to reproduce
  if (foodEaten >= foodRequiredToMate)
  {
    //check if there is another partner to reproduce with

    //if on top of partner

    //reproduce - genetic algorithm

    //else - move towards partner
    //seek(partner.getLocation());  //location of nearest partner

  }
  //else not eaten enough food, or no current partner available, instead look for nearest food source
  else if (!dying/*not dying*/)  
  {
    //locate nearest food source
    int nearestFoodSource = locateNearestFoodSource();
    //std::cout << nearestFoodSource << "\n";
    if (nearestFoodSource != -1) //if there is an available foodSource
    {
      //continue to move towards the nearest foodSource
      moveTowards(TheEnvironment::Instance()->foodSources[nearestFoodSource]->position);
      
      //and if in contact and eating this food source,
      if (GameObject::checkForCollisionWithCircle(
              TheEnvironment::Instance()->foodSources[nearestFoodSource]))
      {
        //run appropriate code to reduce size of food source
        TheEnvironment::Instance()->foodSources[nearestFoodSource]->consumedByMicrobe();
        //and increase size and consumuption counter for microbe
        consumedFoodSource();
      }
      
     
    }
    else //no food sources
    {
      acceleration.clear();
      //go to random location
    }
  }
  else //dying
  {
    //go to random location
    //die
  }

  GameObject::update();
}

void Microbe::moveTowards(Vector2D target)
{
  
  //distance between microbe and target
  Vector2D dirToMove = (target - position);

  //magnitude
  float hyp = dirToMove.magnitude();

  dirToMove.setX(dirToMove.getX() / hyp);
  dirToMove.setY(dirToMove.getY() / hyp);


  //std::cout << "x: " << dirToMove.getX() <<
  //  "y: " << dirToMove.getY() << "\n";
  
  acceleration = dirToMove * (speedMultiplier / 100);
  //acceleration = dirToMove * 0.0003f;
  

  /*
  //distance between microbe and target
  Vector2D distance = target - position;
  float distanceF = distance.magnitude();

  // Vector2 direction = Vector2.Normalize(end - start);
  distance.normalise();

  
  std::cout << "x: " << distance.getX() <<
      "y: " << distance.getY() << "\n";
  acceleration = distance * 0.001f;
  */
}


void Microbe::clean()
{
  
}

//calculates the distance between the microbe and each food source
//stores the index of the closest food source and returns it
int Microbe::locateNearestFoodSource()
{
  //std::cout <<  "foodSourcesA: " << TheEnvironment::Instance()->foodSources.size() << "\n";
  //index of closest found foodsource
  int nearestFoodSourceIndex = -1;
  //distance to nearest found food source
  float nearestFoodSourceDistance = UINT_MAX;

  //if there are currently foodsources
  if (TheEnvironment::Instance()->foodSources.size() > 0) {
    //for each food source
    for (size_t i = 0; i < TheEnvironment::Instance()->foodSources.size(); i++)
    {
      //std::cout << "looping " << i << "\n";
      //calculate the distance between the food source and microbe
      float distance = position.calcDistance(TheEnvironment::Instance()->foodSources[i]->position);

      //if the distance is less
      if (distance < nearestFoodSourceDistance)
      {
        //save the index and distance
        nearestFoodSourceDistance = distance;
        nearestFoodSourceIndex = i; 
      }   
    }
    //return index of closest found foodsource
    return nearestFoodSourceIndex;
  }
  else //none found, return -1
  {
    return -1;
  }
}


void Microbe::findNearestReproductivePartner()
{
  //check each microbe to see if they are ready to reproduce 
}


void Microbe::consumedFoodSource()
{
  //increase size of microbe
  GameObject::width += 0.005f;

  //decrease speed of microbe
  if (speedMultiplier > 0.2f)
  {
    speedMultiplier -= (speedMultiplier/50);
  }

  //increase mass of microbe
  
  //add value to total food consumption towards next reproduction

  //increase child draw size
  
}

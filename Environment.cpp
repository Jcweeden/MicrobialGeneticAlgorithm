#include "Environment.h"

Environment* Environment::s_pInstance = 0;

Environment* Environment::Instance()
{
  if(s_pInstance == 0)
  {
    s_pInstance = new Environment();
    return s_pInstance;
  }

  return s_pInstance;
}

Environment::Environment()
{}

Environment::Environment(int microbeCount, int foodSourceCount)
{/*
  //Microbe::foodRequiredToMate = 100;
  
  //init microbes
  for (size_t i = 0; i < microbeCount; i++)
  {
    Microbe *microbe = new Microbe();

    microbe->setVelocity( 0,0);

    microbe->setDamping(0.9f);
    microbe->setAcceleration(0.0f, 0.0f); //no gravity
    microbe->clearAccumForces();

    microbes.push_back(microbe);
  }

  //init food sources
  for (size_t i = 0; i < foodSourceCount; i++)
  {
    FoodSource *foodSource = new FoodSource();

    foodSource->setVelocity( 0,0);

    foodSource->setDamping(0.0f);
    foodSource->setAcceleration(0.0f, 0.0f); //no gravity
    foodSource->clearAccumForces();

    foodSources.push_back(foodSource);
  }
 */
}

void Environment::setup(int microbeCount, int foodSourceCount)
{
  //Microbe::foodRequiredToMate = 100;

  float defaultDampingVal = 0.6f;
  
  //init microbes
  for (size_t i = 0; i < microbeCount; i++)
  {
    Microbe *microbe = new Microbe();

    //rand val between -defaultDampingVal/5 and defaultDampingVal/5 - added to defaultDampingVal to give variation in movement
    float dampingVariation =  -(defaultDampingVal/10) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((defaultDampingVal/10)-(-(defaultDampingVal/10)))));


        
    microbe->setVelocity(0,0);
    microbe->setMass(1.0f);
    microbe->setDamping(0.9f + dampingVariation);
    microbe->setAcceleration(0.0f, 0.0f); //no gravity
    //microbe->clearAccumForces();

    microbes.push_back(microbe);
  }

  //init food sources
  for (size_t i = 0; i < foodSourceCount; i++)
  {
    FoodSource *foodSource = new FoodSource();

    foodSource->setVelocity( 0,0);

    foodSource->setDamping(0.0f);
    foodSource->setAcceleration(0.0f, 0.0f); //no gravity
    foodSource->clearAccumForces();

    foodSources.push_back(foodSource);
  }
}


void Environment::draw()
{
  for (size_t i = 0; i < foodSources.size(); i++)
  {
    foodSources[i]->draw();
  }
  
  for (size_t i = 0; i < microbes.size(); i++)
  {
    microbes[i]->draw();
  }


}

void Environment::update()
{
  //std::cout << "foodSources: " << foodSources.size() << "\n";

  for (size_t i = 0; i < foodSources.size(); i++)
  {
    foodSources[i]->update();
  }
  
  for (size_t i = 0; i < microbes.size(); i++)
  {
    microbes[i]->update();
  }

}

void Environment::clean()
{
  
}



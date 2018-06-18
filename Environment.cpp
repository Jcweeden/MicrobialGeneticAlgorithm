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
    microbe->setDamping(0.6f + dampingVariation);
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
  std::cout << "microbes: " << microbes.size() << "\n";

  for (size_t i = 0; i < foodSources.size(); i++)
  {
    foodSources[i]->update();
  }

  std::vector<unsigned> toDelete;
  
  for (unsigned i = 0; i < microbes.size(); i++)
  {
    microbes[i]->update();

    if (microbes[i]->width < 0)
    {
      toDelete.push_back(i);
    }
  }
  if (toDelete.size() > 0 )
  {
    for (size_t i = 0; i < toDelete.size(); i++)
    {
      delete microbes[toDelete[i]];
      microbes.erase(microbes.begin() + toDelete[i]);
    }
  }
}

void Environment::clean()
{
  for (Microbe *microbe: microbes)
  {
    //delete from microbes
    delete microbe;
  }

  for (FoodSource *food: foodSources)
  {
    //delete from microbes
    delete food;
  } 
}



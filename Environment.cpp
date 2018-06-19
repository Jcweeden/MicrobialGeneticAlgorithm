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

void Environment::setup(unsigned microbeCount, unsigned foodSourceCount, unsigned obstaclesCount,
                        unsigned gridSizeX, unsigned gridSizeY, unsigned nodeDiameter)
{
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

  //init obstacles
  for (size_t i = 0; i < obstaclesCount; i++)
  {
    Obstacle *obstacle = new Obstacle();

    obstacle->setVelocity( 0,0);

    obstacle->setDamping(0.0f);
    obstacle->setAcceleration(0.0f, 0.0f); //no gravity

    obstacles.push_back(obstacle);
  }

  //init A* grid, runs setup in Grid constructor
  grid = Grid(gridSizeX, gridSizeY, nodeDiameter);
}


void Environment::draw()
{
  //if selected, pass in the location of the selcected microbe
  grid.selectedObjectPosition = microbes[0]->position;
  
  //if enabled, draw the A* traversal grid
  grid.drawGrid();

  //draw each foodSource
  for (size_t i = 0; i < foodSources.size(); i++)
  {
    foodSources[i]->draw();
  }
  

  //draw each Microbe on top of all this
  for (size_t i = 0; i < microbes.size(); i++)
  {
    microbes[i]->draw();
  }

    //draw each Microbe on top of all this
  for (size_t i = 0; i < obstacles.size(); i++)
  {
    obstacles[i]->draw();
  }
}

void Environment::update()
{
  //std::cout << "microbes: " << microbes.size() << "\n";

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

  for (Obstacle *obs: obstacles)
  {
    //delete from microbes
    delete obs;
  }  

  //delete all nodes in grid
  grid.clean();
}



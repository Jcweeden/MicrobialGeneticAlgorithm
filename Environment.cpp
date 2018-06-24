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

  //init obstacles first so they nodes can be set to intraversble in the grid
  for (size_t i = 0; i < obstaclesCount; i++)
  {
    Obstacle *obstacle = new Obstacle();

    obstacle->setVelocity( 0,0);

    obstacle->setDamping(0.0f);
    obstacle->setAcceleration(0.0f, 0.0f); //no gravity

    obstacles.push_back(obstacle);
  }
  
  std::cout << "Env.setup() before grid = Grid\n";

  //init A* grid, runs setup and creates nodes in Grid constructor
  grid = Grid(gridSizeX, gridSizeY, nodeDiameter);

  //pathFinder.setGrid(&grid);
  std::cout << "Env.setup() init grid = Grid\n";

  
  //now init microbes, ensuring they do not spawn on intraversable terrain
  for (size_t i = 0; i < microbeCount; i++)
  { 
    Microbe *microbe = new Microbe();

    //if and while the coords randomly selected put the microbe into untraversable terrain
    //randomise position again, and loop until the object is placed in traversable terrain
    while (!(grid.getNodeFromCoords(microbe->position)->traversable))
    {
      microbe->setNewRandomisedPosition();  //generate a new location
    } 
    
    //rand val between -defaultDampingVal/5 and defaultDampingVal/5 -
    //added to defaultDampingVal to give variation in movement
    float dampingVariation =  -(defaultDampingVal/10) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((defaultDampingVal/10)-(-(defaultDampingVal/10)))));
        
    microbe->setVelocity(0,0);
    microbe->setMass(1.0f);
    microbe->setDamping(0.6f + dampingVariation);
    microbe->setAcceleration(0.0f, 0.0f); //no gravity

    //set the pathfinder to use the initialised grid
    microbe->pathFinder.setGrid(&grid);

    microbes.push_back(microbe);
  }

  //init food sourcess, ensuring they do not spawn on intraversable terrain
  for (size_t i = 0; i < foodSourceCount; i++)
  {
    FoodSource *foodSource = new FoodSource();


    //if and while the coords randomly selected put the foodSource into untraversable terrain
    //randomise position again, and loop until the object is placed in traversable terrain
    while (!(grid.getNodeFromCoords(foodSource->position)->traversable))
    {
      foodSource->setNewRandomisedPosition();  //generate a new location
    } 
    
    foodSource->setVelocity( 0,0);

    foodSource->setDamping(0.0f);
    foodSource->setAcceleration(0.0f, 0.0f); //no gravity
    foodSource->clearAccumForces();

    foodSources.push_back(foodSource);
  }
}


void Environment::draw()
{
  //std::cout << "Env.draw()\n";
  //if selected, pass in the location of the selcected microbe
  //grid.selectedObjectPosition = microbes[0]->position;
  
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
  
  //draw each obstacle on top of all this
  for (size_t i = 0; i < obstacles.size(); i++)
  {
    obstacles[i]->draw();
  }
  
}

void Environment::update()
{
  //std::cout << "microbes: " << microbes.size() << "\n";

  //foodSources[0]->position = Vector2D(300,500);
  //microbes[0]->position = Vector2D(100,100);
  
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

  //std::cout << "about to apply path\n";
  //grid.pathway = microbes[0]->pathFinder.pathway;
  //std::cout << "applied path\n";
}

void Environment::clean()
{
  for (Microbe *microbe: microbes)
  {
    microbe->clean();
    //delete from microbes
    delete microbe;
  }

  for (FoodSource *food: foodSources)
  {
    //delete from foodSources
    delete food;
  }

  for (Obstacle *obs: obstacles)
  {
    //delete from obstacles
    delete obs;
  }  

  //delete all nodes in grid
  grid.clean();
}



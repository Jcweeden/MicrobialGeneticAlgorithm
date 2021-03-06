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
    : microbeCounter(1)
{}

void Environment::setup(unsigned microbeCount, unsigned foodSourceCount, unsigned obstaclesCount,
                        unsigned gridSizeX, unsigned gridSizeY, unsigned nodeDiameter)
{
  maxFitnessAchievedReproductions = 0;
  timeMaxFitnessAchieved = 0;
  selectedMicrobeIndex = 0;
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

  std::cout << "Env.setup() init grid = Grid\n";

  
  //now init microbes, ensuring they do not spawn on intraversable terrain
  for (size_t i = 0; i < microbeCount; i++)
  { 
    Microbe *microbe = new Microbe();
    microbe->microbeID = microbeCounter++;
    
    //if and while the coords randomly selected put the microbe into untraversable terrain
    //randomise position again, and loop until the object is placed in traversable terrain
    while (!(grid.getNodeFromCoords(microbe->position)->traversable))
    {
      microbe->setNewRandomisedPosition();  //generate a new location
    } 
    
    //rand val between -defaultDampingVal/5 and defaultDampingVal/5 -
    //added to defaultDampingVal to give variation in movement
    float dampingVariation =  -(defaultDampingVal/10) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((defaultDampingVal/10)-(-(defaultDampingVal/10)))));
        
    microbe->setVelocity(rand() % 4, rand() % 4);
    microbe->setMass(1.0f);
    microbe->setDamping(0.6f + dampingVariation);
    microbe->setAcceleration(0.0f, 0.0f); //no gravity

    //set the pathfinder to use the initialised grid
    microbe->pathFinder.setGrid(&grid);

    //init the microbial genetic algorithm to be assigned new random genes
    microbe->mga.assignNewRandomGenotypes();
    
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
    
    foodSource->setVelocity(0,0);

    foodSource->setDamping(0.0f);
    foodSource->setAcceleration(0.0f, 0.0f); //no gravity
    foodSource->clearAccumForces();

    foodSources.push_back(foodSource);
  }
}


void Environment::draw()
{  
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
  handleInput();
  grid.handleInput();
  
  for (size_t i = 0; i < foodSources.size(); i++)
  {
    //std::cout << "updating foodSource " << i << "/" << foodSources.size()-1 <<"\n";
    foodSources[i]->update();
  }

  std::vector<unsigned> toDelete;
  
  for (unsigned i = 0; i < microbes.size(); i++)
  {
    
    //std::cout << "updating microbe " << i << "/" << microbes.size()-1 <<"\n";
    microbes[i]->update();

    if (microbes[i]->width < 0)
    {
      //std::cout << "microbe " << i << "/" << microbes.size() <<" to be deleted\n";
      toDelete.push_back(i);

      //if a microbe is selected
      if ( selectedMicrobeIndex >= 0) {

        //if an microbe before in the array is being deleted, reduce the index to keep following same microbe
        if (i < selectedMicrobeIndex) selectedMicrobeIndex--;

        //and is the microbe being deleted, then set the selected index to -1 (off)
        if (selectedMicrobeIndex == i)
        {
          selectedMicrobeIndex = -1;

          //and stop any further genes from this dead genotype being played
          TheSoundMixer::Instance()->stopPlayingGenotypes();
        }
      }
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
  
  //if a microbe is selected, update the grid to so that the selected microbe's pathway can be drawn
  if (selectedMicrobeIndex != -1)
    grid.pathway = microbes[selectedMicrobeIndex]->pathFinder.pathway;
  else //else clear the grid so that none is drawn
    grid.pathway.clear();    
  
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



void Environment::handleInput()
{
  //MOUSE
  if (TheInputHandler::Instance()->getMouseButtonState(0))
  {
    //get position of click
    Vector2D mousePos (TheInputHandler::Instance()->getMousePosition()->getX(),
                       TheInputHandler::Instance()->getMousePosition()->getY());

    //check with each microbe if the click position was on that microbe
    for (size_t i = 0; i < microbes.size(); i++)
    {
      //if it was, then set that microbe as selected, play the genotype, and return
      if (microbes[i]->checkForCollisionWithPoint(&mousePos))
      {
        selectedMicrobeIndex = i;
        microbes[selectedMicrobeIndex]->playGenotypeSong();
        return;
      }
    }
    //else, no microbe was selected - so select none
    selectedMicrobeIndex = -1;

    //and should a genotype song be playing, then stop it
    TheSoundMixer::Instance()->stopPlayingGenotypes();
  }
}

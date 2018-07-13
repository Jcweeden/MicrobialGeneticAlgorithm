#include "Microbe.h"
#include <limits.h>


Microbe::Microbe() :
    GameObject(
        rand() % (TheGame::Instance()->getWindowWidth()-30) + 15, //x
        rand() % (TheGame::Instance()->getWindowHeight()-30) + 15,//y
        15.0f,//width (used as the radius)
        0,    //height (not used)
        rand() % 225 + 30,//r
        rand() % 225 + 30,//g
        rand() % 225 + 30,//b
        rand() % 160 + 40 //a
               ),
    foodEaten(0), dying(false), speedMultiplier(10.0f), startingRadius(15.0f), childRadius(0.0f), radiusToShrinkBy(0.0f), framesToNextPathfind(0), childrenProduced(0), microbeSpawnTime(SDL_GetTicks()), currentStatus(0), nearestFoodSource(-1), nearestPartnerIndex(-1)
{
}

void Microbe::draw()
{
  //draw child, should the microbe have one
  if ( childRadius > 0)
  {
    filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), childRadius, colourR, colourG, colourB, colourA);
    circleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), childRadius, 0, 0, 0, 255);
  }

  //draw microbe itself
  filledCircleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), width, colourR, colourG, colourB, colourA);
  circleRGBA(TheGame::Instance()->getRenderer(), getPositionX(), getPositionY(), width, 0, 0, 0, 255);
}

void Microbe::update()
{
  //resetVal is how many frames should elapse between each update of running the pathfinding algorithm
  int resetVal = 4;

  //if the shrinkage is due to reproduction
  if (radiusToShrinkBy > 0 )
  {
    if (!dying) {
      width -=  startingRadius/100;
      radiusToShrinkBy -= startingRadius/100;
    }

    //else, shrinkage is due to death
    else {
      width -=  startingRadius/100;
      radiusToShrinkBy -= startingRadius/100;

      //when shrinkage of the microbe reaches the edges of the child, reduce the size
      //of the child with the microbe itself
      if (width < childRadius) childRadius = width;
    }
  }

  //if off the screen and not dying
  if ((position.getX() < 0 || position.getX() > TheGame::Instance()->getWindowWidth() ||
       position.getY() < 0 || position.getY() > TheGame::Instance()->getWindowHeight()) &&
      !dying)
  {
    //find a path towards the center of the screen
    moveTowards(Vector2D(TheGame::Instance()->getWindowWidth()/2,
                         TheGame::Instance()->getWindowHeight()/2));
  }
  //if has eaten enough food to reproduce
  else if (foodEaten >= foodRequiredToMate && !dying)
  {
    if (framesToNextPathfind <= 0) {
      //locateNearestFoodSource will set new pathway should one exist
      int nearestPartnerIndex = locateNearestReproductivePartner(); //get index of nearest food source
      framesToNextPathfind = resetVal;  //reset number of frames countdown to find new path
      currentStatus = 2; //update UI to say we are seeking a partner

      if (nearestPartnerIndex == -1)//no partner was found
      { //go to random location
        currentStatus = 3; //update UI to say we are waiting for an available partner
        pathFinder.findPath(position, generateRandomNearLocation()); //and generate a path to a random location
        framesToNextPathfind = resetVal*4;  //reset number of frames countdown to find new path to higher val
      }
    }
    //if a partner available
    if (nearestPartnerIndex != -1) {
      if (GameObject::checkForCollisionWithCircle(
              TheEnvironment::Instance()->microbes[nearestPartnerIndex]))
      {
        //get fitnesses of this microbe and of partner
        unsigned thisMicrobeFitness = mga.getFitness();
        unsigned partnerFitness = TheEnvironment::Instance()->microbes[nearestPartnerIndex]->mga.getFitness();

        std::cout<< "thisMicrobeFitness: " << thisMicrobeFitness << " partnerFitness: " << partnerFitness << "\n";

        //if this is the stronger microbe, or both microbe's have same fitness
        if (thisMicrobeFitness > partnerFitness || thisMicrobeFitness == partnerFitness)
        {
          //produce a child from this microbe's genes
          produceChild(TheEnvironment::Instance()->microbes[nearestPartnerIndex]);         

          //kill the partner
          TheEnvironment::Instance()->microbes[nearestPartnerIndex]->deathFromReproduction();

          //remove child from center of microbe, increment childrenProduced counter
          completedReproduction();
        }
        else //partner is the stronger microbe
        {
          //spawn a child from the partner
          TheEnvironment::Instance()->microbes[nearestPartnerIndex]->produceChild(this);
          TheEnvironment::Instance()->microbes[nearestPartnerIndex]->completedReproduction();

          //and kill off this microbe
          deathFromReproduction();
        }
      }
    }
    
    //if there is a path 
    if (pathFinder.pathway.size() > 0) {
      //continue to move towards the nearest foodSource //USING Astar
      moveTowards(pathFinder.pathway.front()->getNodeCentralPosition());
    }
  }
  //else not eaten enough food, look for nearest food source
  else if (!dying)  
  {
    //if on frame to find new closest food source
    if (framesToNextPathfind <= 0) {

      //locateNearestFoodSource will set new pathway should one exist
      nearestFoodSource = locateNearestFoodSource(); //get index of nearest food source
      framesToNextPathfind = resetVal;  //reset number of frames countdown to find new path

      currentStatus = 0; //update UI to say we are seeking food

      if (nearestFoodSource == -1)//no food source was found
      { //go to random location
        currentStatus = 1; //update UI to say we are waiting for an available food source
        pathFinder.findPath(position, generateRandomNearLocation()); //and generate a path to a random location
        framesToNextPathfind = resetVal*4;  //reset number of frames countdown to find new path to higher val
      }
    }

    //if a food source available
    if (nearestFoodSource != -1) {
      //check if in contact with the currently tracked food source,
      if (GameObject::checkForCollisionWithCircle(TheEnvironment::Instance()->foodSources[nearestFoodSource]))
      {
        //if so, run appropriate code to reduce size of food source
        TheEnvironment::Instance()->foodSources[nearestFoodSource]->consumedByMicrobe();
        //and increase size and consumuption counter for microbe
        consumedFoodSource();
      }
    }

    //if there is a path 
    if (pathFinder.pathway.size() > 0) {
      //continue to move towards the nearest foodSource //USING Astar
      moveTowards(pathFinder.pathway.front()->getNodeCentralPosition());
    }
  }
  else //dying - randomly move about whilst shrinking
  {
    currentStatus = 4;
    if (framesToNextPathfind <= 0) {
      pathFinder.findPath(position, generateRandomNearLocation());
      framesToNextPathfind = resetVal*4;
    }

    if (pathFinder.pathway.size() > 0) {
      //move towards random location  //USING Astar
      moveTowards(pathFinder.pathway.front()->getNodeCentralPosition());
    }
  }
    
  framesToNextPathfind--;
    
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

  acceleration = dirToMove * (speedMultiplier / 100);
}

void Microbe::clean()
{
  pathFinder.clean();
}

//calculates a path to the closest accessible foodSource and returns the index of it
int Microbe::locateNearestFoodSource()
{
  //if there are currently foodsources within the environment
  if (TheEnvironment::Instance()->foodSources.size() > 0) {

    //init vec to hold distances between microbe and all food sources. index in vector is index of foodSource
    std::vector<float> distances (TheEnvironment::Instance()->foodSources.size(), UINT_MAX);

    //for each food source
    for (size_t i = 0; i < TheEnvironment::Instance()->foodSources.size(); i++)
    {
      //store the distance between the food source and microbe
      distances[i] = position.calcDistance(TheEnvironment::Instance()->foodSources[i]->position);
    }
      
    //set a limit on the number of food sources to check
    //(required as A* is run for each one if they are not close)
    unsigned numFoodSourcesToCheck = 5;
    if (numFoodSourcesToCheck > distances.size()) numFoodSourcesToCheck = distances.size();

    //for the number of food sources to check
    for (size_t i = 0; i < numFoodSourcesToCheck; i++)
    {
      //find the closest one
      float minDistanceIndex = 0;
      for (size_t j = 1; j < distances.size(); j++)
      {        

        //if the distance is less
        if (distances[j] < distances[minDistanceIndex])
        {
          //save the index
          minDistanceIndex = j; 
        }   
      }
        
      //check if there is a path from the microbe to the food source
      if (distances[minDistanceIndex] != UINT_MAX)
      {
        if (pathFinder.findPath(position, TheEnvironment::Instance()->foodSources[minDistanceIndex]->position))
        {
          nearestFoodSource = minDistanceIndex;
          return nearestFoodSource; //if there is a path, return index of closest found foodsource
        }
        else
        {
          distances[minDistanceIndex] = UINT_MAX; //else, remove from the list
        }
      }
    } //and loop and try the next closest food source

    //if iterated numFoodSourcesToCheck times and none were found, return no foodSource found
    nearestFoodSource = -1;
    return nearestFoodSource;
  }
  else //no foodSources found, return -1, no foodSource found
  {
    nearestFoodSource = -1;
    return nearestFoodSource;
  }
}

//check each microbe to see if they are ready to reproduce
int Microbe::locateNearestReproductivePartner()
{
  //if there are currently other microbes within the environment
  if (TheEnvironment::Instance()->microbes.size() > 0) {
    //init vec to hold distances between microbe and all other reproductive mics. index in vector is index of microbe
    std::vector<float> distances (TheEnvironment::Instance()->microbes.size(), UINT_MAX); 

    unsigned numReproductivePartners = 0;
      
    for (size_t i = 0; i < TheEnvironment::Instance()->microbes.size(); i++) //for each microbe
    {
      if (TheEnvironment::Instance()->microbes[i] != this) //if not this microbe
      {
        //and if the microbe is ready to reproduce
        if (TheEnvironment::Instance()->microbes[i]->isReadyToReproduce())
        {
          //store the distance between the microbe and potential partern
          distances[i] = position.calcDistance(TheEnvironment::Instance()->microbes[i]->position); 
          //increment count of partners available to reproduce
          numReproductivePartners++;
        }
      }
    }

    if (numReproductivePartners > 0) //if partners were found
    {
      //set a limit on the number of partners to check
      //(required as A* is run for each one if they are not close)
      unsigned numPartnersToCheck = 5;
      if (numPartnersToCheck > numReproductivePartners) numPartnersToCheck = numReproductivePartners;

      //for the number of partners to check
      for (size_t i = 0; i < numPartnersToCheck; i++)
      {
        //find the closest one
        float minDistanceIndex = 0;
        for (size_t j = 1; j < distances.size(); j++)
        {        
          //if the distance is less than closest one found yet
          if (distances[j] < distances[minDistanceIndex])
          {
            //save the index
            minDistanceIndex = j; 
          }   
        }
        //and check if there is a path from the microbe to the partner
        if (pathFinder.findPath(position, TheEnvironment::Instance()->microbes[minDistanceIndex]->position))
        {
          nearestPartnerIndex = minDistanceIndex;
          return nearestPartnerIndex; //if there is a path, return index of closest found foodsource
        }
        else
        { //there is no path here 
          distances[minDistanceIndex] = UINT_MAX; //take out of running in next search
        }
        //so loop and try the next closest partner
      }
      //if iterated numPartnersToCheck times and none were found, return no partner found
      nearestPartnerIndex = -1;
      return nearestPartnerIndex;
    }

    else //there is only a single microbe, so return -1
    {
      nearestPartnerIndex = -1;
      return nearestPartnerIndex;
    }
  }
  else //no microbe found, so return -1, no partner found
  {
    nearestPartnerIndex = -1;
    return nearestPartnerIndex;
  }
}

void Microbe::consumedFoodSource()
{
  //increase size of microbe
  GameObject::width += ((startingRadius/foodRequiredToMate)*1.1f) * 2;

  //decrease speed of microbe up until 10% of original speed
  if (speedMultiplier > 0.1f)
  {
    //std::cout << speedMultiplier << "\n";
    speedMultiplier -= (speedMultiplier/8000);
  }

  //increase mass of microbe
    
  //add value to total food consumption towards next reproduction
  foodEaten += 2;
    
  //increase child draw size
  childRadius +=  (startingRadius/foodRequiredToMate) * 2;

  //if large enough to reproduce, is handled in update()
}

void Microbe::completedReproduction()
{
  //increment the counter of how many children the microbe has produced
  childrenProduced++;
    
  //reset food counter so will start collecting food once again
  foodEaten = 0;

  //set radiusToShrinkBy to size of child so over next frames will reduce down in size
  radiusToShrinkBy = startingRadius; //shrink by the size of the child now

  //the child has been removed and instantiated as its own class, so does not need to be drawn here anymore
  childRadius = 0.0f;

  //reset to having no partner to follow
  nearestPartnerIndex = -1;
}

//returns true, ready to reproduce if it has consumed enough food and is not dying
bool Microbe::isReadyToReproduce()
{
  if (!dying) {
    if (foodEaten >= foodRequiredToMate)
    {
      return true;
    }
  } 
  return false;
}


void Microbe::deathFromReproduction()
{
  //increment the counter of how many children the microbe has produced
  childrenProduced++;
    
  //set radiusToShrinkBy to size of microbe so over next frames will shrink entirely
  radiusToShrinkBy = width;

  //set dying to true to disable reproduction
  dying = true;

  //remove all velocity so the user can clearly see the microbe is dying
  velocity.clear();

  //reduce the speed of the microbe as it dies
  speedMultiplier = 0.1f;

  //reset to having no partner to follow
  nearestPartnerIndex = -1;
}

//called from the surviving parent. a child is produced with the losingParent's genes, and with one correct gene from the surviving parent copied over. There is then a 50% chance of mutating a random gene to a random new value in the child
void Microbe::produceChild(const Microbe* losingParent)
{
  Microbe* childMicrobe = new Microbe(); //potential memory leak

  float defaultDampingVal = 0.6f;

  float dampingVariation =  -(defaultDampingVal/10) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((defaultDampingVal/10)-(-(defaultDampingVal/10)))));

  childMicrobe->microbeID = TheEnvironment::Instance()->microbeCounter++;
    
  //set child to the position of the spawning parent
  childMicrobe->setPosition(position);
    
  childMicrobe->setVelocity(0,0);
  childMicrobe->setMass(1.0f);
  childMicrobe->setDamping(0.6f + dampingVariation);
  childMicrobe->setAcceleration(0.0f, 0.0f); //no gravity

  //set child to retain the same colours as the parent
  childMicrobe->colourR = colourR;
  childMicrobe->colourG = colourG;
  childMicrobe->colourB = colourB;
  childMicrobe->colourA = colourA;

  childMicrobe->pathFinder.setGrid(&TheEnvironment::Instance()->grid);

  //initially set genes of child to those of the losing parent
  for (size_t i = 0; i < losingParent->mga.genotypes.size(); i++)
  {
    childMicrobe->mga.genotypes[i] = losingParent->mga.genotypes[i];
  }
    
  //attempt to copy one correct gene over one incorrect gene
  size_t randomGeneIndex;
  bool foundGeneToOverwrite = false;
  std::vector<unsigned> genesToAttempt = {0,1,2,3};

  //if has a correct gene where the child has an incorrect gene
    
  do {
    //randomly select a previously unchecked gene index
    unsigned randIndex = rand() % genesToAttempt.size();
    randomGeneIndex = genesToAttempt[randIndex];
    genesToAttempt.erase(genesToAttempt.begin() + randIndex);
      
    //if the parent gene is correct
    if (mga.isGenotypeCorrect(mga.genotypes[randomGeneIndex]))
    {
      //and if the same gene for the child is incorrect
      if (!childMicrobe->mga.isGenotypeCorrect(mga.genotypes[randomGeneIndex]))
      {
        //we have found a gene to overwrite
        std::cout << "found gene to overwrite\n";
        foundGeneToOverwrite = true;
      }
    }
  } while (foundGeneToOverwrite == false && genesToAttempt.size() > 0);

  //overwrite the incorrect child gene with a correct parental gene
  if (foundGeneToOverwrite)
    childMicrobe->mga.setGenotype(randomGeneIndex, mga.genotypes[randomGeneIndex]);

    
  //and with 50% probability mutate a random gene
  if (rand() % 2 == 1)
  {
    std::cout << "mutated random gene\n";
    childMicrobe->mga.mutateGenotype();
  }

  std:: cout << "child fitness: " << childMicrobe->mga.getFitness() << "\n\n\n";

  //if max fitness has not been achieved before
  if (TheEnvironment::Instance()->timeMaxFitnessAchieved == 0)
  {
    //and has been achieved now
    if (childMicrobe->mga.getFitness() == 4)
    {
      //save the number of reproductiyons that took place before reaching max fitness
      TheEnvironment::Instance()->maxFitnessAchievedReproductions =
          TheEnvironment::Instance()->microbeCounter;
      //and how long this took
      TheEnvironment::Instance()->timeMaxFitnessAchieved = SDL_GetTicks();
    }
  }
    
  //add to the list of microbes
  TheEnvironment::Instance()->microbes.push_back(childMicrobe);
  std:: cout << "repo complete\n\n\n";
}

//randomly generate a location near to the microbe's current position that is plus/minus 1/6 of the window size away for both width and height
Vector2D Microbe::generateRandomNearLocation()
{
  //ints that will store rand gen coords
  int x, y;

  //amount of size to randomly add/minus from current position 
  int randSizeX = TheGame::Instance()->getWindowWidth() / 6;
  int randSizeY = TheGame::Instance()->getWindowHeight() / 6;


  do {
    x = position.getX() + (rand() % (randSizeX*2) - randSizeX);
  }
  while ( x >= TheGame::Instance()->getWindowWidth() || x < 0); //do until within the boundaries

  do {
    y = position.getY() + (rand() % (randSizeX*2) - randSizeX);
  }
  while ( y >= TheGame::Instance()->getWindowHeight() || y < 0);

  //return new random position
  return Vector2D(x,y);
}

void Microbe::playGenotypeSong()
{
  //pass the microbe's current genes to the sound mixer to be played
  SoundMixer::Instance()->loadToQueuedGenotypes(mga.genotypes);
}


#include "Grid.h"

#include "Environment.h"


Grid::Grid()
    : gridSize(Vector2D(0,0)), selectedObjectPosition(Vector2D(-1,-1))
{}

Grid::Grid(unsigned p_gridSizeX, unsigned p_gridSizeY, float p_nodeDiameter)
    : gridSize(Vector2D(p_gridSizeX, p_gridSizeY)), nodeDiameter(p_nodeDiameter), selectedObjectPosition(Vector2D(-1,-1))
{
  nodeRadius = nodeDiameter/2;

  //calulate how many nodes of size nodeDiameter will fit into the grid
  nodeCountX = gridSize.getX()/nodeDiameter;
  nodeCountY = gridSize.getY()/nodeDiameter;
  
  std::cout << "nodeCountX: " << nodeCountX << " nodeCountY: " << nodeCountY << "\n";


  //init 2D vector of nodes to hold nodeCount
  grid = std::vector<std::vector<Node*> > (nodeCountX, std::vector<Node*>(nodeCountY));

  setupGrid();
}

void Grid::setupGrid()
{
  
  //traverse across each row setting values
  for (size_t y = 0; y < nodeCountY; y++)
  {
    for (size_t x = 0; x < nodeCountX; x++)
    {
      bool traversable = true;
      //check if there is an obstacle in this area that renders it intraversable
      //check box against list of obstacles

      //create new node with this variables
      Node* node = new Node(Vector2D(nodeDiameter * x, nodeDiameter * y), x, y, nodeDiameter, nodeDiameter, traversable);

      //store in vector of nodes
      grid[x][y] = node;
    }
  }

  std::cout << "before setting obstacle nodes to intraversable\n";
  
  //determine which of these newly created nodes are in contact with an obstacle, and set traversable = false
  setObstacleNodesToUntraversable();
  
  std::cout << "successfully before setting obstacle nodes to intraversable, completed filling grid\n";
  
}

void Grid::setObstacleNodesToUntraversable()
{ 
  //check each obstacle against the grid, setting those nodes in contact with an obstacle to untraversable
  for (size_t i = 0; i < TheEnvironment::Instance()->obstacles.size(); i++)
  {
    int currentX = TheEnvironment::Instance()->obstacles[i]->position.getX();
    int currentY = TheEnvironment::Instance()->obstacles[i]->position.getY();
    int width = TheEnvironment::Instance()->obstacles[i]->width;
    int height = TheEnvironment::Instance()->obstacles[i]->height;    

    int widthRemaining = width;
    int heightRemaining = height;
    
    //start checking for contacts at the lowest point of the obstacle, and remove and check nodeDiameter heigher each iteration
    while (heightRemaining >= 0)
    {
      //while there is still width to check at this height
      while (widthRemaining > 0)
      {
        //if at this width and height we are still within the bounds of the grid
        if (currentX+widthRemaining >= 0 && currentX+widthRemaining <= gridSize.getX() &&
            currentY+heightRemaining >= 0 && currentY+heightRemaining <= gridSize.getY() )
        {
          //then this node is covered by obstacle - mark traversable as false
          getNodeFromCoords(Vector2D(currentX+widthRemaining, currentY+heightRemaining))->traversable = false;
        }
        //we have checked at this width, now remove nodeDiameter and check again
        widthRemaining -= nodeDiameter;

        //if have surpassed the edges of the shape, check one last time at it's boundary
        if (widthRemaining <= 0)
        {
          //if at this width and height we are still within the bounds of the grid
          if (currentX+widthRemaining >= 0 && currentX+widthRemaining <= gridSize.getX() &&
              currentY+heightRemaining >= 0 && currentY+heightRemaining <= gridSize.getY() )
          {
            //node is covered by obstacle - mark traversable as false
            getNodeFromCoords(Vector2D(currentX+0, currentY+heightRemaining))->traversable = false;
          }
        }
      }
      
      //have finished checking at all widths for this height of the shape, so move up the shape and begin again 
      heightRemaining -= nodeDiameter;
      //reset width to begin check again
      widthRemaining = width;

      //if have not already checked at the height boundary 
      if (heightRemaining != -nodeDiameter)
      {
        //before starting again, if have height surpassed the edges of the shape,
        //check one last time at it's boundary before the while loop terminates
        if (heightRemaining < 0) heightRemaining = 0;
      }
    }
  }
  
  std::cout << "successfully set obstacle nodes to intraversable\n";
}


void Grid::drawGrid()
{
  
  //Draw whether each node is traversable or not
  for (size_t y = 0; y < nodeCountY; y++)
  {
    for (size_t x = 0; x < nodeCountX; x++)
    {
      //if traversable draw in green,
      if (grid[x][y]->traversable)
      {
        boxRGBA (TheGame::Instance()->getRenderer(),
                 grid[x][y]->position.getX(), grid[x][y]->position.getY(),
                 grid[x][y]->position.getX() + nodeDiameter, grid[x][y]->position.getY() + nodeDiameter,
                 0, 255, 0, 255);
      }
      else //is not travesable so draw in red
      {
        boxRGBA (TheGame::Instance()->getRenderer(),
                 grid[x][y]->position.getX(), grid[x][y]->position.getY(),
                 grid[x][y]->position.getX() + nodeDiameter, grid[x][y]->position.getY() + nodeDiameter,
                 255, 0, 0, 255);
      }
    }

    
    //draw pathway in some colour
    
    for (size_t i = 0; i < pathway.size(); i++ )
    {
      boxRGBA (TheGame::Instance()->getRenderer(),
               pathway[i]->position.getX(), pathway[i]->position.getY(),
               pathway[i]->position.getX() + nodeDiameter, pathway[i]->position.getY() + nodeDiameter,
               125, 125, 0, 255);
    }
    

    //draw the node the selected object is in (if one is selected)
    if (selectedObjectPosition.getX() >= 0 && selectedObjectPosition.getX() <= gridSize.getX() &&
        selectedObjectPosition.getY() >= 0 && selectedObjectPosition.getY() <= gridSize.getY() )
    {
      Node* node = getNodeFromCoords(selectedObjectPosition);
       boxRGBA (TheGame::Instance()->getRenderer(),
                 node->position.getX(), node->position.getY(),
                 node->position.getX() + nodeDiameter, node->position.getY() + nodeDiameter,
                 0, 0, 255, 255);
      
    }
    
    //draw black borders of the grid (if enabled)
    for (size_t x = 0; x <= nodeCountX; x++)
    {//draw vertical lines
      vlineRGBA (TheGame::Instance()->getRenderer(),
                 x * nodeDiameter, 0,
                 gridSize.getY(),
                 0, 0, 0, 255);
    }
    for (size_t y = 0; y <= nodeCountY; y++)
    {//draw horizontal lines
      hlineRGBA (TheGame::Instance()->getRenderer(),
                 0, gridSize.getX(),
                 y * nodeDiameter,
                 0, 0, 0, 255);
    }
  }
  
}


void Grid::clean()
{
  //delete each node in grid
  for (size_t y = 0; y < nodeCountY; y++)
  {
    for (size_t x = 0; x < nodeCountX; x++)
    {
      delete grid[x][y];
    }
  }
}

Node* Grid::getNodeFromCoords(Vector2D worldPosition)
{
  //if inside the grid
  if( worldPosition.getX() >= 0 && worldPosition.getX() <= gridSize.getX() &&
      worldPosition.getY() >= 0 && worldPosition.getY() <= gridSize.getY() )
  {
    //calculate what percentage x & y are in the grid
    float percentageX = worldPosition.getX() / gridSize.getX();
    float percentageY = worldPosition.getY() / gridSize.getY();

    
    int x = nodeCountX * percentageX;
    int y = nodeCountY * percentageY;

    //std::cout << "Grid:getNodeFromCoords() - node is at: x:" << x << " y:" << y << "\n";
    //return the node at this location
    return grid[x][y];
  }
  else
  {
    return grid[0][0];
  }

}



//given the passed in node, any existing nodes in the nine surrounding grids are added to neighbours and returned.
std::vector<Node*> Grid::getNeighbouringNodes(Node* node)
{
  //vector will contain all existing nodes neighbouring parameter node
  std::vector<Node*> neighbours;

  //for the node, before, including and after in the x axis
  for (int x = -1; x <= 1; x++)
  {
    //for the node, before, including and after in the y axis
    for (int y = -1; y <= 1; y++)
    {
      //if the node is the central of the nine (the node passed in), skip this iteration
      if (x == 0 && y == 0) continue;

      //calculate the neighbour's coords
      int neighbourX = node->gridXIndex + x;
      int neighbourY = node->gridYIndex + y;
      
      //if the node is within the limits of the grid
      if (neighbourX >= 0 && neighbourX <= (int)nodeCountX-1 &&
          neighbourY >= 0 && neighbourY <= (int)nodeCountY-1)
      {
        //add to neighbours
        neighbours.push_back(grid[neighbourX][neighbourY]);
      } 
    }
  }
  
  //return the list of existing neighbouring nodes
  return neighbours;
}



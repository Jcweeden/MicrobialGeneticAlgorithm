#include "PathFinder.h"
#include <list>
PathFinder::PathFinder(/*Grid* p_grid*/)
    : grid(new Grid())
{

}

void PathFinder::setGrid(Grid* p_grid)
{
  grid = p_grid;
}

bool PathFinder::findPath(Vector2D startingPosition, Vector2D targetPosition)
{
  Node* startPositionNode = grid->getNodeFromCoords(startingPosition);
  Node* targetPositionNode = grid->getNodeFromCoords(targetPosition);
  //if the start position is null (e.g., getNodeFromCoords returns that the coords are not on the map
  //should one position be off the grid, then return as there will be no viable path
  if (!startPositionNode || !targetPositionNode)
  { //then do not find a new path, return
    return false;
  }
  //or if the target node is not traversable then return also
  else if (targetPositionNode->traversable == false)
  {
    return false;
  }
  
  heap.setHeapSize(grid->nodeCountX*grid->nodeCountY); //std::list<Node*> openSet;
  std::vector<Node*> closedSet;

  //add first node to end of list of openedNodes
  heap.addItem(startPositionNode);/*openSet*/ //heap.items.push_back(startPositionNode);

  //while there are still nodes to check
  while (/*openSet*/heap.getHeapSize() > 0)
  {
    //GET NODE IN OPEN SET WITH LOWEST fCost
    Node* node = /*openSet.front()*/heap.removeFirstItem();  //retrieve the first node for comparision
    closedSet.push_back(node);
    
    //IF IS THE TARGET NODE
    if (node == targetPositionNode)
    {
      //RETRACE
      retracePath(startPositionNode, targetPositionNode);
      // std::cout << "heap.size() upon completion of path: " << heap.getHeapSize() << "\n";
      closedSet.clear();
      heap.clean();
      grid->resetGrid(); //dubious if required
      // std::cout << "pathfinding reset correctly\n";
      return true;
    }
    
    //FOR EACH NEIGHTBOURING NODE
    for (Node* neighbour : grid->getNeighbouringNodes(node))
    {
      //if neigh is in closedSet, or is intraversable then skip to next neighbour
      if (neighbour->traversable == false ||
          std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end()) continue;

      //IF NEW PATH TO NEIGHBOUR IS SHORTER THAN OLD PATH OR NEIGHBOUR IS NOT IN OPEN
      //recalculate movement cost for already open neighbours
      int newMovementCostToNeighbour = node->gCost + calcManhattanDistance(node, neighbour);

      //bool found = (std::find(/*openSet*/heap.items.begin(), /*openSet*/heap.items.end(), neighbour) != /*openSet*/heap.items.end());

      if (newMovementCostToNeighbour < neighbour->gCost || !heap.isInHeap(neighbour) )// (found == false)) //!openSet.contains(neighbour)*/
      {
        neighbour->gCost = newMovementCostToNeighbour;
        neighbour->hCost = calcManhattanDistance(neighbour,targetPositionNode);
        neighbour->parent = Vector2D(node->gridXIndex,node->gridYIndex);

        //bool found = (std::find(/*openSet*/heap.items.begin(), /*openSet*/heap.items.end(), neighbour) != /*openSet*/heap.items.end());
        
        if (!heap.isInHeap(neighbour))// (found == false) //!openSet.contains(neighbour)
        {
          /*openSet*//*heap.items.push_back*/heap.addItem(neighbour);
        }
        else
        {
          heap.updateItem(neighbour);
        }
      }
    }
  }
  //return to alleviate warning - return false if all paths explored and no route to target found.
  return false;
}

void PathFinder::retracePath(Node* start, Node* end)
{
  std::vector<Node*> path;
  Node* currentNode = end;

  while (currentNode != start)
  {
    path.insert(path.begin(), currentNode);
    currentNode = grid->grid[currentNode->parent.getX()][currentNode->parent.getY()];
  }

  //std::cout << "path size: " << path.size() << "\n";
  pathway = path;
}

//calculate the distance between two nodes in the grid strictly using only horizontal and/or vertical movements in
//the path between nodeA and nodeB (that is moving only along grid lines), not diagonally using pythagorean theorem
int PathFinder::calcManhattanDistance(Node* nodeA, Node* nodeB)
{
  int distanceX = abs((int)nodeA->gridXIndex - (int)nodeB->gridXIndex);
  int distanceY = abs((int)nodeA->gridYIndex - (int)nodeB->gridYIndex);

  if (distanceX > distanceY) return 14 * distanceY + 10 * (distanceX-distanceY);

  else return 14 * distanceX + 10 * (distanceY-distanceX);
}

void PathFinder::clean()
{
  pathway.clear();
}

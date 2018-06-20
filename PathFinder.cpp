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

void PathFinder::findPath(Vector2D startingPosition, Vector2D targetPosition)
{
  Node* startPositionNode = grid->getNodeFromCoords(startingPosition);
  Node* targetPositionNode = grid->getNodeFromCoords(targetPosition);

  std::list<Node*> openSet;
  std::vector<Node*> closedSet;
  //add first node to end of list of openedNodes
  openSet.push_back(startPositionNode);

  //while there are still nodes to check
  while (openSet.size() > 0)
  {
    //GET NODE IN OPEN SET WITH LOWEST fCost
    Node* node = openSet.front();  //retrieve the first node for comparision
    
    //for each node in openSet (start at 1 to exclude node assigned in line above)
    for (size_t i = 1; i < openSet.size(); i++) {
      //if openSet[i] has lower or equal cost then the currentNode
      if (openSet.front()->fCost() < node->fCost() || openSet.front()->fCost() == node->fCost())
      {
        //if have the same fCost then determine which is closest to target by comparing hCost
        if (openSet.front()->hCost < node->hCost) node = openSet.front();
      }
    }
    //remove currentNode from openSet and add to closedSet
    openSet.remove(node);
    closedSet.push_back(node);

    //IF IS THE TARGET NODE
    if (node == targetPositionNode)
    {
      //RETRACE
      retracePath(startPositionNode, targetPositionNode);
    }

    //FOR EACH NEIGHTBOURING NODE
    for (Node* neighbour : grid->getNeighbouringNodes(node))
    {
      //if neigh is not in closedSet, or is intraversable then skip to next neighbour
      if (neighbour-> traversable == false) continue;
      if (std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end()) continue;

      //IF NEW PATH TO NEIGHBOUR IS SHORTER THAN OLD PATH OR NEIGHBOUR IS NOT IN OPEN
      //recalculate movement cost for already open neighbours
      int newMovementCostToNeighbour = node->gCost + calcManhattanDistance(node, neighbour);

      bool found = (std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end());

      if (newMovementCostToNeighbour < neighbour->gCost || found == false /*!openSet.contains(neighbour)*/)
      {
        neighbour->gCost = newMovementCostToNeighbour;
        neighbour->hCost = calcManhattanDistance(neighbour,targetPositionNode);
        neighbour->parent = Vector2D(node->gridXIndex,node->gridYIndex);

        if (found == false /*!openSet.contains(neighbour)*/)
          openSet.push_back(neighbour);
      }
    }

  }
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

  std::cout << "path size: " << path.size() << "\n";
  grid->pathway = path;
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

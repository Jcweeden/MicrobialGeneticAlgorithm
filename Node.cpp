#include "Node.h"

Node::Node(Vector2D p_position, unsigned p_gridXIndex, unsigned p_gridYIndex, unsigned p_gridWidth, unsigned p_gridHeight, bool p_traversable)
    : position(p_position),
      gridXIndex(p_gridXIndex), gridYIndex(p_gridYIndex),
      gridWidth(p_gridWidth), gridHeight(p_gridHeight),
      traversable(p_traversable),
      parent(Vector2D(0,0))
{
}

Node::Node()
    : position(Vector2D(0,0)),
      gridXIndex(0), gridYIndex(0),
      gridWidth(0), gridHeight(0),
      traversable(true),
      parent(Vector2D(0,0))
{}

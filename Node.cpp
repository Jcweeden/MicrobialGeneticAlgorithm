#include "Node.h"

Node::Node(Vector2D p_position, unsigned p_gridLengthX, unsigned p_gridLengthY, bool p_traversable)
    : position(p_position), gridX(p_gridLengthX), gridY(p_gridLengthY), traversable(p_traversable)
{
}

Node::Node()
    : position(Vector2D(0,0)), gridX(0), gridY(0), traversable(true)
{}

#include "node.h"
#include <cmath>

int Node::height()
{
	if (this == NULL)
		return 0;

	int leftHeight = (left == NULL) ? 0 : left->height();
	int rightHeight = (right == NULL) ? 0 : right->height();

	return max(leftHeight, rightHeight);
}

int Node::balancing_factor()
{
	int leftHeight = (left == NULL) ? 0 : left->height();
	int rightHeight = (right == NULL) ? 0 : right->height();

	return (abs(leftHeight - rightHeight));
}

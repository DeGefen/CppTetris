#include "GoodPositionNode.h"

bool GoodPositionNode::betterThen(GoodPositionNode* node) { // if "this" is better then "node"
	if (node->blockedSpaces < blockedSpaces) return false;
	if (node->blockedSpaces > blockedSpaces) return true;

	if (node->bottomY < bottomY) return true;
	if (node->bottomY > bottomY) return false;

	if (node->coverage < coverage) return true;
	if (node->coverage > coverage) return false;

	if (node->headX > headX) return true;
	return false;
}

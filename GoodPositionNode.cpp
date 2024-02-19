#include "GoodPositionNode.h"

bool GoodPositionNode::betterThen(GoodPositionNode* node) const { // if "this" is better then "node"

	if (node->linesFilled < linesFilled) return true;
	if (node->linesFilled > linesFilled) return false;

	if (node->blockedSpaces < blockedSpaces) return false;
	if (node->blockedSpaces > blockedSpaces) return true;

	if (node->linesAdded < linesAdded) return false;
	if (node->linesAdded > linesAdded) return true;

	if (node->bottomY < bottomY) return true;
	if (node->bottomY > bottomY) return false;

	if (node->coverage < coverage) return true;
	if (node->coverage > coverage) return false;

	if (node->neighbors < neighbors) return true;
	if (node->neighbors > neighbors) return false;

	if (node->headX > headX) return true;
	if (node->headX < headX) return false;

	return false;
}

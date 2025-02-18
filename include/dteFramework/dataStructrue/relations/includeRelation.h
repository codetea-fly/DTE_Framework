#pragma once

#include "relation.h"

class DTEFramework_API includeRelation : public relation
{
public:
	includeRelation(dte *d);
};

includeRelation::includeRelation(dte *d) {
	this->pointTo = "包含";
	this->pointFrom = "被包含于";
	this->adjacency.clear();
	this->dtPointer = d;
}


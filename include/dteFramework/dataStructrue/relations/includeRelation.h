#pragma once

#include "relation.h"

class DTEFramework_API includeRelation : public relation
{
public:
	includeRelation(dte *d);
};

includeRelation::includeRelation(dte *d) {
	this->pointTo = "����";
	this->pointFrom = "��������";
	this->adjacency.clear();
	this->dtPointer = d;
}


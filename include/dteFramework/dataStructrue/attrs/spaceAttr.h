#pragma once

#include "attribute.h"

class DTEFramework_API spaceAttr : public attribute
{
public:
	inline int test();
};

int spaceAttr::test() {
	return 0;
}
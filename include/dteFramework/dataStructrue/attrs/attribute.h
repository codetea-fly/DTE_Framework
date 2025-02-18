#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <array>

#include <dteFramework/defs.h>

class DTEFramework_API attribute
{
public:
	std::unordered_map<std::string, std::string> kvstore;
public:
	int addValue(std::string key, std::string value);
	int delValue(std::string key);
	int updateValue(std::string key, std::string value);
	std::string getValue(std::string key);
	virtual std::string print();
};


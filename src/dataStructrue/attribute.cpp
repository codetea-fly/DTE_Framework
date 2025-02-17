#include "pch.h"
#include <dteFramework/dataStructrue/attrs/attribute.h>
#include <nlohmann/json.hpp>

int attribute::addValue(std::string key, std::string value)
{
	this->kvstore.emplace(key, value);
	return ERR_OK;
}

int attribute::delValue(std::string key)
{
	this->kvstore.erase(key);
	return ERR_OK;
}

int attribute::updateValue(std::string key, std::string value)
{
	if (delValue(key) != ERR_OK) {
		return ERR_FAIL;
	}
	else {
		return addValue(key, value);
	}
}

std::string attribute::getValue(std::string key)
{
	return this->kvstore.find(key)->second;
}

std::string attribute::print()
{
	std::string result;
	for (auto& kv : this->kvstore) {
		result += "->" + kv.first + " : " + kv.second + "\n";
	}
	return result;
}

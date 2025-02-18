#pragma once

#include <dteFramework/defs.h>
#include <vector>
#include <iostream>
#include <string>
#include "dte.h"
#include <dteFramework/dataStructrue/relations/relation.h>

class dteCollection
{
public:
	std::vector<dte> dtes;
	std::vector<relation> relationTrees;
	std::vector<relation> relationTuples;
public:
	std::string print() {
		std::string result("DTE:====\n");
		try {
			for (dte d : dtes) {
				result += d.print();
			}
			result += "RelationTrees:====\n";
			for (relation r : relationTrees) {
				result += r.print();
			}
			result += "\nRelationTuples:===\n";
			for (relation r : relationTuples) {
				result += r.printTuple();
			}
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		return result;
	}
	int addDte(dte d) {
		this->dtes.push_back(d);
		return ERR_OK;
	}

	int addRelation(relation r) {
		this->relationTrees.push_back(r);
		return ERR_OK;
	}

	int addTuple(relation r) {
		this->relationTuples.push_back(r);
		return ERR_OK;
	}

	//TO-DO ²¹³ävector²Ù×÷
	dte findDte(std::string twinName) {
		//std::cout << "start find" << std::endl;
		for (dte p : dtes) {
			//std::cout << p.getName() << std::endl;
			if (p.getName().compare(twinName) == 0) {
				//std::cout << "found " << twinName << std::endl;
				return p;
			}
		}
	}
};


#pragma once

#include <dteFramework/dataStructrue/dte.h>
#include <dteFramework/defs.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>


using json = nlohmann::json;

class DTEFramework_API relation //关系节点
{
protected:
	std::string pointTo;//指向子节点关系定义
	std::string pointFrom;//父节点指向关系定义
	std::string adjacency;//相邻节点定义
	dte dtPointer;
	std::vector<relation> leftChilds;
	std::vector<relation> rightChilds;
	std::tuple<std::string, std::string, std::string> relationTuple;
public:
	relation() = default;
	relation(dte d) {
		this->pointTo.clear();
		this->pointFrom.clear();
		this->adjacency.clear();
		this->dtPointer = d;
	};
	relation(std::string pt, std::string pf, std::string adj, dte d) {
		this->pointTo = pt;
		this->pointFrom = pf;
		this->adjacency = adj;
		this->dtPointer = d;
	}
	relation(std::string from, std::string desc, std::string to) {
		this->relationTuple = std::make_tuple(from, desc, to);
	}
	//virtual void init(dte *d) = 0;
	inline void addToL(relation r);
	inline void addToR(relation r);
	inline dte* findDte(std::string id);
	inline std::string print(int level = 0);

	json to_relation_json() {
		json res;
		res["pointTo"] = this->pointTo;
		res["pointFrom"] = this->pointFrom;
		res["adjacency"] = this->adjacency;
		res["twinId"] = this->dtPointer.getID();
		res["twinName"] = this->dtPointer.getName();

		res["leftChildren"] = json::array();
		res["rightChildren"] = json::array();

		for (relation r : this->leftChilds) {
			res["leftChildren"].push_back(r.to_relation_json());
		}
		for (relation r : this->rightChilds) {
			res["rightChildren"].push_back(r.to_relation_json());
		}
		return res;
	}

	json to_relation_tuple_json() {
		json result;
		result["from"] = std::get<0>(relationTuple);
		result["desc"] = std::get<1>(relationTuple);
		result["to"] = std::get<2>(relationTuple);
		return result;
	}

	inline std::string printTuple() {
		std::string result;
		result += "(";
		result += std::get<0>(relationTuple);
		result += ", ";
		result += std::get<1>(relationTuple);
		result += ", ";
		result += std::get<2>(relationTuple);
		result += ")\n";
		return result;
	}
};

inline void relation::addToL(relation r) {
	this->leftChilds.push_back(r);
}

inline void relation::addToR(relation r) {
	this->rightChilds.push_back(r);
}

inline dte* relation::findDte(std::string id)
{
	return nullptr;
}

inline std::string relation::print(int level) {
	std::string result;

	result += this->dtPointer.getName();
	if (this->leftChilds.size() == 0 && this->rightChilds.size() == 0) {
		//叶节点，回溯
		level--;
		return result;
	}
	else {
		level++;
		result += "\n";
		for (int i = 0; i < level; i++) {
			result += "    ";
		}
		result += "|_L_" + this->pointTo + "__";
		for (relation p : leftChilds) {
			result += p.print(level);
		}
		result += "\n";
		for (int i = 0; i < level; i++) {
			result += "    ";
		}
		result += "|_R_" + this->pointTo + "__";
		for (relation p : rightChilds) {
			result += p.print(level);
		}
	}

	return result;
}
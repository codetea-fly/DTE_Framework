#include "pch.h"

#include <dteFramework/context/importer/apiImporter.h>
#include <dteFramework/dataStructrue/attrs/abilityAttr.h>
#include <dteFramework/dataStructrue/attrs/extensionAttr.h>
#include <dteFramework/dataStructrue/attrs/geoAttr.h>
#include <dteFramework/dataStructrue/attrs/identityAttr.h>
#include <dteFramework/dataStructrue/attrs/properAttr.h>
#include <dteFramework/dataStructrue/attrs/spaceAttr.h>
#include <dteFramework/dataStructrue/attrs/statusAttr.h>
#include <dteFramework/dataStructrue/dteCollection.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>
#include <string>

using json = nlohmann::json;


template<typename T> std::string converToString(const T& t) {
	std::ostringstream oss;  //创建一个格式化输出流
	oss << t;             //把值传递如流中
	return oss.str();
}

template <typename T>
T initAttr(json j) {
	T result;
	if (!j.is_null()) {
		for (auto& element : j.items()) {
			//std::cout << "addkv:" << element.key() << std::endl;
			if (!element.value().is_null()) {
				if (!element.value().is_string()) {
					result.addValue(element.key(), converToString(element.value()));
				}
				else {
					result.addValue(element.key(), element.value());
				}
			}
			else {
				result.addValue(element.key(), "");
			}
		}
	}
	return result;
}

template <typename T>
T initArrayAttr(json j) {
	T result;
	if (j.size() != 0) {
		for (int k = 0; k < j.size(); k++) {
			for (auto& element : j[k].items()) {
				//std::cout << "addkv:" << k << "-" << element.key() << std::endl;
				std::string key = std::to_string(k) + "-" + element.key();
				if (!element.value().is_null()) {
					if (!element.value().is_string()) {
						result.addValue(key, converToString(element.value()));
					}
					else {
						result.addValue(key, element.value());
					}
				}
				else {
					result.addValue(key, "");
				}
			}
		}
	}
	return result;
}

template <typename T>
T initExtAttr(json j) {
	T result;
	if (!j.is_null()) {
		for (auto& element : j.items()) {
			//std::cout << "addkv:" << element.key() << std::endl;
			if (!element.value().is_null()) {
				std::string prefix = element.key();
				for (auto& extvalue : element.value().items()) {
					std::string key = prefix + "-" + extvalue.key();
					if (!extvalue.value().is_null()) {
						if (!extvalue.value().is_string()) {
							result.addValue(key, converToString(extvalue.value()));
						}
						else {
							result.addValue(key, extvalue.value());
						}
					}
					else {
						result.addValue(key, "");
					}
				}
			}
		}
	}
	return result;
}

dteCollection apiImport(std::string path) {

	//std::cout << path << std::endl;
	json j;
	dteCollection dteCollect;
	try {
		std::ifstream jfile(path);
		jfile >> j;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	//std::cout << "start parsing" << std::endl;
	try {
		for (int i = 0; i < j.at("result").size(); i++) {
			//解析每个属性
			identityAttr idattr = initAttr<identityAttr>(j.at("result")[i].at("mark"));
			idattr.addValue("twinName", j.at("result")[i].at("twinName"));
			abilityAttr abattr = initArrayAttr<abilityAttr>(j.at("result")[i].at("ability"));
			geoAttr geoattr = initArrayAttr<geoAttr>(j.at("result")[i].at("geometry"));
			spaceAttr spacettr = initAttr<spaceAttr>(j.at("result")[i].at("spaceTime"));
			statusAttr statusattr = initArrayAttr<statusAttr>(j.at("result")[i].at("state"));
			extensionAttr extattr = initExtAttr<extensionAttr>(j.at("result")[i].at("extend"));
			properAttr proattr = initExtAttr<properAttr>(j.at("result")[i].at("proprietary"));
			//组装dte
			dte d(idattr, spacettr, statusattr, geoattr, abattr, extattr, proattr);
			//std::cout << "-----------------" << std::endl;
			//std::cout << d.print() << std::endl;
			//std::cout << "-----------------" << std::endl;
			dteCollect.addDte(d);
		}
		
		//TO-DO 解析关系树
		for (int i = 0; i < j.at("result").size(); i++) {
			for (auto& element : j.at("result")[i].at("relationship").items()) {
				//解析关系文本
				if (!element.value().is_null()) {
					std::string desc = element.value().at("relationDesc");
					std::string delimeter = "-包含于-";
					auto index = desc.find_first_of(delimeter);
					//std::cout << index << std::endl;
					//utf-8中文占3字符
					std::string childName = desc.substr(0, index);
					std::string fatherName = desc.substr(index + 11, desc.length() - index-11);
					//std::cout << childName << " -> " << fatherName << std::endl;
					//find child
					//std::cout << "find child" << std::endl;
					dte child = dteCollect.findDte(childName);
					//find father
					//std::cout << "find father" << std::endl;
					dte father = dteCollect.findDte(fatherName);
					relation r_father(u8"包含", u8"包含于", "", father);
					relation r_child(u8"包含", u8"包含于", "", child);

					r_father.addToL(r_child);
					//遍历已有关系树
					//TO-DO 找出已构建的关系树中和r_father相关的树，并将r_father填入，否则新建以r_father为rootNode的树
					dteCollect.addRelation(r_father);

					//关系组引入
					relation r_tuple(childName, u8"包含于", fatherName);
					dteCollect.addTuple(r_tuple);
				}
 			}
		}

	}
	catch (std::exception& e) {
		std::cout << "error!" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return dteCollect;
}


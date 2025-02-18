#pragma once

#include <dteFramework/dataStructrue/attrs/abilityAttr.h>
#include <dteFramework/dataStructrue/attrs/extensionAttr.h>
#include <dteFramework/dataStructrue/attrs/geoAttr.h>
#include <dteFramework/dataStructrue/attrs/identityAttr.h>
#include <dteFramework/dataStructrue/attrs/properAttr.h>
#include <dteFramework/dataStructrue/attrs/spaceAttr.h>
#include <dteFramework/dataStructrue/attrs/statusAttr.h>
#include <dteFramework/defs.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DTEFramework_API dte
{
protected:
	identityAttr idAttr;
	spaceAttr spAttr;
	statusAttr stAttr;
	geoAttr geAttr;
	abilityAttr abAttr;
	extensionAttr extAttr;
	properAttr proAttr;
public:
	dte() {};
	dte(identityAttr i, spaceAttr s, statusAttr st, geoAttr geo, abilityAttr ab, extensionAttr ext, properAttr pro) {
		this->idAttr = i;
		this->spAttr = s;
		this->stAttr = st;
		this->geAttr = geo;
		this->abAttr = ab;
		this->extAttr = ext;
		this->proAttr = pro;
	}
	std::string print() {
		std::string result = "\nidentity:---\n";
		result += idAttr.print();
		result += "\nspaceTime:---\n";
		result += spAttr.print();
		result += "\nstate:---\n";
		result += stAttr.print();
		result += "\ngeo:---\n";
		result += geAttr.print();
		result += "\nability:---\n";
		result += abAttr.print();
		result += "\nextension:---\n";
		result += extAttr.print();
		result += "\nproper:---\n";
		result += proAttr.print();
		return result;
	}
	std::string getName() {
		return this->idAttr.getValue("twinName");
	}

	std::string getID() {
		return this->idAttr.getValue("twinId");
	}

	json attr_to_json(attribute attr) {
		json res;
		for (auto& kv : attr.kvstore) {
			res[kv.first] = kv.second;
		}
		return res;
	}

	json to_dte_json() {
		json res;
		res["identity"] = attr_to_json(this->idAttr);
		res["spaceTime"] = attr_to_json(this->spAttr);
		res["state"] = attr_to_json(this->stAttr);
		res["geo"] = attr_to_json(this->geAttr);
		res["ability"] = attr_to_json(this->abAttr);
		res["extension"] = attr_to_json(this->extAttr);
		res["property"] = attr_to_json(this->proAttr);
		return res;
	}
};
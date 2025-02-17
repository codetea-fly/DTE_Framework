#include "pch.h"


#include <dteFramework/context/exporter/dteExporter.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>

using json = nlohmann::json;

static json exportDte(dte d) {
    return d.to_dte_json();
}

static json exportRelation(relation r) {
    return r.to_relation_json();
}

static json exportDteArray(std::vector<dte> array) {
    //std::cout << "exporting dte array" << std::endl;
    json res = json::array();
    for (dte d : array) {
        res.push_back(exportDte(d));
    }
    return res;
}

static json exportRelation(std::vector<relation> treeArray) {
    //std::cout << "exporting relation array" << std::endl;
    json res = json::array();
    for (relation r : treeArray) {
        res.push_back(exportRelation(r));
    }
    return res;
}

static json exportRelationTuple(std::vector<relation> tupleArray) {
    json res = json::array();
    for (relation r : tupleArray) {
        res.push_back(r.to_relation_tuple_json());
    }
    return res;
}

int dteExport(std::string path, dteCollection collect)
{
    json res;
    //std::cout << "start exporting" << std::endl;
    try {
        json dteArray = exportDteArray(collect.dtes);
        json treeArray = exportRelation(collect.relationTrees);
        res["dtes"] = dteArray;
        res["relationTrees"] = treeArray;
        res["relationTuples"] = exportRelationTuple(collect.relationTuples);

        std::ofstream o(path);
        o <<  res << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return ERR_FAIL;
    }
    return ERR_OK;
}

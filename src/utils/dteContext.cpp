#include "pch.h"

#include <iostream>
#include <string>
#include <dteFramework/context/dteContext.h>

#include <dteFramework/context/importer/apiImporter.h>
#include <dteFramework/context/exporter/dteExporter.h>

dteContext::dteContext() {
	this->importMap = {
		{"DTE", nullptr},
		{"DATABASE", nullptr},
		{"API", apiImport}
	};
	this->exportMap = {
		{"DTE", dteExport},
		{"DATABASE", nullptr}
	};
}

int dteContext::addImportMap(std::string key, importHandler handler)
{
	this->importMap.emplace(key, handler);
	return ERR_OK;
}

int dteContext::delImportMap(std::string key)
{	
	this->importMap.erase(key);
	return ERR_OK;
}

int dteContext::updateImportMap(std::string key, importHandler handler)
{
	if (this->importMap.count(key) == 0) {
		return ERR_FAIL;
	}
	else {
		delImportMap(key);
		addImportMap(key, handler);
	}
	return ERR_OK;
}

int dteContext::addExportMap(std::string key, exportHandler handler)
{
	this->exportMap.emplace(key, handler);
	return ERR_OK;
}

int dteContext::delExportMap(std::string key)
{
	this->exportMap.erase(key);
	return ERR_OK;
}

int dteContext::updateExportMap(std::string key, exportHandler handler)
{
	if (this->exportMap.count(key) == 0) {
		return ERR_FAIL;
	}
	else {
		delExportMap(key);
		addExportMap(key, handler);
	}
	return ERR_OK;
}

importHandler dteContext::getImportHandler(std::string key)
{
	return this->importMap.find(key)->second;
}

exportHandler dteContext::getExportHandler(std::string key)
{
	return this->exportMap.find(key)->second;
}
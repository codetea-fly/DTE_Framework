#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include <dteFramework/defs.h>
#include <dteFramework/dataStructrue/dte.h>
#include <dteFramework/dataStructrue/dteCollection.h>

/* import操作函数
*/
typedef dteCollection (*importHandler)(std::string path);
typedef int (*exportHandler)(std::string path, dteCollection entity);

class DTEFramework_API dteContext
{
private:
	std::unordered_map<std::string, importHandler> importMap;
	std::unordered_map<std::string, exportHandler> exportMap;

public:
	dteContext();//初始化两个map
	int addImportMap(std::string key, importHandler handler);
	int delImportMap(std::string key);
	int updateImportMap(std::string key, importHandler handler);
	int addExportMap(std::string key, exportHandler handler);
	int delExportMap(std::string key);
	int updateExportMap(std::string key, exportHandler handler);
	importHandler getImportHandler(std::string key);
	exportHandler getExportHandler(std::string key);
};


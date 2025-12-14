#pragma once

#include "include/core/common/OperationResult.h"
#include<string>
#include<unordered_map>

using namespace std;

class ConfigManager 
{
private:

	ConfigManager() = default;
	bool isLoaded = false;
	unordered_map<string, string> settings;

public:
	static ConfigManager& instance();
	OperationResult<void> load(const string& filePath = "config/config.txt");
	OperationResult<string> get(const string& key);
};
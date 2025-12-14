#include "include/helpers/ConfigManager.h"
#include<fstream>
#include<sstream>
#include<iostream>

ConfigManager& ConfigManager::instance()
{
	static ConfigManager instance;
	return instance;
}

OperationResult<void> ConfigManager::load(const string& filePath)
{
	ifstream configFile;
	configFile.open(filePath);
	if (!configFile.is_open())
		return OperationResult<void>::Failure("Unable to open configuration file " + filePath);


	string line;
	while (getline(configFile, line))
	{
		istringstream iss(line);
		if (!line.empty())
		{
			string key, value;
			getline(iss, key, '=');
			getline(iss, value);
			settings[key] = value;
		}
	}
	configFile.close();
	isLoaded = true;
	return OperationResult<void>::Success("Configuration has been loaded");

}

OperationResult<string> ConfigManager::get(const string& key)
{
	if(!isLoaded)
		return OperationResult<string>::Failure("Configuration has not been loaded. Please load the configuration file before accessing keys.");

	if(settings.empty())
		return OperationResult<string>::Failure("Configuration loaded but no settings were found in the file.");

	auto iterator = settings.find(key);
	if (iterator != settings.end())
		return OperationResult<string>::Success(iterator->second);
	
	return OperationResult<string>::Failure("Key not found: " + key);
}
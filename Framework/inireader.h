#pragma once
#include <fstream>
#include <list>
#include <map>
#include <string>

using namespace std;

class INIReader
{
	
public:
	bool LoadIniFile(const string& fileName);
	list<string> GetLoadedSections();
	string GetValueAsString(const string& iniSection, const string& key);
	int GetValueAsInt(const string& iniSection, const string& key);
	float GetValueAsFloat(const string& iniSection, const string& key);
	bool GetValueAsBoolean(const string& iniSection, const string& key);
	char* GetValueAsChar(const string& iniSection, const string& key);
		
protected:
	ifstream m_iniFile;
	list<string> m_sectionNames;
	map<string, string> m_sections;
	
	
private:

};

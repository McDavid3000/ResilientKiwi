#include "inireader.h"

#include <fstream>
#include <iostream>

bool INIReader::LoadIniFile(const string& fileName)
{
	m_iniFile.open(fileName);

	//Check if file was opened
	if (!m_iniFile.is_open())
	{
		return false; //File failed to open.
	}
	else { //File opened
		//Declare variables
		char buffer[192];
		string sectionName = "";
		string keyName = "";
		string value = "";
		
		if (m_iniFile.is_open()) {
			while (m_iniFile.getline(buffer, 128)) {

				//Ignore lines that start with comment characters
				if (buffer[0] != ';' && buffer[0] != '#' && buffer[0] != '\0')
				{

					if (buffer[0] == '[') //Start section
					{
						sectionName = "";
						int charCounter = 1;
						while (buffer[charCounter] != ']' && charCounter < static_cast<int>(std::strlen(buffer)))
						{
							sectionName += buffer[charCounter++];
							
						}
						m_sectionNames.push_back(sectionName);

					}
					else {
						//Get key
						int charCounter = 0;
						while (buffer[charCounter] != '=')
						{
							keyName += buffer[charCounter++];
						}

						//Get value
						while (charCounter < static_cast<int>(std::strlen(buffer)))
						{
							value += buffer[++charCounter];
						}
					}

					//If keyname and value are set, create section
					if (keyName != "" && value != "")
					{
						m_sections.insert_or_assign(sectionName + "|" + keyName, value);
						//Reset key and value
						keyName = "";
						value = "";
					}
				}

			}
			
		}
		m_iniFile.close();
		return true;
	}
}

list<string> INIReader::GetLoadedSections()
{
	return m_sectionNames;
}


string INIReader::GetValueAsString(const string& iniSection, const string& key)
{
	//Check key exists
	string mapKey = iniSection + "|" + key;
	if(m_sections.find(mapKey) == m_sections.end())
	{
		//If no key found
		return "KEY NOT FOUND";
	}
	//Else return value
	return m_sections.at(iniSection+"|"+key);
}

char* INIReader::GetValueAsChar(const string& iniSection, const string& key)
{
	//Check key exists
	string mapKey = iniSection + "|" + key;
	if (m_sections.find(mapKey) == m_sections.end())
	{
		//If no key found
		return "KEY NOT FOUND";
	}
	//Else return value
	return const_cast<char*>(m_sections.at(iniSection + "|" + key).c_str());
}


int INIReader::GetValueAsInt(const string& iniSection, const string& key)
{
	//Check key exists
	string mapKey = iniSection + "|" + key;
	if (m_sections.find(mapKey) == m_sections.end())
	{
		//If no key found
		return 000;
	}
	//Else return value
	return stoi(m_sections.at(iniSection + "|" + key));
}

float INIReader::GetValueAsFloat(const string& iniSection, const string& key)
{
	//Check key exists
	string mapKey = iniSection + "|" + key;
	if (m_sections.find(mapKey) == m_sections.end())
	{
		//If no key found
		return -0.0000001f;
	}
	//Else return value
	return stof(m_sections.at(iniSection + "|" + key));
}

bool INIReader::GetValueAsBoolean(const string& iniSection, const string& key)
{
	//Check key exists
	string mapKey = iniSection + "|" + key;
	if (m_sections.find(mapKey) == m_sections.end())
	{
		//If no key found
		return false;
	}

	//Check if string matches "TRUE" (case insensitive)
	if(_strcmpi(m_sections.at(iniSection + "|" + key).c_str(), "TRUE") == 0)
	{
		return true;
	}
	//Else, check if string matches "False" (case insensitive)
	else if (_strcmpi(m_sections.at(iniSection + "|" + key).c_str(), "FALSE") == 0)
	{
		return true;
	}
	//Else return false (Bad input)
	return false;
}

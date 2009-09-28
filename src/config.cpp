
#include <map>
#include <fstream>
#include "config.h"
#include "CommonStructures.h"
#include "messages.h"

namespace PacGame
{

    namespace Config
    {
        typedef map<string,string>::iterator Iterator;
        map<string,string> _content;

        string Trim(string str)
        {
            size_t startpos = str.find_first_not_of(" ");
            size_t endpos = str.find_last_not_of(" ");
            return str.substr( startpos, endpos-startpos+1 );
        }

        bool ReadConfig(string configFile)
        {
            ifstream file(configFile.c_str());
            if(file.bad()) return false;

            string line;
            string name;
            int posEqual;

            for (int count=0;getline(file,line);count++) {
                if (!line.length()) continue;
                if (line[0] == '#') continue; //commentar symbol
                if (line[0] == ';') continue; //commentar symbol

                posEqual = line.find('=');
                if(posEqual != string::npos)
                {
                    name  = Trim(line.substr(0,posEqual));
                    _content[name] = Trim(line.substr(posEqual+1));
                }
                else
                {
                    Messages::errorMessage("Invalid line " + Functions::toString(count) + " in config file!");
                }
            }

            file.close();
            return true;
        }

        int GetValueInt(string name)
        {
            Iterator it = _content.find(name);
            if(it != _content.end())
                return Functions::strToInt(it->second);
            else
                return 0;
        }

        string GetValueString(string name)
        {
            Iterator it = _content.find(name);
            if(it != _content.end())
                return it->second;
            else
                return NULL;
        }

        bool GetValueBool(string name)
        {
            return GetValueInt(name);
        }

        void SetValueInt(string name, int value)
        {
            _content[name] = Functions::toString(value);
        }

        void SetValueString(string name, string value)
        {
            _content[name] = value;
        }

        void SetValueBool(string name, bool value)
        {
            _content[name] = Functions::toString(value);
        }

        bool SaveConfig(string configFile)
        {
            ofstream file(configFile.c_str());
            if(file.bad()) return false;

            for (Iterator it=_content.begin() ; it != _content.end(); it++)
            {
                file << it->first << "=" << it->second << endl;
            }

            file.close();
            return true;
        }
    }

}

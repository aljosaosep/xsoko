/* 
 * File:   config.h
 * Author: jernej
 *
 * Created on Ponedeljek, 28 september 2009, 17:22
 */

#ifndef _CONFIG_H
#define	_CONFIG_H

#include <string>

using namespace std;

namespace PacGame
{

    namespace Config
    {

        bool ReadConfig(string configFile);
        bool SaveConfig(string configFile);

        int GetValueInt(string name);
        string GetValueString(string name);
        bool GetValueBool(string name);

        void SetValueInt(string name, int value);
        void SetValueString(string name, string value);
        void SetValueBool(string name, bool value);
    }

}

#endif	/* _CONFIG_H */


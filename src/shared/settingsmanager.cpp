/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "precomp.h"
#include "settingsmanager.h"
#include "utils.h"
#include "type.h"

Settings::SettingsMap Settings::readFromFile(std::ifstream && file)
{
    Settings::SettingsMap map;
    if (file)
    {
        while (!file.eof())
        {
            std::string line;
            std::getline(file, line);
            auto vk = split(line, "=");
            if (vk.size() != 2) continue;
            std::string key = vk[0], value = vk[1];
            trim(key);
            strtolower(key);
            trim(value);
            map[key] = string2type(value);
        }
    }
    return map;
}

void Settings::writeToFile(std::ofstream && file, const Settings::SettingsMap& settings,bool minimal)
{
    for (const auto& p : settings)
    {
        if (minimal)
            file << p.first << "=" << type2string(p.second) << std::endl;
        else
            file << p.first << " = " << type2string(p.second) << std::endl;
    }
}
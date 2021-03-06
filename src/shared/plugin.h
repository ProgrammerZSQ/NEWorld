/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <string>
using std::string;
#include <utility>
#include <boost/dll/shared_library.hpp>

#include "common.h"
#include "vec3.h"
#include "blockdata.h"

struct PluginData
{
    char* pluginName;
    char* authorName;
    char* internalName;
};

// Single plugin
class Plugin
{
public:
    explicit Plugin(const string& filename) : m_status(-1)
    {
        loadFrom(filename);
    }

    Plugin(Plugin&& rhs) : m_lib(std::move(rhs.m_lib)), m_data(rhs.m_data), m_status(rhs.m_status)
    {
        rhs.m_data = nullptr;
        rhs.m_status = -1;
    }

    Plugin(const Plugin&) = delete;

    Plugin& operator= (const Plugin&) = delete;

    ~Plugin()
    {
        unload();
    }

    // Get plugin data
    const PluginData& getData() const
    {
        return *m_data;
    }

    // Get load status
    int getStatus() const
    {
        return m_status;
    }

    // Is loaded
    bool isLoaded() const
    {
        return m_status == 0;
    }

    // Load plugin, return 0 for success
    int loadFrom(const string& filename);
    // Unload plugin
    void unload();

private:
    // Plugin DLL
    boost::dll::shared_library m_lib;
    // Plugin Data
    const PluginData* m_data;
    // Load status
    int m_status = -1;
};

#endif // !PLUGIN_H_

#include "Config.hpp"
#include "CMD/Logger.hpp"
#include <fstream>
#include <sstream>

std::unordered_map<std::string, std::string> Config::m_data;

bool Config::Load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
       // Logger::error("Failed to load config: %s", filename.c_str());
        return false;
    }

    m_data.clear();
    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter = line.find('=');
        if (delimiter != std::string::npos) {
            std::string key = line.substr(0, delimiter);
            std::string value = line.substr(delimiter + 1);
            m_data[key] = value;
        }
    }

    file.close();
    //Logger::log("Config loaded: %s", filename.c_str());
    return true;
}

bool Config::Save(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        //Logger::error("Failed to save config: %s", filename.c_str());
        return false;
    }

    for (const auto& [key, value] : m_data) {
        file << key << "=" << value << "\n";
    }

    file.close();
    //Logger::log("Config saved: %s", filename.c_str());
    return true;
}

void Config::SetValue(const std::string& key, const std::string& value) {
    m_data[key] = value;
}

std::string Config::GetValue(const std::string& key, const std::string& defaultValue) {
    auto it = m_data.find(key);
    return it != m_data.end() ? it->second : defaultValue;
}

void Config::SetBool(const std::string& key, bool value) {
    m_data[key] = value ? "true" : "false";
}

bool Config::GetBool(const std::string& key, bool defaultValue) {
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        return it->second == "true";
    }
    return defaultValue;
}

void Config::SetInt(const std::string& key, int value) {
    m_data[key] = std::to_string(value);
}

int Config::GetInt(const std::string& key, int defaultValue) {
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        try {
            return std::stoi(it->second);
        }
        catch (...) {
            return defaultValue;
        }
    }
    return defaultValue;
}

void Config::SetFloat(const std::string& key, float value) {
    m_data[key] = std::to_string(value);
}

float Config::GetFloat(const std::string& key, float defaultValue) {
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        try {
            return std::stof(it->second);
        }
        catch (...) {
            return defaultValue;
        }
    }
    return defaultValue;
}
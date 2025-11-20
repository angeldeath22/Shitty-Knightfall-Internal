#pragma once
#include <string>
#include <unordered_map>

class Config {
public:
    static bool Load(const std::string& filename);
    static bool Save(const std::string& filename);

    static void SetValue(const std::string& key, const std::string& value);
    static std::string GetValue(const std::string& key, const std::string& defaultValue = "");

    static void SetBool(const std::string& key, bool value);
    static bool GetBool(const std::string& key, bool defaultValue = false);

    static void SetInt(const std::string& key, int value);
    static int GetInt(const std::string& key, int defaultValue = 0);

    static void SetFloat(const std::string& key, float value);
    static float GetFloat(const std::string& key, float defaultValue = 0.0f);

private:
    static std::unordered_map<std::string, std::string> m_data;
};
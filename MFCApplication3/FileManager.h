#pragma once
#include <string>

class FileManager {
public:
    static std::string LoadText(const std::string& path);
    static void SaveText(const std::string& path, const std::string& text);
};

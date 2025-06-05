#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string FileManager::LoadText(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Не удалось открыть файл для чтения");

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

void FileManager::SaveText(const std::string& path, const std::string& text) {
    std::ofstream file(path);
    if (!file) throw std::runtime_error("Не удалось открыть файл для записи");

    file << text;
}

#include "SynonymProcessor.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>

void SynonymProcessor::LoadSynonyms(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) throw std::runtime_error("Не удалось открыть файл синонимов");

    std::string line;
    while (std::getline(file, line)) {
        auto colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;

        std::string key = line.substr(0, colonPos);
        std::string synonymsStr = line.substr(colonPos + 1);
        std::istringstream ss(synonymsStr);
        std::string synonym;

        while (std::getline(ss, synonym, ',')) {
            synonym.erase(0, synonym.find_first_not_of(" \t"));
            synonymMap[key].push_back(synonym);
        }
    }

    Logger::Log("INFO", "Синонимы успешно загружены");
}

std::string SynonymProcessor::ReplaceWords(const std::string& text) {
    std::istringstream iss(text);
    std::ostringstream oss;
    std::string word;
    std::random_device rd;
    std::mt19937 gen(rd());

    while (iss >> word) {
        std::string stripped = word;
        stripped.erase(std::remove_if(stripped.begin(), stripped.end(),
            [](char c) { return ispunct(c); }), stripped.end());

        auto it = synonymMap.find(stripped);
        if (it != synonymMap.end() && !it->second.empty()) {
            std::uniform_int_distribution<> dis(0, (int)it->second.size() - 1);
            std::string replacement = it->second[dis(gen)];
            Logger::Log("INFO", "Слово '" + stripped + "' заменено на '" + replacement + "'");
            oss << replacement << " ";
        }
        else {
            oss << word << " ";
        }
    }

    return oss.str();
}

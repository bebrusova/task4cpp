#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class SynonymProcessor {
public:
    void LoadSynonyms(const std::string& filePath);
    std::string ReplaceWords(const std::string& text);
private:
    std::unordered_map<std::string, std::vector<std::string>> synonymMap;
};

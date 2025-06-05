#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger
{
public:
    // Логирование сообщения с уровнем важности
    static void Log(const std::string& level, const std::string& message);

private:
    static std::mutex logMutex;          // Для потокобезопасности
    static std::ofstream logFile;        // Файловый поток
    static void Init();                  // Инициализация файла
};

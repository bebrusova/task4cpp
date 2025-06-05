#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger
{
public:
    // ����������� ��������� � ������� ��������
    static void Log(const std::string& level, const std::string& message);

private:
    static std::mutex logMutex;          // ��� ������������������
    static std::ofstream logFile;        // �������� �����
    static void Init();                  // ������������� �����
};

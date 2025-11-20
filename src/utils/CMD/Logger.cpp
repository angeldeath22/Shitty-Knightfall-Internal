#include "Logger.hpp"
#include <chrono>
#include <fstream>
std::mutex logMutex;

void Logger::INIT_CMD() {


    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    SetConsoleTitleA("IL2CPP Console");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hConsole, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, dwMode);
    }
    std::lock_guard<std::mutex> guard(logMutex);

    std::filesystem::path logPath("log.txt");
    std::filesystem::path oldLogPath("log_old.txt");

    if (std::filesystem::exists(oldLogPath)) {
        std::filesystem::remove(oldLogPath);
    }

    if (std::filesystem::exists(logPath)) {
        std::filesystem::rename(logPath, oldLogPath);
    }
}

void Logger::write_log(const std::string& prefix, const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);


    std::string formatted = "[ " + prefix + " ] " + message;


    std::cout << formatted << std::endl;


    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << formatted << std::endl;
    }
}

void Logger::debug(const std::string& message) {
#ifndef PUBLIC
    Logger::write_log(">", message);
#endif
}

void Logger::success(const std::string& message) {
#ifndef PUBLIC
    Logger::write_log("+", message);
#endif
}

void Logger::error(const std::string& message) {
#ifndef PUBLIC
    Logger::write_log("-", message);
#endif
}

void Logger::log(const std::string& message) {
#ifndef PUBLIC
    Logger::write_log("*", message);
#endif
}
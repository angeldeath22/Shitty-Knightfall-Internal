#include "System.hpp"
#include "../utils/CMD/Logger.hpp"

bool System::Initialize() {
    Logger::log("Initializing System...");
    return true;
}

void System::Shutdown() {
    Logger::log("Shutting down System...");
}
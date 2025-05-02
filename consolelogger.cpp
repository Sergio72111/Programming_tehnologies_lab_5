#include "consolelogger.h"
#include <iostream>

void ConsoleLogger::Log(const std::string& message) {
    std::cout << "[LOG] " << message << std::endl;
}

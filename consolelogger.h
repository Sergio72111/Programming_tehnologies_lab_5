#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "ilogger.h"

class ConsoleLogger : public ILogger {
public:
    void Log(const std::string& message) override;
};

#endif // CONSOLELOGGER_H

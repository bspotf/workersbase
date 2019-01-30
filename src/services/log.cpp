#include "log.h"
#include <iostream>
#include <fstream>

std::shared_ptr<Log> Log::getInstance()
{
    static Log instance;
    return std::make_shared<Log>(instance);
}

Log::Log()
{
    this->debugLevel = DEBUG_LEVEL_ERROR;
}

void Log::error(const std::string& message)
{
    if (debugLevel >= DEBUG_LEVEL_ERROR) {
        writeMessage(DEBUG_LEVEL_ERROR, message);
    }
}

void Log::warning(const std::string& message)
{
    if (debugLevel >= DEBUG_LEVEL_WARNING) {
        writeMessage(DEBUG_LEVEL_WARNING, message);
    }
}

void Log::message(const std::string& message)
{
    if (debugLevel >= DEBUG_LEVEL_MESSAGE) {
        writeMessage(DEBUG_LEVEL_MESSAGE, message);
    }
}


void Log::writeMessage(int debugLevel, const std::string& message)
{
    std::string prefix;
    switch (debugLevel) {
    case DEBUG_LEVEL_ERROR:
        prefix = "[ERROR] ";
        break;
    case DEBUG_LEVEL_WARNING:
        prefix = "[WARNING] ";
        break;
    case DEBUG_LEVEL_MESSAGE:
        prefix = "[MESSAGE] ";
    default:
        return;
    }
    std::cerr << prefix + message << std::endl;
    appendToFile(message);
}

void Log::appendToFile(const std::string& message)
{
    std::ofstream outStream;
    outStream.open("log.txt", std::ios::app);
    if (outStream)
    {
        outStream << message << std::endl;
        outStream.close();
    }
}

void Log::setDebugLevel(DebugLevel level)
{
    this->debugLevel = level;
}

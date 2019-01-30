#include "log.h"
#include <iostream>
#include <fstream>

Log::Log()
{
    this->debugLevel = DEBUG_LEVEL_ERROR;
}

void Log::writeError(const std::string& message)
{
    if (debugLevel >= DEBUG_LEVEL_ERROR) {
        std::string err = "[ERROR] " + message;
        std::cerr << err << std::endl;
        appendToFile(message);
    }
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

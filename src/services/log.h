#ifndef LOG_H
#define LOG_H

#include <string>

class Log
{
public:
    Log();
    void writeError(const std::string& message);

    enum DebugLevel
    {
        DEBUG_LEVEL_DISABLED = 0,
        DEBUG_LEVEL_ERROR = 1,
        DEBUG_LEVEL_WARNING = 2,
        DEBUG_LEVEL_MESSAGE = 3,
    };
    enum MessageType
    {
        MESSAGE_INFO,
        MESSAGE_WARNING,
        MESSAGE_ERROR,
    };
    static void createInstance();
    void setDebugLevel(DebugLevel level);
protected:
    void appendToFile(const std::string& message);
private:
    DebugLevel debugLevel;
};

#endif // LOG_H

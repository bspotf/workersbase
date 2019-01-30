#ifndef LOG_H
#define LOG_H

#include <string>
#include <memory>

class Log
{
public:

    static std::shared_ptr<Log> getInstance();

    void error(const std::string& message);
    void warning(const std::string& message);
    void message(const std::string& message);
    void writeMessage(int debugLevel, const std::string& message);

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
    void setDebugLevel(DebugLevel level);
protected:
    Log();
    void appendToFile(const std::string& message);
private:
    DebugLevel debugLevel;
};

#endif // LOG_H

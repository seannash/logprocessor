#pragma once

#include <string_view>

namespace monitor {

// Protocol class for all Loggers
class Logger {
public:
    virtual ~Logger();
    
    // Writes a log msg prefixed by the time
    virtual void log(unsigned long time, std::string_view msg) = 0;
};

} // namespace monitor
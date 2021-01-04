#pragma once

#include <mutex>
#include <sstream>
#include <string_view>

#include <monitor_logger.h>

namespace monitor {

// Logs the records to a string. Useful for testing.
class StringLogger: public Logger {
public:
    StringLogger();
    void log(unsigned long tp, std::string_view msg) override;

    std::string getLog();
private:
    std::mutex d_mutex;
    std::stringstream d_buffer;
};

} // namespace monitor
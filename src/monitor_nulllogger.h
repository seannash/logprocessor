#pragma once

#include <string_view>

#include <monitor_logger.h>

namespace monitor {

// Useful logger for testing
class NullLogger: public Logger {
public:
    NullLogger();
    void log(unsigned long tp, std::string_view msg) override;
};

} // namespace monitor
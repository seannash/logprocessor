#pragma once

#include <mutex>
#include <string_view>

#include <monitor_logger.h>

namespace monitor {

class ConsoleLogger: public Logger {
public:
    ConsoleLogger();
    void log(unsigned long tp, std::string_view msg) override;
private:
    std::mutex d_mutex;
};

} // namespace monitor
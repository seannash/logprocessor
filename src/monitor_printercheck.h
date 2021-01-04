#pragma once

#include <memory>

#include <monitor_check.h>
#include <monitor_logger.h>
#include <monitor_logrecord.h>

namespace monitor {

// Useful check for testing. Prints out the logs to standard out.
class PrinterCheck: public Check {
public:
    PrinterCheck(std::shared_ptr<Logger>& logger);
    void operator()(const LogRecord& rec) override;
private:
    std::shared_ptr<Logger> d_logger;
};

} // namespace monitor
#pragma once

#include <chrono>

#include <monitor_logger.h>
#include <monitor_logrecord.h>

namespace monitor {

// Protocol class for all classes tracking statistics
class Stat {
public:
    virtual ~Stat();

    // Data from this record will be considered for calculations
    virtual void addTo(const LogRecord& rec) = 0;
    
    // The data from this record should be removed from the calculations
    virtual void removeFrom(const LogRecord& rec) = 0;

    // Generate a log
    virtual void log(unsigned long tp, Logger& logger) = 0;;
};

} // namespace monitor
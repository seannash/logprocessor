#pragma once

#include <chrono>

#include <monitor_logrecord.h>

namespace monitor {

class Check {
public:
    virtual ~Check();

    // The log record will be checked. Some checks can be stateful
    virtual void operator()(const LogRecord& rec) = 0;
};

} // namespace monitor
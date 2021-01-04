#pragma once

#include <memory>
#include <map>
#include <mutex>

#include <monitor_check.h>
#include <monitor_logger.h>
#include <monitor_logrecord.h>
#include <monitor_trafficcheck.h>

namespace monitor {

class TrafficCheck: public Check {
public:
    // TODO The logger is set at construction time but should be set by the Monitor
    TrafficCheck(std::shared_ptr<Logger> logger, int averageTraffic, int span = 120);

    // Uses the log record and keeps state to see traffic level;
    void operator()(const LogRecord& rec) override;

private:
    // Used to check if a time point is within the span of stored data
    bool within_span(std::chrono::seconds point);

    std::shared_ptr<Logger> d_logger; // The output logger
    int d_averageTaffic;              // The average traffic to look for
    bool d_highState;                 // Flag if state is high traffic
    std::chrono::seconds d_span;      // The span of time in seconds for calculations
    std::chrono::seconds d_curTime; // The latest time seen

    unsigned long d_count;                         // The number of logs logged
    std::map<std::chrono::seconds, int> d_traffic; // A map of a time point to number of logs
};

} // namespace monitor

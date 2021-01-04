#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <regex>
#include <string_view>
#include <vector>

#include <monitor_check.h>
#include <monitor_logrecord.h>
#include <monitor_logparser.h>
#include <monitor_stat.h>
#include <monitor_storage.h>

namespace monitor {

class GenericMonitor {
public:
    GenericMonitor();
    GenericMonitor(std::chrono::seconds spanStorage, std::shared_ptr<Logger> logger);

    // Used to add a check to the monitor
    void addCheck(std::unique_ptr<Check> check);
    // Used to add a Statistic to the monitor
    void addStat(std::unique_ptr<Stat> stat);

    // Process a file, return value is number of lines processed
    long process(std::istream& is);
    // Process a LogRecord, return value is number of lines processed
    long process(const LogRecord& line);
    // Process a string, return value is number of lines processed
    long process(const std::string& line);

private:
    // Used to remove the log record from all stat objects
    void removeFromStats(const LogRecord& rec);
    
    // Add the log record to all stat objects
    void addToStats(const LogRecord& rec);
    
    // Perform checks passing it the record rec
    void doChecks(const LogRecord& rec);
    
    // Maintain the storage
    // 1. Keep the storage limited by the span
    // 2. When evicting records, remove them from the stat objects
    // 3. Add the new record
    void maintainStorage(const LogRecord& rec);

    // Have the stat objects log for time point
    void log(unsigned long tp);

    // The interval in seconds of when statistics are written
    int d_statInterval;
    // The logger for the stats objects
    std::shared_ptr<Logger> d_logger;
    // The Storage object for all logs currently in use by stat objects.
    Storage d_storage;
    // A container of all the added check objects
    std::vector<std::unique_ptr<Check>> d_checks;
    // A container of all added stat objects
    std::vector<std::unique_ptr<Stat>> d_stats;
    // Keeps track of at what the next time is to write statistics
    std::optional<unsigned long> d_nextLogTime;
    // Lines processed. This rolls over. Useful for seeing the program did something.
    unsigned long d_lines = 0;
    // The log parser that does string->LogRecord
    LogParser d_parser;
};

} // namespace monitor
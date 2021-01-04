#pragma once

#include <chrono>
#include <map>
#include <regex>
#include <string_view>

#include <monitor_logrecord.h>

namespace monitor {

class Storage {
public:
    // This is the type of the datastructure used for storeing data
    // A multimap was used which is a map that can hold multiple values
    // for the same key instead of a queue since the logs in the sample
    // were not fully ordered. Some could be a couple seconds late.
    // There is no lookahead, so if some are late at the 10 second mark
    // They could be missed by the statistics
    // TODO Implement lookahead.
    using storage_t = std::multimap<std::chrono::seconds, LogRecord>;
    // iter_t type is for an iterator pair for less typing
    using iters_t = std::pair<storage_t::iterator, storage_t::iterator>;

    Storage(std::chrono::seconds span);
    std::size_t size() const;

    // Adds a record to storage
    void add(LogRecord rec);

    // Maintains storage by evicting records out of the span
    void maintain(std::chrono::seconds cur);

    // Return an iterator pair of records outside the span
    // This is used by GenericMonitor to remove the records from
    // the stats objects.
    Storage::iters_t find_out_of_span(std::chrono::seconds start);
    
private:
    std::chrono::seconds d_span; // Number of seconds to keep in storage
    std::multimap<std::chrono::seconds, LogRecord> d_storage;
};

} // namespace monitor
#pragma once

#include <map>
#include <queue>
#include <set>

#include <monitor_logger.h>
#include <monitor_logrecord.h>
#include <monitor_stat.h>

namespace monitor {

// Keeps track of the 5 top sites
class TopSitesStat: public Stat {
public:
    TopSitesStat();
    void addTo(const LogRecord& rec) override;
    void removeFrom(const LogRecord& rec) override;
    void log(unsigned long tp, Logger& logger) override;
private:
    // Type is used in the set for order the sites by hits
    using qrec_t = std::pair<long, std::string>;

    // Keeps unordered the sites by hit counts
    std::map<std::string, long> d_counts;
    
    // Keeps ordered the sites with hit count
    std::set<qrec_t> d_top;
};

} // namespace monitor
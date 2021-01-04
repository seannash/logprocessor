#include <monitor_genericmonitor.h>

#include <iostream>
#include <string>



#include <chrono>

#include <cassert>

namespace monitor {

GenericMonitor::GenericMonitor(std::chrono::seconds storageSpan, std::shared_ptr<Logger> logger)
: d_statInterval(10)
, d_logger(logger)
, d_storage(storageSpan)
, d_checks()
, d_stats()
, d_nextLogTime()
, d_lines()
, d_parser()
{}

void GenericMonitor::addCheck(std::unique_ptr<Check> check)
{
    d_checks.push_back(std::move(check));
}

void GenericMonitor::addStat(std::unique_ptr<Stat> stat)
{
    d_stats.push_back(std::move(stat));
}

void GenericMonitor::log(unsigned long tp)
{
    for (auto& stat: d_stats)
    {
        stat->log(tp, *d_logger);
    }
}

void GenericMonitor::removeFromStats(const LogRecord& rec)
{
    for (auto& stat: d_stats)
    {
        stat->addTo(rec);
    }
}

void GenericMonitor::addToStats(const LogRecord& rec)
{
    for (auto& stat: d_stats)
    {
        stat->addTo(rec);
    }
}

void GenericMonitor::doChecks(const LogRecord& rec)
{
    for (auto& check: d_checks) {
        (*check)(rec);
    }
}

void GenericMonitor::maintainStorage(const LogRecord& rec)
{
    std::chrono::seconds cur_point(rec.date);

    if (rec.date>*d_nextLogTime) {
        log(*d_nextLogTime);
        d_nextLogTime = rec.date+d_statInterval-(rec.date-*d_nextLogTime)%d_statInterval;
    }

    auto [start0, end0] = d_storage.find_out_of_span(cur_point);
    for (auto iter=start0; iter!=end0; ++iter) {
        removeFromStats(iter->second);
    }
    d_storage.add(rec);  // Storage remove out of span records  when a new recordc is added
}

long GenericMonitor::process(std::istream& input_stream)
{
    std::string line{};
    while(std::getline(input_stream, line))
    {
        LogRecord rec;
        int parse_valid = d_parser.parse(line, &rec);
        if (parse_valid!=0) {
            continue;
        }
        
        process(rec);
    }
    log(*d_nextLogTime);
    return d_lines;
}

long GenericMonitor::process(const std::string& line)
{
    LogRecord rec;
    int parse_valid = d_parser.parse(line, &rec);
    if (parse_valid!=0) {
        return d_lines;
    }
        
    return process(rec);
}

long GenericMonitor::process(const LogRecord& rec)
{
    if (d_lines==std::numeric_limits<long>::max()) {
        d_lines == 0;
    }
    d_lines++;
    if (!d_nextLogTime) {
        d_nextLogTime = rec.date+d_statInterval;
    }
    maintainStorage(rec);
    addToStats(rec);
    doChecks(rec); 
    return d_lines;
}

} // namespace monitor
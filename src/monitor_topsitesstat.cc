#include <monitor_topsitesstat.h>

#include <sstream>

#include <iostream>

namespace monitor {

TopSitesStat::TopSitesStat()
: d_counts()
, d_top()
{}

void TopSitesStat::addTo(const LogRecord& rec)
{
    std::string section = get_section(rec);
    if (section.empty())
        return; // No section so record is ignored
    d_counts[section]+=1; // If section is not found in map, C++ creates it with default value of int which is 0.
    long cnt = d_counts[section];
    if (cnt>1) // Remove old data from d_top
        d_top.erase({cnt-1, section});
    d_top.insert({cnt, section});
}

void TopSitesStat::removeFrom(const LogRecord& rec)
{
    std::string section = get_section(rec);
    int old_cnt = d_counts[section];
    if (old_cnt==0)
        return;
    if (old_cnt>1)
        d_counts[section]-=1;
    else
        d_counts.erase(section);
    d_top.erase({old_cnt, section});
    if (old_cnt>1)
        d_top.insert({old_cnt-1, section});
}

void TopSitesStat::log(unsigned long tp, Logger& logger)
{
    auto iter = std::rbegin(d_top);
    std::stringstream ss;
    ss << "Top sections:";
    // This will take the last 5
    // TODO: How should ties be broken? Currently theu are done by alphabeticaly sorted backwards.
    for (int i=0; i<5 && iter!=std::rend(d_top); ++i, ++iter)
    {
        ss << " " << iter->second;
    }
    logger.log(tp, ss.str());
}

} // namespace monitor
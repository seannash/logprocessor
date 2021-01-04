#include <monitor_trafficcheck.h>

#include <sstream>

#include <iostream>

namespace monitor {

TrafficCheck::TrafficCheck(std::shared_ptr<Logger> logger, int averageTraffic, int span)
: d_logger(logger)
, d_averageTaffic(averageTraffic)
, d_highState(false)
, d_span(std::chrono::seconds(span))
, d_curTime()
, d_count()
, d_traffic()
{}

bool TrafficCheck::within_span(std::chrono::seconds point)
{
    std::chrono::seconds cutoff = d_curTime-d_span;
    return point > cutoff;
}

void TrafficCheck::operator()(const LogRecord& rec)
{
    std::chrono::seconds point(rec.date);
    d_curTime = std::max(d_curTime, point);
    if (!within_span(point))
        return;

    d_traffic[point]+=1;
    d_count+=1;
    
    std::optional<std::chrono::seconds> highStateEndTime {};
    std::chrono::seconds cutoff = d_curTime-d_span;
    if (d_highState) {
        long remove = d_count - d_span.count()*d_averageTaffic;
        auto iter = d_traffic.begin();
        auto last = iter;
        while (iter!=d_traffic.end() && iter->first<cutoff && remove>0) {
            remove -= iter->second;
            last = iter;
            iter = std::next(iter);
        }
        if (remove<=0) {
            highStateEndTime = last->first+d_span;
        }
    }
    auto iter = d_traffic.upper_bound(cutoff);
    if (iter!=d_traffic.end()) {
        for (auto j= d_traffic.begin(); j!=iter; ++j)
            d_count-=iter->second;
        d_traffic.erase(d_traffic.begin(), iter);
    }

    double averageTraffic = (double)d_count/d_span.count();
    if (!d_highState && averageTraffic>d_averageTaffic) {
        d_highState = true;
        std::stringstream ss;
        ss << "High traffic generate alert - hits " << d_count << " at " << d_curTime.count();
        d_logger->log(d_curTime.count(), ss.str()); 
    } else if (d_highState && averageTraffic<d_averageTaffic) {
        d_highState = false;
        std::stringstream ss;
        auto endTime = highStateEndTime ? *highStateEndTime : d_curTime;
        ss << "Normal Traffic Resumed";
        d_logger->log(endTime.count(), ss.str());
    }
}

} // namespace monitor
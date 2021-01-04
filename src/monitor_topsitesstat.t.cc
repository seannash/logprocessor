#include <monitor_topsitesstat.h>

#include <catch.hpp>

#include <monitor_logger.h>
#include <monitor_stringlogger.h>

#include <iostream>
#include <sstream>


namespace monitor {

namespace {

LogRecord make_record(long time, std::string section)
{   // TODO Having a builder for LogRecord would be better
    std::stringstream ss;
    ss << "GET " << " /" << section << "/opther blah";
    LogRecord rec;
    rec.remoteHost="A";
    rec.rfc931="B";
    rec.authuser="C";
    rec.date=time;
    rec.request=ss.str();
    rec.status=200;
    rec.bytes=1;
    return rec;
}

} // namespace

TEST_CASE()
{
    TopSitesStat stat;
}

TEST_CASE()
{
    std::vector<std::string> sections { "A0", "A1", "B0", "B1", "B2", "B3", "B4"};
    const int N = sections.size();
    TopSitesStat stat;
    for (int i=0; i<6; ++i) {
        std::string& section = sections[ i%N ];
        stat.addTo(make_record(i, section));
    }
    StringLogger logger;
    stat.log(0, logger);
    auto logstr = logger.getLog();
    REQUIRE(logstr == "0: Top sections: /B3 /B2 /B1 /B0 /A1\n");
    stat.removeFrom(make_record(7,sections[4]));
    stat.log(0, logger);
    logstr = logger.getLog();
    REQUIRE(logstr == "0: Top sections: /B3 /B1 /B0 /A1 /A0\n");
}


TEST_CASE()
{
    std::vector<std::string> sections { "A0", "A1", "B0", "B1", "B2", "B3", "B4"};
    const int N = sections.size();
    TopSitesStat stat;
    stat.addTo(make_record(1, "A"));
    stat.addTo(make_record(1, "B"));
    StringLogger logger;
    stat.log(0, logger);
    auto logstr = logger.getLog();
    REQUIRE(logstr == "0: Top sections: /B /A\n");
    stat.removeFrom(make_record(1, "A"));
    stat.log(0,logger);
    logstr = logger.getLog();
    REQUIRE(logstr == "0: Top sections: /B\n");
}

} // monitor
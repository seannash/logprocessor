#include <monitor_trafficcheck.h>

#include <catch.hpp>

#include <monitor_logger.h>
#include <iostream>

#include <monitor_nulllogger.h>
#include <monitor_stringlogger.h>

namespace monitor {

TEST_CASE("Create")
{
    std::shared_ptr<Logger> logger = std::make_shared<NullLogger>();
    TrafficCheck check0(logger,1);
    std::unique_ptr<Check> check1 = std::make_unique<TrafficCheck>(logger,1);
}

namespace {
LogRecord make_record(long time)
{   // TODO Having a builder for LogRecord would be better
    LogRecord rec;
    rec.remoteHost="A";
    rec.rfc931="B";
    rec.authuser="C";
    rec.date=time;
    rec.request="D";
    rec.status=200;
    rec.bytes=1;
    return rec;
}
} // namespace


TEST_CASE()
{
    
    std::shared_ptr<Logger> logger = std::make_shared<StringLogger>();
    StringLogger* stringLogger = (StringLogger*) logger.get();
    TrafficCheck check(logger,10);
    std::string lines;
    for (int i=0;i<601; ++i)
        check(make_record(0));
    REQUIRE(stringLogger->getLog()=="");
    for (int i=0;i<601; ++i)
        check(make_record(1));
    // TODO Make checking the logs more inexact, so to be less brittle
    REQUIRE(stringLogger->getLog()=="1: High traffic generate alert - hits 1201 at 1\n");
    check(make_record(120));
    REQUIRE(stringLogger->getLog()=="120: Normal Traffic Resumed\n");
    
}

} // monitor
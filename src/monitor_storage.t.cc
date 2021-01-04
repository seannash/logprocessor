#include <monitor_storage.h>

#include <catch.hpp>

#include <iostream>

namespace monitor {

namespace {

LogRecord make_record(long time)
{
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
    Storage gm0();
    Storage gm1(std::chrono::seconds(150));
}

TEST_CASE()
{
    const std::chrono::seconds span(1);
    Storage gm(span);
    gm.add( make_record(1));
    REQUIRE(gm.size()==1);
    gm.add( make_record(1));
    REQUIRE(gm.size()==2);
    gm.add(make_record(3));
    REQUIRE(gm.size()==1);
}

TEST_CASE()
{
    const std::chrono::seconds span(5);
    Storage gm(span);
    for (int i=0; i<=10; ++i)
        gm.add( make_record(i));
    REQUIRE(gm.size()==6);
}

TEST_CASE()
{
    const std::chrono::seconds span(100);
    Storage gm(span);
    for (int i=0; i<=10; ++i)
        gm.add( make_record(i));
    gm.maintain(span+std::chrono::seconds(5));
    REQUIRE(gm.size()==6);
}

} // monitor
#include <monitor_logparser.h>

#include <catch.hpp>

#include <regex>
#include <iostream>

namespace monitor {

TEST_CASE()
{
    std::string line =   R"|("10.0.0.1","-","apache",1549574332,"GET /api/user HTTP/1.0",200,1234)|";
    LogRecord rec {};
    LogParser parser;
    int rc = parser.parse(line, &rec);
    REQUIRE(rc==0);
    REQUIRE(rec.remoteHost=="10.0.0.1");
    REQUIRE(rec.rfc931 == "-");
    REQUIRE(rec.authuser == "apache");
    REQUIRE(rec.date== 1549574332);
    REQUIRE(rec.request == "GET /api/user HTTP/1.0");
    REQUIRE(rec.status == 200);
    REQUIRE(rec.bytes == 1234);
}

} // monitor
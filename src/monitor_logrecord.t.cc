#include <monitor_logrecord.h>

#include <catch.hpp>

namespace monitor {

TEST_CASE()
{
    LogRecord rec;
}

TEST_CASE()
{
    LogRecord rec;
    rec.request="GET /api/bill";
    auto section = get_section(rec);
    REQUIRE(section == "/api");
}

} // monitor
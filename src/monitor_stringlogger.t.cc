#include <monitor_stringlogger.h>

#include <catch.hpp>

namespace monitor {

TEST_CASE()
{
    StringLogger logger;
    logger.log(0, "Hi there");
}

} // monitor
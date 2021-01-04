#include <monitor_nulllogger.h>

#include <catch.hpp>

namespace monitor {

TEST_CASE()
{
    NullLogger logger;
    logger.log(0,"Hi there from unit");
}

} // monitor
#include <monitor_consolelogger.h>

#include <catch.hpp>

namespace monitor {

TEST_CASE()
{
    ConsoleLogger logger;
    logger.log(0, "Hi there from unit");
}

} // monitor
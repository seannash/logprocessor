#include <monitor_logger.h>

#include <catch.hpp>

namespace monitor {

class SubLog: public Logger
{
public:
    void log(unsigned long x, std::string_view msg) override
    {}
};

TEST_CASE()
{
    // This test that the abstract class can be built. Some issues like missing a
    // deconstructor when virtual will fail linkage.
    SubLog logger;
    logger.log(0, "Hi");
}

} // monitor
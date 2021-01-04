#include <monitor_printercheck.h>

#include <monitor_nulllogger.h>

#include <catch.hpp>

namespace monitor {


TEST_CASE()
{
    std::shared_ptr<Logger> logger =  std::make_shared<NullLogger>();
    PrinterCheck printerCheck0(logger);
}

} // monitor
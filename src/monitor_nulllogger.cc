#include <monitor_nulllogger.h>

#include <iostream>

namespace monitor {

NullLogger::NullLogger()
{}

void NullLogger::log(unsigned long tp, std::string_view msg)
{
}

} // namespace monitor
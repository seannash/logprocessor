#include <monitor_consolelogger.h>

#include <iostream>

namespace monitor {

ConsoleLogger::ConsoleLogger()
: d_mutex()
{}

void ConsoleLogger::log(unsigned long tp, std::string_view msg)
{
    std::scoped_lock lg(d_mutex);
    std::cout << tp << ": " << msg << '\n';
}

} // namespace monitor
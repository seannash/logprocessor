#include <monitor_stringlogger.h>

#include <iostream>

namespace monitor {

StringLogger::StringLogger()
: d_mutex(), d_buffer()
{}

void StringLogger::log(unsigned long tp, std::string_view msg)
{
    std::scoped_lock lg(d_mutex);
    d_buffer << tp << ": " << msg << '\n';
}

std::string StringLogger::getLog()
{
    std::string log = d_buffer.str();
    d_buffer.clear();
    d_buffer.str("");
    return log;
}

} // namespace monitor
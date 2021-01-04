#pragma once

#include <ostream>
#include <string>

namespace monitor {

struct LogRecord
{
    std::string unparsed;
    std::string remoteHost;
    std::string rfc931;
    std::string authuser;
    unsigned long date;
    std::string request;
    int status;
    long bytes;
};

std::string get_section(const LogRecord& rec);

std::ostream& operator<<(std::ostream& os, const LogRecord& rec);

} // namespace monitor
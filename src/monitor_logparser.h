#pragma once

#include <regex>
#include <string_view>

#include <monitor_logrecord.h>

namespace monitor {

class LogParser {
public:
    LogParser();
    int parse(const std::string& line, LogRecord* record);
private:
    std::regex d_expr;
};

} // namespace monitor
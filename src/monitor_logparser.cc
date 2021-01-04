#include <monitor_logparser.h>

#include <regex>
#include <stdexcept>
#include <string>

namespace monitor {

namespace {
const char* LINE_FORMAT =  R"|("([\d\.]*)","(.*)","(.*)",(\d*),"(.*)",(\d*),(\d*))|";
} // namespace

LogParser::LogParser()
: d_expr(LINE_FORMAT)
{}

int LogParser::parse(const std::string&  line, LogRecord* record)
{
    std::smatch sm;
    std::regex_match (line, sm, d_expr);
    if (sm.size()!=8) {
        // Line is not a proper log line
        return -10-sm.size();
    }
    try {
        record->unparsed = line;
        record->remoteHost = sm[1];
        record->rfc931 = sm[2];
        record->authuser = sm[3];
        record->date = stol(sm[4]);
        record->request = sm[5];
        record->status = stoi(sm[6]);
        record->bytes = stol(sm[7]);
    } catch(std::logic_error& ex) {
        //  std::invalid_argument or std::out_of_range can be thrown by stoi and stol
        return -1;
    }
    return 0;
}

} // namespace monitor
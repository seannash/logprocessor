#include <monitor_logrecord.h>

#include <iostream>

namespace monitor {

std::ostream& operator<<(std::ostream& os, const LogRecord& rec)
{
    os << "[ "
       << "remoteHost: " << rec.remoteHost
       << ", rfc931: " << rec.rfc931
       << ", authuser: " << rec.authuser
       << ", date: " << rec.date
       << ", request: " << rec.request
       << ", status: " << rec.status
       << ", bytes: " << rec.bytes
       << " ]";
    return os;
}

std::string get_section(const LogRecord& rec)
{
    const std::string& request = rec.request;
    std::size_t start = request.find('/',0);
    if (start==std::string::npos)
        return {};
    std::size_t end = start+1;
    const int N = request.size();
    while(end<N && request[end]!=' ' && request[end]!='/') // TODO Better validation
        ++end;
    return request.substr(start,end-start);
}

} // namespace monitor
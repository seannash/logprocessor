#include <monitor_printercheck.h>

#include <sstream>

namespace monitor {

PrinterCheck::PrinterCheck(std::shared_ptr<Logger>& logger)
: d_logger(logger)
{}

void PrinterCheck::operator()(const LogRecord& rec)
{
    std::stringstream ss;
    ss << rec << '\n';
    d_logger->log(rec.date, ss.str());
}


} // namespace monitorclear
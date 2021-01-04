#include <iostream>

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

#include <monitor_consolelogger.h>
#include <monitor_logger.h>
#include <monitor_logrecord.h>
#include <monitor_logparser.h>

#include <monitor_genericmonitor.h>
#include <monitor_printercheck.h>
#include <monitor_trafficcheck.h>

#include <monitor_stat.h>
#include <monitor_topsitesstat.h>

int main(int argc, char** argv)
{
    // There could be other types of loggers such as the StringLogger for testing
    // TODO This all can be wrapped in a class like DatadogMonitor
    std::shared_ptr<monitor::Logger> logger = std::make_shared<monitor::ConsoleLogger>();
    std::unique_ptr<monitor::Check> trafficCheck = std::make_unique<monitor::TrafficCheck>(logger, 10);
    std::unique_ptr<monitor::Stat> topSitesStat = std::make_unique<monitor::TopSitesStat>();
    monitor::GenericMonitor gm( std::chrono::seconds(10), logger);
    gm.addCheck(std::move(trafficCheck));
    gm.addStat(std::move(topSitesStat));
    // I use a check to print the line for debugging purposes
    //std::unique_ptr<monitor::Check> printerCheck = std::make_unique<monitor::PrinterCheck>(logger);
    //gm.addCheck(std::move(printerCheck));
    // TODO Improve command line handeling
    if (argc<1) {
        std::cerr << "Useage: " << argv[0] << " [filename]\n";
    }
    std::string file_name = argv[1];
    std::ifstream input_stream(file_name);
    if (!input_stream.good()) {
        std::cerr << "Unable to open file " << file_name << std::endl;
        exit(1);
    }
    gm.process(input_stream);

    return 0;
}
#include <monitor_genericmonitor.h>

#include <catch.hpp>

#include <iostream>
#include <sstream>

#include <monitor_nulllogger.h>

namespace monitor {

TEST_CASE()
{
    std::shared_ptr<Logger> logger = std::make_shared<NullLogger>();
    GenericMonitor gm(std::chrono::seconds(1), logger);
}

TEST_CASE()
{
    std::string line =   R"|("10.0.0.1","-","apache",1549574332,"GET /api/user HTTP/1.0",200,1234)|";
    std::shared_ptr<Logger> logger = std::make_shared<NullLogger>();
    GenericMonitor gm(std::chrono::seconds(1), logger);
    const int N = 11;
    std::stringstream ss;
    for (int i=0; i<N; ++i) {
        ss << line << '\n';
        ss << "Something not good that will be skipped\n";
    }
    auto num_processed = gm.process(ss);
    REQUIRE(num_processed==N);
}

TEST_CASE()
{
    std::vector<std::string> lines{
        R"|("remotehost","rfc931","authuser","date","request","status","bytes")|",
        R"|("10.0.0.1","-","apache",1549574332,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.2","-","apache",1549573860,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.4","-","apache",1549573860,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.4","-","apache",1549573860,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.2","-","apache",1549573860,"GET /api/help HTTP/1.0",200,1234)|",
        R"|("10.0.0.5","-","apache",1549573860,"GET /api/help HTTP/1.0",200,1234)|",
        R"|("10.0.0.4","-","apache",1549573860,"GET /api/help HTTP/1.0",200,1234)|",
        R"|("10.0.0.5","-","apache",1549573860,"POST /report HTTP/1.0",500,1307)|",
        R"|("10.0.0.3","-","apache",1549573860,"POST /report HTTP/1.0",200,1234)|",
        R"|("10.0.0.3","-","apache",1549573860,"GET /report HTTP/1.0",200,1194)|",
        R"|("10.0.0.3","-","apache",154993861,"GET /report HTTP/1.0",200,1194)|",
        R"|("10.0.0.3","-","apache",1549593870,"GET /report HTTP/1.0",200,1194)|",
        R"|("10.0.0.3","-","apache",1549593880,"GET /report HTTP/1.0",200,1194)|"
    };
    std::stringstream ss;
    for(const auto& line: lines) {
        ss << line << '\n';
    }
    std::shared_ptr<Logger> logger = std::make_shared<NullLogger>();
    GenericMonitor gm(std::chrono::seconds(1), logger);
    unsigned long processed = gm.process(ss);
    // The minus one is the header which fails to parse and is ignored
    REQUIRE(processed==lines.size()-1);
 }

TEST_CASE()
{
    std::vector<std::string> lines{
        R"|("remotehost","rfc931","authuser","date","request","status","bytes")|",
        R"|("10.0.0.1","-","apache",1549574332,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.2","-","apache",1549573860,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.4","-","apache",1549573860,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.4","-","apache",1549573860,"GET /api/user HTTP/1.0",200,1234)|",
        R"|("10.0.0.2","-","apache",1549573860,"GET /api/help HTTP/1.0",200,1234)|",
        R"|("10.0.0.5","-","apache",1549573860,"GET /api/help HTTP/1.0",200,1234)|",
        R"|("10.0.0.4","-","apache",1549573860,"GET /api/help HTTP/1.0",200,1234)|",
        R"|("10.0.0.5","-","apache",1549573860,"POST /report HTTP/1.0",500,1307)|",
        R"|("10.0.0.3","-","apache",1549573860,"POST /report HTTP/1.0",200,1234)|",
        R"|("10.0.0.3","-","apache",1549573860,"GET /report HTTP/1.0",200,1194)|",
        R"|("10.0.0.3","-","apache",154993861,"GET /report HTTP/1.0",200,1194)|",
        R"|("10.0.0.3","-","apache",1549593870,"GET /report HTTP/1.0",200,1194)|",
        R"|("10.0.0.3","-","apache",1549593880,"GET /report HTTP/1.0",200,1194)|"
    };

    std::shared_ptr<Logger> logger = std::make_shared<NullLogger>();
    GenericMonitor gm(std::chrono::seconds(1), logger);
    unsigned long processed = 0;
    for(const auto& line: lines) {
        processed = gm.process(line);
    }
    // The minus one is the header which fails to parse so it is ignored
    REQUIRE(processed==lines.size()-1);
 }

} // monitor
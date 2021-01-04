

SRCS +=  monitor_check.cc
SRCS +=  monitor_consolelogger.cc
SRCS +=  monitor_genericmonitor.cc
SRCS +=  monitor_logger.cc
SRCS +=  monitor_logrecord.cc
SRCS +=  monitor_logparser.cc 
SRCS +=  monitor_nulllogger.cc
SRCS +=  monitor_printercheck.cc
SRCS +=  monitor_stat.cc
SRCS +=  monitor_storage.cc
SRCS +=  monitor_stringlogger.cc
SRCS +=  monitor_topsitesstat.cc
SRCS +=  monitor_trafficcheck.cc
OBJS = $(SRCS:.cc=.o)
MAIN = monitor.m.cc

#TEST_SRCS +=  monitor_check.t.cc
TEST_SRCS +=  monitor_consolelogger.t.cc
TEST_SRCS +=  monitor_genericmonitor.t.cc
TEST_SRCS +=  monitor_logger.t.cc
TEST_SRCS +=  monitor_logrecord.t.cc
TEST_SRCS +=  monitor_logparser.t.cc 
TEST_SRCS +=  monitor_nulllogger.t.cc
TEST_SRCS +=  monitor_printercheck.t.cc
#TEST_SRCS +=  monitor_stat.t.cc
TEST_SRCS +=  monitor_storage.t.cc
TEST_SRCS +=  monitor_stringlogger.t.cc
TEST_SRCS +=  monitor_topsitesstat.t.cc
TEST_SRCS +=  monitor_trafficcheck.t.cc
TEST_OBJS = $(TEST_SRCS:.cc=.o)
TEST_MAIN = monitor.t.cc

INCLUDES=-I. -I../catch2
CCFLAGS=-g --std=c++17
CXX=g++
LIBS=

.DEFAULT_GOAL:= all

%.o:: %.cc
	$(CXX) $(INCLUDES) $(CCFLAGS) ${LIBS} -c $< -o $*.o

%.t.o:: %.t.cc
	$(CXX) $(INCLUDES) $(CCFLAGS) ${LIBS} -c $< -o $*.t.o

all: $(OBJS) ${MAIN} $(TEST_OBJS) ${TEST_MAIN}
	$(CXX) $(INCLUDES) $(CCFLAGS) ${LIBS} ${OBJS} ${MAIN} -o monitor
	$(CXX) $(INCLUDES) $(CCFLAGS) ${LIBS} ${OBJS} ${TEST_OBJS} ${TEST_MAIN} -o monitor_unit_tests

.PHONY:
test: 
	./monitor_unit_tests
        
clean:
	rm -f *.o monitor monitor_unit_tests

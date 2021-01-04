# Random Project For Fun

This application proccesses logs and displays metrics.

## How to Build And Run

This project is written in C++ so a lot of fun can be involved in building.
The only external dependency is the catch2 library that is inluded with this project.
I developed this on a linux computer. The computer needs make and a recent version of gcc
that supports C++11. A docker target is setup in the makefile to run gcc:10 from
dockerhub which can successfully build and run the project.

The following commands can be used to start docker, build, run unit tests and run the executable
against the sample provided.

```shell
make docker
make
make sample
```

For docker to see other log files, they have to be in the project directory or subdirectory. And the monitor program can be run:
```shell
src/monitor data/sample_csv.txt
```

## Design 20,000 View

The biggest decision was whether to make the application multithreaded or single threaded. I went with a single threaded
approach which keeps all of the ouput logs in sync. A multithreaded approach could have different checks outputing
alerts out of time order but can be more performant.

The main() sets up a GenericMonitor, which reads a file. The file is only read one line at a time
and after parsing that line is sent to the stat objects and checker objects. Every 10 seconds
that is passed in log file time, the stat messages are printed. If one log line is 200 seconds ahead,
the stats are only printed at the first expected 10 second interval than skipped.

The skipping of stat printing when no logs are coming in was a design decision. I prefer not to have that data
as log files when nothing is happening can be very large. In the past I have seen those log sections as just noise.

## General C++ Notes

I went with a physical design style fo having a namespace for the project, "monitor"
and having this namespace prefix all component files. A component has two or three files.
The implementation is in a ".cc" file. The header is in a ".h" file. Most components except for
two of the abstract base classes have a test implementation file which is ".t.cpp". The namespace
besides being part of the file name is a C++ namespace in all the files but the two main files.
The normal main is in "monitor.m.cpp". And the main for test executable is part of catch2
and included in "monitor.t.cpp"

## Libraries Used

I used the catch2 library for testing. This is in the directory "catch2".

## Improvements

- Improve on the command line parameter parsing in "monitor.m.cpp".
- The alert messages by TrafficCheck can have a parser or be created in such a way that the test
does not have to know the exact strings which is brittle.
- Consistent use of time representation. At the beginning I used std::chrono but then switched to
the original unsigned long format.
- Use of a better regex library that than std::regex. It is known to be slow.
- Use std::string_view instead of strings for function calls that only need a view. One thing
holding back useage was std::regex does not use std::string_view yet.

## Components


### Checks

Checks can components that can be added to a Monitor object and these will be feed in LogRecords. Alerts will be logged.

component             | Description
----------------------|--------------------------------------------------------------------------------------
monitor_check         | Protocol class (Abstract Base Class) for all checks
monitor_printercheck  | Check does not allerts and prints all logs processed to standard out for debugging.
monitor_trafficcheck  | Checks for high and low traffic

### Statistics

Statistics are for calculating values of the logs. The time span of all statistics is set universally by
the GenericMonitor class and the default is 120 seconds. The single datastore is used to save memory.

component             | Description
----------------------|--------------------------------------------------------------------------------------
monitor_stat          | Protocol class (abstract base class) for all stat classes
monitor_topsitesstat  | Keeps track of the top sites seen

### Monitor

The monitor classes of which there is only one is the focus of this assignment. A monitor object is created, and
statistics and checks can be added. The monitor can read logs from a file or take one string at a time.

component              | Description
-----------------------|--------------------------------------------------------------------------------------
monitor_genericmonitor | The log monitor class

### Loggers

Loggers control where the output of checks and stats objects are written too

component              | Description
-----------------------|--------------------------------------------------------------------------------------
monitor_consolelogger  | This writes logs to the console
monitor_logger         | Protocol class (abstract base class) for all loggers
monitor_nulllogger     | Used for testing and does not write any logs.
monitor_stringlogger   | Used for testing and writes logs to a string.

### Storage

The storage component keeps track of all logs that are currently used for statistics. Currently,
monitor_genericmonitor uses monitor_storage to maintain some logs need for statistics in memory. 

component              | Description
-----------------------|--------------------------------------------------------------------------------------
monitor_storage        | Keeps track of logs seen by time and limits by a time span, used for a shared store for statistics


### Log Related

Logs are read in from a file. The string needs to be parsed for the classes to use.

component              | Description
-----------------------|--------------------------------------------------------------------------------------
monitor_logparser      | Parses a log string into a LogRecord
monitor_logrecord      | Holds a log by fields

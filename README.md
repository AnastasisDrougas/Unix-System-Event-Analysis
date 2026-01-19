# Unix System Event Analysis
This project implements an event monitoring system in a UNIX environment that collects and processes log files. Shell scripts are used for filtering and automation, while C programs handle statistics extraction and error management. Parallel processing with threads enables faster analysis of multiple log files.

## How to run
### Single thread implementation (analyse.c)
  - gcc -o analyze_log analyse.c
  - ./analyse_log yourLogFile
### Shell script for running multiple log files at once (run_monitor.sh)
  - gcc -o analyze_log analyse.c
  - chmod +x run_monitor.sh
  - ./run_monitor.sh yourFolder
### Multithreading implementation (parallel_analyse.c)
  - gcc -o parallel_analyse_log parallel_analyse.c -pthread
  - ./parallel_analyse_log yourLogFile1.log yourLogFile2.log ...

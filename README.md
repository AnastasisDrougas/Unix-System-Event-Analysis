# Unix System Event Analysis

A UNIX-based log analysis and event monitoring system built with **C and Bash**. The project automates log processing, extracts statistics from log files, and identifies events of interest using shell scripting and compiled C programs.

It includes both a single-threaded implementation and a multithreaded implementation using POSIX threads (pthreads) to process multiple log files concurrently.

## Features

- **Log analysis in C** — process log files and extract relevant statistics.
- **Shell automation** — filter, sort, and organize log data using Bash and standard UNIX utilities.
- **Event monitoring** — identify and process relevant log events.
- **Multithreaded processing** — analyze multiple log files concurrently using POSIX threads.
- **Error handling** — handle file access and processing errors.
- **Automated reporting** — organize processed results and generate summary reports.

## Requirements

- Linux or another UNIX-like operating system
- GCC compiler
- Bash
- POSIX threads (`pthread`)
- Standard UNIX utilities such as `grep` and `sort`

## Installation

Clone the repository:

```bash
git clone https://github.com/AnastasisDrougas/Unix-System-Event-Analysis.git
cd Unix-System-Event-Analysis
```

Compile the programs using GCC.

### Single-threaded implementation

```bash
gcc -Wall -Wextra -o analyze_log analyse.c
```

### Multithreaded implementation

```bash
gcc -Wall -Wextra -o parallel_analyse_log parallel_analyse.c -pthread
```

## Usage

### 1. Analyze a single log file

Run the single-threaded analyzer with a log file as its argument:

```bash
./analyze_log yourLogFile.log
```

### 2. Monitor and process multiple log files

Make the monitoring script executable:

```bash
chmod +x run_monitor.sh
```

Run it by providing the directory containing the log files:

```bash
./run_monitor.sh yourFolder
```

The script automates log processing using shell utilities and organizes the resulting data and reports according to its implementation.

### 3. Analyze multiple log files concurrently

Run the multithreaded analyzer with one or more log files:

```bash
./parallel_analyse_log file1.log file2.log file3.log
```

The multithreaded implementation uses POSIX threads to process multiple input files concurrently.

## Technologies

- **C** — log processing, statistics extraction, and error handling
- **Bash** — automation and workflow orchestration
- **GCC** — compilation
- **POSIX threads (pthreads)** — concurrent log analysis
- **UNIX utilities** — text filtering, sorting, and file processing


#!/bin/bash

#
# @author AnastasisDrougas - it2024023.
# @date 30/12/2025.
#

#Print file's name and #arguements.
echo "File Name: $0"
echo "Argument Number: $#"

#Checking if the user gave any arguments.
if [ "$#" -lt 1 ]; then 
    echo "No arguments given!, Usage: $0 <directory>"
    exit 1
fi

dir="$1"
report="./monitor/reports/full_reports.txt"

> "$report"

#Checking if the given directory exists.
if [ ! -d "$dir" ];then
    echo "Directory '$dir' does not exist!"
    exit 1
fi

#Checking if the given directory is empty.
if [ -z "$(ls -A "$dir")" ];then
    echo "Directory '$dir' is Empty!"
    exit 0
fi

#Checking if the analyse.log is executable
if [ ! -x ./analyse_log ];then
    echo "Error: ./analyse_log is not executable!"
    exit 1
fi

#For each file in this directory:
for file in "$dir"/*;do
    if [ -f "$file" ]; then
        echo "Processing $file.."

        case "$(basename "$file")" in
            network.log)
                echo "NETWORK: '$file' ->" >> "$report"
                ;;
            system.log)
                echo "SYSTEM: '$file' ->" >> "$report"
                ;;
            security.log)
                echo "SECURITY: '$file' ->" >> "$report"
                ;;
            *)
                echo "OTHER: '$file' ->" >> "$report"
                ;;
        esac
        ./analyse_log "$file" >> "$report"
    fi 
done
echo "All logs processed. Report saved to $report"
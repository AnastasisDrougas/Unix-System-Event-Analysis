#!/bin/bash
while true; do
    echo "$(date) TIMESTAMP_LOOP" >> monitor/raw/timestamps.log
    sleep 7
done

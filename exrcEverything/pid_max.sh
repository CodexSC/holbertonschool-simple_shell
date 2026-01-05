#! /bin/bash

if [ -f /proc/sys/kernel/pid_max ]; then
    echo "Maximum PID: $(cat /proc/sys/kernel/pid_max)"
else
    echo "Error: /proc/sys/kernel/pid_max not found"
    echo "This script requires a Linux system with /proc filesystem support"
    exit 1
fi

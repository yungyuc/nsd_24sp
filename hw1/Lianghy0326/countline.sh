#!/bin/bash

# Check if the correct number of arguments is passed
if [ "$#" -ne 1 ]; then
    if [ "$#" -lt 1 ]; then
        echo "missing file name"
    else
        echo "only one argument is allowed"
    fi
    exit 1
fi

# Check if the file exists
if [ -e "$1" ]; then
    # Count the lines and print the result
    line_count=$(wc -l < "$1")
    echo "${line_count} lines in $1"
else
    echo "$1 not found"
fi




#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "missing file name"
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
else
    file_name=$1
    # check if file exists
    if [ -e "${file_name}" ]; then
        line=$(wc -l $1)
        echo "${line} lines in ${filename}"
    else
        echo "${file_name} not found"
    fi
fi
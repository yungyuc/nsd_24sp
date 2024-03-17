#!/bin/bash

if [ $# -lt 1 ]; then
    echo "missing file name"
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed"
else
    fname=$1
    if [ -e "$fname" ]; then
        num_lines=$(wc -l < "$fname")
        echo "$num_lines lines in $fname"
    else
        echo "$fname not found"
    fi
fi
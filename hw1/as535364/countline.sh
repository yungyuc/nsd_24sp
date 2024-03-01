#!/bin/bash

if [ $# -lt 1 ]; then
    echo "missing file name"
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
else
    file=$1
    if [ -f $file ]; then
        lines=$(wc -l < $file)
        echo "$lines lines in $file"
    else
        echo "$file not found"
    fi
fi

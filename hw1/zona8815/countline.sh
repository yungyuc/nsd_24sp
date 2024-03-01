#!/bin/bash

# Check the number of arguments
# < 1
if [ "$#" -lt 1 ]; then
    echo "missing file name"
# > 1
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
else
    fname=$1
    # Check if the file exists or not
    if [ -e "$fname" ]; then
        # Count the number of lines
        num_lines=$(wc -l < "$fname")
        echo "$num_lines lines in $fname"
    else
        echo "$fname not found"
    fi
fi

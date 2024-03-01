#!/bin/bash

# Count lines in file
# Usage:
# ./countline.sh [filename]

if (($# < 1)); then
    echo "missing file name"
elif (($# > 1)); then
    echo "only one argument is allowed"
else
    echo $(wc -l countline.sh | tr -dc '0-9')
fi

# [Note] $# get the number of arguments (command not included)

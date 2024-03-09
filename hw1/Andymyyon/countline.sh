#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Please select exactly one file";
    exit;
elif [[ ! $(file -b $1) == *"text"* ]];
then
    echo "Please select a file that exists and contains text";
    exit;
else
    echo "All good";
fi

let "count=0"
count=$(wc -l < $1)
echo "There are "$count" lines in this file.";
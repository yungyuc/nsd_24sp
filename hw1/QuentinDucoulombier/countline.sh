#!/bin/bash

if [ "$#" -lt 1 ]; then
	echo "missing file name"
	exit 1
elif [ "$#" -gt 1 ]; then
	echo "only one argument is allowed"
	exit 1
else
	if [ -f "$1" ]; then
		lines=$(wc -l < "$1")
    	echo "$lines lines in $1"
  	else
    	echo "$1 not found"
    	exit 1
  	fi
fi

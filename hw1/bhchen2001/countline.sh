#!/bin/bash

#
# This script count the number of lines in a file
#

# get the file name from the command line
countFile=$1

# argument check
if [ "$#" -eq "0" ] ; then
  echo "missing file name"
  exit 1
elif [ "$#" -gt "1" ] ; then
  echo "only one argument is allowed"
  exit 1
else
  if [ ! -e $countFile ] ; then
    echo "file not found"
    exit 1
  else
    echo $(wc -l $countFile | cut -d ' ' -f 1) lines in $countFile
  fi
fi

exit 0

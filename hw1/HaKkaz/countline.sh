#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 1 ]; then
  echo "Usage: $0 <file>"
  exit 1
fi

filename=$1

if [ ! -f "$filename" ]; then
  echo "$filename not found"
  exit
fi

line_count=$(wc -l $filename | tr -dc "0-9")
echo "$line_count lines in $filename"

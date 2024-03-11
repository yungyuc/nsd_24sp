#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo $#
    echo "missing file name"
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
else 
    fname="$1"
    if [ -f "$fname" ];then
        echo "`wc -l $fname` lines in $fname"
    else 
        echo "$fname not found"
    fi
fi






# #!/usr/bin/env python3

# import sys
# import os.path


# if len(sys.argv) < 2:
#     sys.stdout.write('missing file name\n')
# elif len(sys.argv) > 2:
#     sys.stdout.write('only one argument is allowed\n')
# else:
#     fname = sys.argv[1]
#     if os.path.exists(fname):
#         with open(fname) as fobj:
#             lines = fobj.readlines()
#         sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
#     else:
#         sys.stdout.write('{} not found\n'.format(fname))



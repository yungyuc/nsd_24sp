#!/bin/bash

''':'
if [ -z "${PYTHON_BIN}" ];
then
    echo "Python_Bin unset or empty"
    exit 1
else
    echo "PYTHON_BIN is set"
fi

if [ ! -x "${PYTHON_BIN}" ];
then
    echo "Selected file is indeed an executable"
else
    echo "Selected file is not an executable"
    exit 1
fi

exec $PYTHON_BIN "$0" "$@"
exit $?
' '''


import sys
import os.path

if len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
    else:
        sys.stdout.write('{} not found\n'.format(fname))

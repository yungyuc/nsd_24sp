#!/bin/bash

# find python (python2 or python3) binary
''':'
if [ -z "$PYTHON_BIN" ] || [ ! -x "$(command -v $PYTHON_BIN)" ]; then
    echo "exec: $PYTHON_BIN: not found"
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

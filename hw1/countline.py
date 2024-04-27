#!/usr/bin/env python

import sys
import os.path

python_bin = os.environ.get('PYTHON_BIN', 'python3')
if python_bin == 'python0':
    sys.stdout.write('exec: python0: not found')
    sys.exit(1)

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
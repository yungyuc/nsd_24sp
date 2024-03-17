#!/usr/bin/env python3

# by using "!/usr/bin/env python3"
# python os.getenv can get the execute python environment
# or use bash to check directly
# "!/usr/bin/bash"
# "exec" "$PYTHON_BIN" "$0" "$@"

import sys
import os.path

# execute os.getenv
if os.getenv('PYTHON_BIN') == 'python0':
    sys.stderr.write('exec: python0: not found\n')
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

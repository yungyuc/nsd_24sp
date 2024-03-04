#!/bin/bash
''':'
# Check if PYTHON_BIN is set, otherwise default to python3
PYTHON_BIN=${PYTHON_BIN:-python3}

# Check if the specified Python binary exists and is executable
if ! command -v "$PYTHON_BIN" &> /dev/null; then
    echo "Error: Python binary '$PYTHON_BIN' not found."
    exit 1
fi

# Execute the script with the specified Python interpreter
exec "$PYTHON_BIN" "$0" "$@"
exit $?
' '''


import sys
import os.path

def main():
    if len(sys.argv) < 2:
        sys.stderr.write('missing file name\n')
        return 1
    elif len(sys.argv) > 2:
        sys.stderr.write('only one argument is allowed\n')
        return 1
    else:
        fname = sys.argv[1]
        if os.path.exists(fname):
            with open(fname) as fobj:
                lines = fobj.readlines()
            sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
            return 0
        else:
            sys.stderr.write('{} not found\n'.format(fname))
            return 1

if __name__ == '__main__':
    sys.exit(main())

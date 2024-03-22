# setup.py

import os
import sys
import setuptools
from setuptools import setup, Extension
import pybind11

# Define the extension module
module = Extension(
    "_vector",                              # Module name
    sources=["vector2D.cpp"],               # C++ source file
    include_dirs=[pybind11.get_include()],  # Include pybind11 headers
    language="c++"
)

# Setup
def main():
    setup(
        name="_vector",
        description="Custom vector class to calculate angle between two vectors",
        ext_modules=[module],
        # install_requires=["pybind11>=2.6"],
        # setup_requires=["pybind11>=2.6"],
        # python_requires=">=3.6",
    )

if __name__ == '__main__':
    main()

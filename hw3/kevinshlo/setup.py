#!/usr/bin/env python3

from setuptools import setup, Extension

module = Extension("_matrix", sources=["matrix.cpp"], libraries=["cblas"])

setup(
    name="_matrix",
    version="1.0",
    ext_modules=[module],
)

#!/usr/bin/env python3

from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension("_vector", ["_vector.cpp"]),
]

setup(
    name="_vector",
    version="1.0",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)

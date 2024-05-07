#!/usr/bin/env python3

from setuptools import setup, Extension

# https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-link-line-advisor.html
module = Extension(
    "_matrix",
    sources=["./matrix.cpp", "../mod.cpp"],
    include_dirs=["${MKLROOT}/include", "./"],
    library_dirs=["${MKLROOT}/lib/intel64"],
    libraries=["mkl_rt", "pthread", "m", "dl"],
    extra_compile_args=["-std=c++17", "-O3", "-m64", "-Wl,--no-as-needed"],
    define_macros=[("MKL", None)],
)

setup(
    name="_matrix",
    version="1.0",
    ext_modules=[module],
)

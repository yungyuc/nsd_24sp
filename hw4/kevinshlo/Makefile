matrix: matrix.cpp setup.py
#	command -v apt-get > /dev/null 2>&1 && sudo apt-get -qy install libopenblas-dev || sudo dnf -qy install blas-devel openblas-devel
	python setup.py -q build_ext --inplace
#	stubgen -m _matrix --include-docstrings -o ./

test: matrix test_matrix.py
	python3 -m pytest -v

clean:
	rm -rf build __pycache__ .pytest_cache
	rm -f _matrix.*.so
#	rm _matrix.pyi

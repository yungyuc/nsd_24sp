matrix: matrix.cpp setup.py
	python setup.py -q build_ext --inplace
#	stubgen -m _matrix --include-docstrings -o ./

test: matrix test_matrix.py
	python3 -m pytest -v

clean:
	rm -rf build __pycache__ .pytest_cache
	rm -f _matrix.*.so
#	rm _matrix.pyi

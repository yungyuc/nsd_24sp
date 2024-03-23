_vector: _vector.cpp setup.py
	./setup.py -q build_ext --inplace

test: _vector _vector_test.py
	python3 -m pytest -v

clean:
	rm -r build
	rm _vector.*.so

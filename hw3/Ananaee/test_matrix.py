import pytest
# from _matrix import Matrix, multiply_naive, multiply_tile, multiply_mkl
import _matrix

# Test matrix creation
def test_make_matrix():
    nrow = 3
    ncol = 4
    mat = _matrix.Matrix(nrow, ncol)
    assert mat.nrow() == nrow
    assert mat.ncol() == ncol

def test_make_matrix2():
     
    nrow = 2
    ncol = 2
    mat = _matrix.Matrix(nrow, ncol, [1.0,1.0,1.0,1.0])
    assert mat.nrow() == nrow
    assert mat.ncol() == ncol

    for i in range(nrow):
        for j in range(ncol):
            assert mat[i,j] == 1.0

def test_basic():
    size = 100
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    mat3 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0
            
    assert size == mat1.nrow()
    assert size == mat1.ncol()
    assert size == mat2.nrow()
    assert size == mat2.ncol()
    assert size == mat3.nrow()
    assert size == mat3.ncol()

    assert 2 == mat1[0, 1]
    assert size + 2 == mat1[1, 1]
    assert size * 2 == mat1[1, size - 1]
    assert size * size == mat1[size - 1, size - 1]

    for i in range(mat1.nrow()):
        for j in range(mat1.ncol()):
            assert 0 != mat1[i, j]
            assert mat1[i, j] == mat2[i, j]
            assert 0 == mat3[i, j]

    assert mat1 == mat2
    assert mat1 is not mat2

def test_multiplication():
    size = 5
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    mat3 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0

    res_naive = _matrix.multiply_naive(mat1, mat2)
    res_tile = _matrix.multiply_tile(mat1, mat2,2)
    res_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert size == res_naive.nrow()
    assert size == res_naive.ncol()
    assert size == res_mkl.nrow()
    assert size == res_mkl.ncol()
    assert size == res_tile.nrow()
    assert size == res_tile.ncol()

    for i in range(res_naive.nrow()):
        for j in range(res_naive.ncol()):
            assert mat1[i, j] != res_mkl[i, j]
            assert res_naive[i, j] == res_mkl[i, j]==res_tile[i,j]

# Test naive matrix multiplication
def test_multiply_naive():
    mat1 = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
    mat2 = _matrix.Matrix(3, 2, [7, 8, 9, 10, 11, 12])
    result = _matrix.multiply_naive(mat1, mat2)
    expected_result = [[58, 64], [139, 154]]
    for i in range (result.nrow()) :
        for j in range (result.ncol()):
            assert result(i,j) == expected_result[i,j]

# Test matrix multiplication with tiling
def test_multiply_tile():
    mat1 = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
    mat2 = _matrix.Matrix(3, 2, [7, 8, 9, 10, 11, 12])
    result = _matrix.multiply_tile(mat1, mat2, 1)  # Set tile_size = 1 for testing
    expected_result = [[58, 64], [139, 154]]
    for i in range (result.nrow()) :
        for j in range (result.ncol()):
            assert result(i,j) == expected_result[i,j]

# Test matrix multiplication with MKL
def test_multiply_mkl():
    mat1 = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
    mat2 = _matrix.Matrix(3, 2, [7, 8, 9, 10, 11, 12])
    result = _matrix.multiply_mkl(mat1, mat2)
    expected_result = [[58, 64], [139, 154]]
    for i in range (result.nrow()) :
        for j in range (result.ncol()):
            assert result(i,j) == expected_result[i,j]

# Test multiplication with identity matrix
def test_multiply_with_identity():
    mat = _matrix.Matrix(3, 3, [1, 2, 3, 4, 5, 6, 7, 8, 9])
    identity = _matrix.Matrix(3, 3, [1, 0, 0, 0, 1, 0, 0, 0, 1])
    result = _matrix.multiply_naive(mat, identity)
    for i in range (result.nrow()) :
        for j in range (result.ncol()):
            assert result[i,j] == mat[i,j]

# Test multiplication with transpose matrix
def test_multiply_with_transpose():
    mat = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
    transpose = _matrix.Matrix(3, 2, [1, 4, 2, 5, 3, 6])
    result = _matrix.multiply_naive(mat, transpose)
    expected_result = [[14, 32], [32, 77]]
    for i in range (result.nrow()) :
        for j in range (result.ncol()):
            assert result[i,j] == expected_result[i,j]

# Test multiplication with zero matrix
def test_multiply_with_zero():
    mat = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
    zero = _matrix.Matrix(3, 3, [0, 0, 0, 0, 0, 0, 0, 0, 0])
    result = _matrix.multiply_naive(mat, zero)
    for i in range (result.nrow()) :
        for j in range (result.ncol()):
            assert result[i,j] == zero[i,j]

# Run the tests
if __name__ == "__main__":
    pytest.main([__file__])

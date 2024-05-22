
import pytest
import _matrix 

def test_matrix_creation_and_access():
    """Test the creation of a matrix and access to its elements."""
    nrow, ncol = 2, 3
    m = _matrix.Matrix(nrow, ncol)
    assert m.nrow == nrow
    assert m.ncol == ncol

    # Test initialization and access using __setitem__ and __getitem__
    for i in range(nrow):
        for j in range(ncol):
            m[i, j] = i * ncol + j  

    for i in range(nrow):
        for j in range(ncol):
            assert m[i, j] == i * ncol + j 

def populate_matrix(A, B):
    """Populate matrices A and B for multiplication using __setitem__."""
    A[0, 0] = 1
    A[0, 1] = 2
    A[1, 0] = 3
    A[1, 1] = 4

    B[0, 0] = 2
    B[0, 1] = 0
    B[1, 0] = 1
    B[1, 1] = 2

def test_multiply_naive():
    """Test naive matrix multiplication."""
    A = _matrix.Matrix(2, 2)
    B = _matrix.Matrix(2, 2)
    populate_matrix(A, B)

    C = _matrix.multiply_naive(A, B)

    assert C[0, 0] == 4
    assert C[0, 1] == 4
    assert C[1, 0] == 10
    assert C[1, 1] == 8

def test_multiply_tile():
    """Test matrix multiplication with tiling."""
    A = _matrix.Matrix(2, 2)
    B = _matrix.Matrix(2, 2)
    populate_matrix(A, B)

    C = _matrix.multiply_tile(A, B, 128)

    assert C[0, 0] == 4
    assert C[0, 1] == 4
    assert C[1, 0] == 10
    assert C[1, 1] == 8

def test_multiply_mkl():
    """Test matrix multiplication using MKL."""
    A = _matrix.Matrix(2, 2)
    B = _matrix.Matrix(2, 2)
    populate_matrix(A, B)

    C = _matrix.multiply_mkl(A, B)

    assert C[0, 0] == 4
    assert C[0, 1] == 4
    assert C[1, 0] == 10
    assert C[1, 1] == 8

def test_incompatible_dimensions():
    """Test multiplication with incompatible dimensions."""
    A = _matrix.Matrix(2, 3)
    B = _matrix.Matrix(2, 2)  # Incompatible with A for multiplication

    with pytest.raises(ValueError):
        _matrix.multiply_naive(A, B)

    with pytest.raises(ValueError):
        _matrix.multiply_tile(A, B, 128)

    with pytest.raises(ValueError):
        _matrix.multiply_mkl(A, B)
if __name__ == "__main__":
    pytest.main()
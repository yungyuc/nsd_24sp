import _matrix  

def get_bytes_allocated():
    """Return the number of bytes currently allocated by matrices."""
    return _matrix.bytes()

def get_total_allocated():
    """Return the total number of bytes allocated since the program started without subtracting deallocated memory."""
    return _matrix.allocated()

def get_total_deallocated():
    """Return the total number of bytes deallocated since the program started."""
    return _matrix.deallocated()

def create_matrix(nrows, ncols):
    """Create a new matrix with given dimensions using the C++ matrix class."""
    return _matrix.Matrix(nrows, ncols)

def multiply_matrices(mat1, mat2):
    """Multiply two matrices using the defined multiplication method in C++, e.g., MKL-based multiplication."""
    return _matrix.multiply_mkl(mat1, mat2)

def print_matrix(mat):
    """Utility function to print a matrix row by row."""
    for i in range(mat.nrow):
        for j in range(mat.ncol):
            print(f"{mat[i, j]:.2f}", end=" ")
        print() 

if __name__ == "__main__":
    A = create_matrix(3, 3)
    B = create_matrix(3, 3)
    
    for i in range(3):
        for j in range(3):
            A[i, j] = i + 1
            B[i, j] = (i + 1) * (j + 1)

    print("Matrix A:")
    print_matrix(A)
    print("Matrix B:")
    print_matrix(B)

    C = multiply_matrices(A, B)
    print("Product of A and B:")
    print_matrix(C)

    # Display memory usage
    print(f"Bytes currently allocated: {get_bytes_allocated()} bytes")
    print(f"Total bytes allocated: {get_total_allocated()} bytes")
    print(f"Total bytes deallocated: {get_total_deallocated()} bytes")

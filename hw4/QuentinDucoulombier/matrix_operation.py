import _matrix  

def get_bytes_allocated():
    """Return the number of bytes currently allocated by matrices."""
    return _matrix.bytes()

def get_total_allocated():
    """Return the total number of bytes allocated since the program started."""
    return _matrix.allocated()

def get_total_deallocated():
    """Return the total number of bytes deallocated since the program started."""
    return _matrix.deallocated()

def create_matrix(nrows, ncols):
    """Create a new matrix with given dimensions."""
    return _matrix.Matrix(nrows, ncols)

def multiply_matrices(mat1, mat2):
    """Multiply two matrices using the defined multiplication method in C++."""
    return _matrix.multiply_mkl(mat1, mat2)

def print_matrix(mat):
    """Utility function to print a matrix."""
    for i in range(mat.nrow):
        for j in range(mat.ncol):
            print(f"{mat[i, j]:.2f}", end=" ")
        print()  # Newline for next row

if __name__ == "__main__":
    # Example usage
    A = create_matrix(3, 3)
    B = create_matrix(3, 3)
    
    # Populating matrices with values
    for i in range(3):
        for j in range(3):
            A[i, j] = i + 1
            B[i, j] = (i + 1) * (j + 1)

    print("Matrix A:")
    print_matrix(A)
    print("Matrix B:")
    print_matrix(B)

    # Perform matrix multiplication
    C = multiply_matrices(A, B)
    print("Product of A and B:")
    print_matrix(C)

    # Memory usage
    print(f"Bytes allocated: {get_bytes_allocated()} bytes")
    print(f"Total allocated: {get_total_allocated()} bytes")
    print(f"Total deallocated: {get_total_deallocated()} bytes")

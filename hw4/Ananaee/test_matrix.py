import _matrix
import pytest

import sys
import os
import timeit
import unittest

class MatrixTest(unittest.TestCase):

    def make_matrices(self, nrow, ncol):

        mat = _matrix.Matrix(nrow, ncol)

        for i in range(nrow):
            for j in range(ncol):
                mat[i,j] = i*ncol+j+1

        return mat
    
    def test_make_matrix(self):
        nrow = 3
        ncol = 4
        mat = _matrix.Matrix(nrow, ncol)
        assert mat.nrow == nrow
        assert mat.ncol == ncol

    def test_make_matrix2(self):

        size = 10
        mat_elements = [i for i in range(1, size*size+1)]
        mat1 = _matrix.Matrix(size, size, mat_elements)

        for i in range(size):
            for j in range(size):
                self.assertEqual(mat_elements[i*size+j], mat1[i,j])



    def test_basic(self):

        nrow = 100
        ncol = 200

        mat1 = self.make_matrices(nrow, ncol)
        mat2 = self.make_matrices(nrow, ncol)
        mat3 = self.make_matrices(nrow, ncol)

        assert nrow == mat1.nrow == mat2.nrow == mat3.nrow
        assert ncol == mat1.ncol == mat2.ncol == mat3.ncol

        for i in range(nrow):
            for j in range(ncol):
                assert (i * ncol + j + 1) == mat1[i,j] == mat2[i,j] == mat3[i,j]

        self.assertEqual(mat1, mat2)
        self.assertTrue(mat1 is not mat2)

    def test_multiply_match(self):

        size1 = 100
        size2 = 200
        size3 = 300
        t_size = 16

        mat1 = _matrix.Matrix(size1, size2)
        mat2 = _matrix.Matrix(size2, size3)

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_tile = _matrix.multiply_tile(mat1, mat2, t_size)
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        assert size1 == ret_naive.nrow == ret_tile.nrow == ret_mkl.nrow
        assert size3 == ret_naive.ncol == ret_tile.ncol == ret_mkl.ncol

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                assert ret_naive[i,j] == ret_tile[i,j]
                assert ret_tile[i,j] == ret_mkl[i,j]


    def check_tile(self, mat1, mat2, tsize):

        if 0 == tsize:
            ret_tile = _matrix.multiply_naive(mat1, mat2)
            tile_str = "_matrix.multiply_naive(mat1, mat2)"
        else:
            ret_tile = _matrix.multiply_tile(mat1, mat2, tsize)
            tile_str = "_matrix.multiply_tile(mat1, mat2, tsize)"
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        for i in range(ret_tile.nrow):
            for j in range(ret_tile.ncol):
                self.assertNotEqual(mat1[i,j], ret_mkl[i,j])
                self.assertEqual(ret_tile[i,j], ret_mkl[i,j])

        ns = dict(_matrix=_matrix, mat1=mat1, mat2=mat2, tsize=tsize)
        t_tile = timeit.Timer(tile_str, globals=ns)
        t_mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', globals=ns)

        time_tile = min(t_tile.repeat(10, 1))
        time_mkl = min(t_mkl.repeat(10, 1))
        ratio = time_tile/time_mkl

        return ratio, time_tile

    def test_tile_perf(self):

        size = 500
        t_size_list = [16, 32, 64]

        show_ratio = bool(os.environ.get('SHOW_RATIO', False))

        mat1 = self.make_matrices(size, size)
        mat2 = self.make_matrices(size, size)

        ratio0, time0 = self.check_tile(mat1, mat2, 0)
        if show_ratio:
            print("naive ratio:", ratio0)

        for t_size in t_size_list:
            ratio, time = self.check_tile(mat1, mat2, t_size)
            if show_ratio:
                print(f"tile {t_size} ratio:", ratio)
                print(f"time{t_size}/time0:", time/time0)
            self.assertLess(ratio/ratio0, 0.8) 


    def test_multiply_naive(self):
        mat1 = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
        mat2 = _matrix.Matrix(3, 2, [7, 8, 9, 10, 11, 12])
        result = _matrix.multiply_naive(mat1, mat2)
        expected_result = [[58, 64], [139, 154]]
        for i in range (result.nrow) :
            for j in range (result.ncol):
                assert result[i,j] == expected_result[i][j]

    def test_multiply_mkl(self):
        mat1 = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
        mat2 = _matrix.Matrix(3, 2, [7, 8, 9, 10, 11, 12])
        result = _matrix.multiply_mkl(mat1, mat2)
        expected_result = [[58, 64], [139, 154]]
        for i in range (result.nrow) :
            for j in range (result.ncol):
                assert result[i,j] == expected_result[i][j]

    # Test multiplication with identity matrix
    def test_multiply_with_identity(self):
        mat = _matrix.Matrix(3, 3, [1, 2, 3, 4, 5, 6, 7, 8, 9])
        identity = _matrix.Matrix(3, 3, [1, 0, 0, 0, 1, 0, 0, 0, 1])
        result = _matrix.multiply_naive(mat, identity)
        for i in range (result.nrow) :
            for j in range (result.ncol):
                assert result[i,j] == mat[i,j]


    # Test multiplication with zero matrix
    def test_multiply_with_zero(self):
        mat = _matrix.Matrix(2, 3, [1, 2, 3, 4, 5, 6])
        zero = _matrix.Matrix(3, 3, [0, 0, 0, 0, 0, 0, 0, 0, 0])
        result = _matrix.multiply_naive(mat, zero)
        for i in range (result.nrow) :
            for j in range (result.ncol):
                assert result[i,j] == zero[i,j]




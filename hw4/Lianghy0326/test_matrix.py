import _matrix
import pytest
import sys
import os
import timeit
import unittest

class GradingTest(unittest.TestCase):

    def make_matrices(self, nrow, ncol):

        mat = _matrix.Matrix(nrow, ncol)

        for i in range(nrow):
            for j in range(ncol):
                mat[i,j] = i*ncol+j+1

        return mat

    def test_basic(self):
        nrow = 100
        ncol = 200

        mat1 = self.make_matrices(nrow, ncol)
        mat2 = self.make_matrices(nrow, ncol)
        mat3 = self.make_matrices(nrow, ncol)

        assert nrow == mat1.row == mat2.row == mat3.row
        assert ncol == mat1.col == mat2.col == mat3.col

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

        mat1 = self.make_matrices(size1, size2) # 100 x 200
        self.assertEqual(8 * size1*size2, _matrix.bytes())
        mat2 = self.make_matrices(size2, size3) # 200 x 300
        self.assertEqual(8 * size1*size2 + 8 * size2*size3, _matrix.bytes())

        base_bytes = _matrix.bytes()
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_tile = _matrix.multiply_tile(mat1, mat2, t_size)
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        assert size1 == ret_naive.row == ret_tile.row == ret_mkl.row
        assert size3 == ret_naive.col == ret_tile.col == ret_mkl.col


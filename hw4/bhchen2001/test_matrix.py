# mod from validate.py@nsdhw_24sp/hw3

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

    def test_basic(self):

        '''
        unit test basic matrix operations
            - nrow, ncol
            - getitem
            - setitem
            - equality
        '''
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

        '''
        unit test matrix multiplication correctness
            - naive
            - tile
            - mkl
        '''
        size1 = 100
        size2 = 200
        size3 = 300
        t_size = 16

        mat1 = self.make_matrices(size1, size2)
        self.assertEqual(8 * size1*size2, _matrix.bytes())
        mat2 = self.make_matrices(size2, size3)
        self.assertEqual(8 * size1*size2 + 8 * size2*size3, _matrix.bytes())

        base_bytes = _matrix.bytes()
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_tile = _matrix.multiply_tile(mat1, mat2, t_size)
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        assert size1 == ret_naive.nrow == ret_tile.nrow == ret_mkl.nrow
        assert size3 == ret_naive.ncol == ret_tile.ncol == ret_mkl.ncol

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                assert ret_naive[i,j] == ret_tile[i,j] == ret_mkl[i,j]

        self.assertEqual(base_bytes + 3 * 8 * size1*size3, _matrix.bytes())
        self.assertEqual(base_alloc + 3 * 8 * size1*size3, _matrix.allocated())
        self.assertEqual(base_dealloc, _matrix.deallocated())
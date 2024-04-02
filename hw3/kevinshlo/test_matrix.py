#!/usr/bin/env python3

import sys
import os
import timeit
import unittest

# The python module that wraps the matrix code.
import _matrix


class GradingTest(unittest.TestCase):

    def make_matrices(self, size):
        mat1 = _matrix.Matrix(size, size)
        mat2 = _matrix.Matrix(size, size)
        mat3 = _matrix.Matrix(size, size)

        for it in range(size):
            for jt in range(size):
                mat1[it, jt] = it * size + jt + 1
                mat2[it, jt] = it * size + jt + 1
                mat3[it, jt] = 0

        return mat1, mat2, mat3

    def test_basic(self):
        size = 100
        mat1, mat2, mat3, *_ = self.make_matrices(size)

        for i in [mat1.nrow, mat1.ncol, mat2.nrow, mat2.ncol, mat3.nrow, mat3.ncol]:
            self.assertEqual(size, i)

        self.assertEqual(2, mat1[0, 1])
        self.assertEqual(size + 2, mat1[1, 1])
        self.assertEqual(size * 2, mat1[1, size - 1])
        self.assertEqual(size * size, mat1[size - 1, size - 1])

        for i in range(mat1.nrow):
            for j in range(mat1.ncol):
                self.assertNotEqual(0, mat1[i, j])
                self.assertEqual(mat1[i, j], mat2[i, j])
                self.assertEqual(0, mat3[i, j])

        self.assertEqual(mat1, mat2)
        self.assertTrue(mat1 is not mat2)

    def test_match_naive_mkl(self):
        size = 100
        mat1, mat2, *_ = self.make_matrices(size)

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        for i in [mat1.nrow, mat1.ncol, mat2.nrow, mat2.ncol]:
            self.assertEqual(size, i)

        self.assertEqual(ret_naive, ret_mkl)
        self.assertNotEqual(mat1, ret_mkl)

    def test_zero(self):
        size = 100
        mat1, mat2, mat3, *_ = self.make_matrices(size)

        ret_naive = _matrix.multiply_naive(mat1, mat3)
        ret_mkl = _matrix.multiply_mkl(mat1, mat3)

        for i in [ret_naive.nrow, ret_naive.ncol, ret_mkl.nrow, ret_mkl.ncol]:
            self.assertEqual(size, i)

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                self.assertEqual(0, ret_naive[i, j])
                self.assertEqual(0, ret_mkl[i, j])

    def test_tile(self):
        size = 100
        mat1, mat2, *_ = self.make_matrices(size)

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_tile = _matrix.multiply_tile(mat1, mat2, 0)

        for i in [ret_naive.nrow, ret_naive.ncol, ret_tile.nrow, ret_tile.ncol]:
            self.assertEqual(size, i)

        self.assertEqual(ret_naive, ret_tile)
        self.assertNotEqual(mat1, ret_tile)


if __name__ == "__main__":
    unittest.main()

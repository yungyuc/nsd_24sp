import sys
import os
import timeit
import random
import pytest
import unittest

import _matrix

class testMatrix(unittest.TestCase):
    def makeMatrices(self, size):
        mat1 = _matrix.Matrix(size, size)
        mat2 = _matrix.Matrix(size, size)
        mat3 = _matrix.Matrix(size, size)

        for i in range(size):
            for j in range(size):
                mat1[i, j] = i * size + j + 1
                mat2[i, j] = j * size + i + 1
                mat3[i, j] = 0

        return mat1, mat2, mat3

    def testMatMul(self):
        m = random.randint(1, 1000)
        k = random.randint(1, 1000)
        n = random.randint(1, 1000)

        mat1 = _matrix.Matrix(m, k)
        mat2 = _matrix.Matrix(k, n)

        for i in range(m):
            for j in range(k):
                mat1[i, j] = random.randint(1, 1000)

        for i in range(k):
            for j in range(n):
                mat2[i, j] = random.randint(1, 1000)

        naive_result = _matrix.naiveMatMul(mat1, mat2)
        tiling_result = _matrix.tilingMatMul(mat1, mat2, 64)
        mkl_result = _matrix.mklMatMul(mat1, mat2)

        for i in range(m):
            for j in range(n):
                assert naive_result[i, j] == tiling_result[i, j]
                assert naive_result[i, j] == mkl_result[i, j]

    def checkTiling(self, mat1, mat2, tileSize):
        assert tileSize > 0
        tiling_result = _matrix.tilingMatMul(mat1, mat2, tileSize)
        mkl_result = _matrix.mklMatMul(mat1, mat2)

        for i in range(tiling_result.m_nrow):
            for j in range(tiling_result.m_ncol):
                assert mat1[i, j] != mkl_result[i, j]
                assert tiling_result[i, j] == mkl_result[i, j]

        nameSpace = dict(_matrix=_matrix, mat1=mat1, mat2=mat2, tileSize=tileSize)
        tiling_time = timeit.Timer("_matrix.tilingMatMul(mat1, mat2, tileSize)", globals=nameSpace)
        mkl_time = timeit.Timer("_matrix.mklMatMul(mat1, mat2)", globals=nameSpace)

        tiling_time = min(tiling_time.repeat(10, 1))
        mkl_time = min(mkl_time.repeat(10, 1))

        ratio = tiling_time / mkl_time

        return ratio, tiling_time

    def testPerformance(self):
        mat1, mat2, mat3 = self.makeMatrices(1000)
        ratio_1, tiling_time_1 = self.checkTiling(mat1, mat2, 1)
        ratio_16, tiling_time_16 = self.checkTiling(mat1, mat2, 16)
        assert ratio_16 / ratio_1 <= 0.8
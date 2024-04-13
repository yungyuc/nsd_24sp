import _matrix
import random
import sys
import timeit

def makeMatrices():
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

    return mat1, mat2

def testPerformance(tileSize):
    mat1, mat2 = makeMatrices()

    nameSpace = dict(_matrix=_matrix, mat1=mat1, mat2=mat2, tileSize=tileSize)
    naive_time = timeit.Timer("_matrix.naiveMatMul(mat1, mat2)", globals=nameSpace)
    tiling_time = timeit.Timer("_matrix.tilingMatMul(mat1, mat2, tileSize)", globals=nameSpace)
    mkl_time = timeit.Timer("_matrix.mklMatMul(mat1, mat2)", globals=nameSpace)

    with open('performance.txt', 'w') as file:
        file.write('The time for each method is the average of 10 executions\n')
        file.write(f'm={mat1.m_nrow}, k={mat1.m_ncol}, n={mat2.m_ncol}\n')
        avg_naive_time = sum(naive_time.repeat(10, 1)) / 10
        file.write(f'Naive takes {avg_naive_time} seconds.\n')
        avg_tiling_time = sum(tiling_time.repeat(10, 1)) / 10
        file.write(f'Tiling takes {avg_tiling_time} seconds.\n')
        avg_mkl_time = sum(mkl_time.repeat(10, 1)) / 10
        file.write(f'MKL takes {avg_mkl_time} seconds.\n')
        file.write(f'Ratio of Tiling over Naive (tileSize={tileSize}): {avg_tiling_time/avg_naive_time}.\n')
        file.write(f'Ratio of MKL over Naive: {avg_mkl_time/avg_naive_time}.\n')

if __name__ == '__main__':
    testPerformance(tileSize=16)
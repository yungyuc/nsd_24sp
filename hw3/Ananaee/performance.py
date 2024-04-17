import sys
import timeit
import _matrix

class Writer:

    def __init__(self, streams):

        self.streams = streams

    def write(self, msg):

        for stream in self.streams:

            stream.write(msg)


def benchmark():

    setup = '''
import _matrix
size = 1000
mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)
for i in range(size):
    for j in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
'''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile64 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 64)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as fobj:

        w = Writer([sys.stdout, fobj])

        w.write(f'Start multiply_naive (repeat={repeat}), take min = ')
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile (repeat={repeat}), take min = ')
        tile64sec = minsec = min(tile64.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_mkl (repeat={repeat}), take min = ')
        mklsec = minsec = min(mkl.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write('MKL speed-up over naive: %g x\n' % (naivesec/mklsec))
        w.write('Tile speed-up over naive: %g x\n' % (tile64sec/mklsec))

if __name__ == '__main__':
    benchmark()
import _vector
import math
import unittest

class TestVectorAngle(unittest.TestCase):
    def test_zero_angle(self):
        self.assertAlmostEqual(_vector.calculate_angle((1, 0), (1, 0)), 0)

    def test_right_angle(self):
        self.assertAlmostEqual(_vector.calculate_angle((1, 0), (0, 1)), math.pi / 2)

    def test_acute_angle(self):
        self.assertAlmostEqual(_vector.calculate_angle((1, 0), (1, 1)), math.pi / 4)

    def test_obtuse_angle(self):
        self.assertAlmostEqual(_vector.calculate_angle((1, 0), (-1, 1)), 3 * math.pi / 4)

if __name__ == '__main__':
    unittest.main()

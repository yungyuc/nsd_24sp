#!/usr/bin/env python3

import _vector

import unittest
import numpy as np


class AngleTC(unittest.TestCase):
    eps = 1e-5

    @staticmethod
    def golden(a: list[float], b: list[float]):
        return np.arccos(np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b)))

    def test_zero_length(self):  # zero-length 2-vector (invalid input).
        a, b = [], []
        with self.assertRaisesRegex(ValueError, "vector size not equals to 2"):
            _vector.angle(a, b)

    def test_zero_angle(self):  # 0-deg
        a, b = [1.0, 1.0], [1.0, 1.0]
        assert abs(_vector.angle(a, b) - self.golden(a, b)) < self.eps

    def test_right_angle(self):  # 90-deg
        a, b = [1.0, 1.0], [-1.0, 1.0]
        assert abs(_vector.angle(a, b) - self.golden(a, b)) < self.eps

    def test_other_angle(self):  # one other angle
        a, b = [1.0, 2.0], [-1.0, 2.0]
        assert abs(_vector.angle(a, b) - self.golden(a, b)) < self.eps


if __name__ == "__main__":
    suite = unittest.TestLoader().loadTestsFromTestCase(AngleTC)
    unittest.TextTestRunner().run(suite)

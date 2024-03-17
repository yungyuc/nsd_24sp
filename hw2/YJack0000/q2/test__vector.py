import _vector
import math
import pytest


def test_zero_length():
    v1 = (0.0, 0.0)
    v2 = (-1.0, 0.0)
    assert math.isnan(_vector.calculate_angle(v1, v1))
    assert math.isnan(_vector.calculate_angle(v1, v2))


def test_zero_angle():
    v1 = (1.0, 0.0)
    v2 = (1.0, 0.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(0.0, rel=1e-5)


def test_right_angle():
    v1 = (1.0, 0.0)
    v2 = (0.0, 1.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(math.pi / 2, rel=1e-5)


def test_other_angle():
    v1 = (1.0, 0.0)
    v2 = (1.0, 1.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(math.pi / 4, rel=1e-5)

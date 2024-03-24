import _vector
import math
import pytest


def test_zero_length():
    v1 = (0.0, 0.0)
    v2 = (-1.0, 0.0)
    assert math.isnan(_vector.angle_of_vector(v1, v1))
    assert math.isnan(_vector.angle_of_vector(v1, v2))


def test_zero_angle():
    v1 = (1.1, 1.1)
    v2 = (1100.0, 1100.0)
    assert _vector.angle_of_vector(v1, v2) == pytest.approx(0.0, rel=1e-6)


def test_angles():
    v1, v2 = (2, 0), (math.sqrt(3), 1)
    assert _vector.angle_of_vector(v1, v2) == pytest.approx(math.pi / 6, rel=1e-6) # degree 30

    v1, v2 = (1, 0), (2, 2)
    assert _vector.angle_of_vector(v1, v2) == pytest.approx(math.pi / 4, rel=1e-6) # degree 45

    v1, v2 = (1, 0), (1, math.sqrt(3))
    assert _vector.angle_of_vector(v1, v2) == pytest.approx(math.pi / 3, rel=1e-6) # degree 60

    v1, v2 = (1, 0), (0, 1)
    assert _vector.angle_of_vector(v1, v2) == pytest.approx(math.pi / 2, rel=1e-6) # degree 90

    v1, v2 = (1, 0), (-1, 0)
    assert _vector.angle_of_vector(v1, v2) == pytest.approx(math.pi, rel=1e-6) # degree 180
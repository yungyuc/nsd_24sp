import pytest
import math
import _vector

def test_zero_len_v1():
    v1 = (0, 0)
    v2 = (1, 0)
    angle = _vector.get_angle(v1, v2)
    assert math.isnan(angle), "Should return NaN if v1 is a zero-length vector."

def test_zero_len_v2():
    v1 = (1, 0)
    v2 = (0, 0)
    angle = _vector.get_angle(v1, v2)
    assert math.isnan(angle), "Should return NaN if v2 is a zero-length vector."

def test_zero_len_v1v2():
    v1 = (0, 0)
    v2 = (0, 0)
    angle = _vector.get_angle(v1, v2)
    assert math.isnan(angle), "Should return NaN if both v1 and v2 are zero-length vectors."

def test_parallel():
    v1 = (1, 1)
    v2 = (3, 3)
    angle = _vector.get_angle(v1, v2)
    assert math.isclose(angle, 0, abs_tol=1e-4), "Angle between two parallel vectors should be close to 0."

def test_orthogonal():
    v1 = (1, 0)
    v2 = (0, -1)
    angle = _vector.get_angle(v1, v2)
    assert math.isclose(angle, math.pi/2, abs_tol=1e-4), "Angle between two orthogonal vectors should be close to pi/2."


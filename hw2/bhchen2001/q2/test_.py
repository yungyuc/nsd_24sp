import pytest
from math import pi
from _vector import _vec_angle

def deg2rad(deg):
    return deg / 180 * pi

def approx_eq(a, b, tol=1e-6):
    return abs(a - b) < tol

'''
Test for zero-length vector
'''
@pytest.mark.parametrize("v1, v2, expected", [
    ([0, 0], [0, 0], -1),
    ([0, 0], [1, 0], -1),
    ([0, 0], [0, 1], -1)
])
def test_zero_length_vector(v1, v2, expected):
    assert _vec_angle(v1, v2) == expected

'''
Test for zero angle
'''
@pytest.mark.parametrize("v1, v2, expected", [
    ([1, 0], [1, 0], 0),
    ([1, 2], [100, 200], 0)
])
def test_zero_angle(v1, v2, expected):
    assert _vec_angle(v1, v2) == expected

'''
Test for right angle
'''
@pytest.mark.parametrize("v1, v2, expected", [
    ([1, 0], [0, 1], deg2rad(90)),
    ([1, 2], [2, -1], deg2rad(90))
])
def test_right_angle(v1, v2, expected):
    assert _vec_angle(v1, v2) == expected

'''
Test for obtuse angle
'''
@pytest.mark.parametrize("v1, v2, expected", [
    ([1, 0], [-1, 0], deg2rad(180.0)),
    ([1, 2], [-1, -2], deg2rad(180.0))
])
def test_obtuse_angle(v1, v2, expected):
    assert approx_eq(_vec_angle(v1, v2), expected)
    # assert _vec_angle(v1, v2) == expected
import _vector
import pytest
import math

def test_zero_length_vector_first():
    vec1 = (0.0, 0.0)
    vec2 = (1.0, 0.0)
    angle = _vector.calculateAngle(vec1, vec2)
    assert math.isnan(angle), "Angle calculation should return NaN for a zero-length vector"

def test_zero_length_vector_second():
    vec1 = (1.0, 0.0)
    vec2 = (0.0, 0.0)
    angle = _vector.calculateAngle(vec1, vec2)
    assert math.isnan(angle), "Angle calculation should return NaN for a zero-length vector"

def test_zero_angle():
    vec1 = (1.0, 0.0)
    vec2 = (10.0, 0.0)
    angle = _vector.calculateAngle(vec1, vec2)
    assert math.isclose(angle, 0.0, abs_tol=1e-5), "Angle between vectors in the same direction should be 0"

def test_right_angle():
    vec1 = (1.0, 0.0)
    vec2 = (0.0, 1.0)
    angle = _vector.calculateAngle(vec1, vec2)
    assert math.isclose(angle, math.pi / 2, abs_tol=1e-5), "Angle between perpendicular vectors should be pi/2"

def test_acute_angle():
    vec1 = (1.0, 0.0)
    vec2 = (1.0, 1.0)
    angle = _vector.calculateAngle(vec1, vec2)
    expected_angle = math.pi / 4
    assert math.isclose(angle, expected_angle, abs_tol=1e-5), "Angle between (1,0) and (1,1) should be pi/4"

def test_obtuse_angle():
    vec1 = (-1.0, 0.0)
    vec2 = (1.0, 1.0)
    angle = _vector.calculateAngle(vec1, vec2)
    expected_angle = 3 * math.pi / 4
    assert math.isclose(angle, expected_angle, abs_tol=1e-5), "Angle between (-1,0) and (1,1) should be 3*pi/4"

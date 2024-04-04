import pytest
import math
import _vector

def test_same_direction():
    angle = _vector.calculate_angle(1, 0, 2, 0)
    assert math.isclose(angle, 0.0, rel_tol=1e-9)

def test_orthogonal_vectors():
    angle = _vector.calculate_angle(0, 1, 1, 0)
    assert math.isclose(angle, math.pi / 2, rel_tol=1e-9)

def test_opposite_direction():
    angle = _vector.calculate_angle(1, 0, -1, 0)
    assert math.isclose(angle, math.pi, rel_tol=1e-9)

def test_zero_length_vector_a():
    angle = _vector.calculate_angle(0, 0, 1, 0)
    assert math.isnan(angle)

def test_zero_length_vector_b():
    angle = _vector.calculate_angle(1, 0, 0, 0)
    assert math.isnan(angle)

def test_both_vectors_zero_length():
    angle = _vector.calculate_angle(0, 0, 0, 0)
    assert math.isnan(angle)

def test_close_to_limits():
    # Testing with vectors very close to being in the same or opposite direction
    epsilon = 1e-10
    angle_same_close = _vector.calculate_angle(1, 0, 1, epsilon)
    angle_opposite_close = _vector.calculate_angle(1, 0, -1, epsilon)
    assert math.isclose(angle_same_close, 0.0, rel_tol=1e-9)
    assert math.isclose(angle_opposite_close, math.pi, rel_tol=1e-9)

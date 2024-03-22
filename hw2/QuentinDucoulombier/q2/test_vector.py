import pytest
import _vector
import math

# Basic geometric relationships
def test_parallel_positive_direction():
    angle = _vector.calculate_angle(1, 0, 1, 0)
    assert math.isclose(angle, 0, rel_tol=1e-9)

def test_parallel_negative_direction():
    angle = _vector.calculate_angle(1, 0, -1, 0)
    assert math.isclose(angle, math.pi, rel_tol=1e-9)

def test_perpendicular_vectors():
    angle = _vector.calculate_angle(1, 0, 0, 1)
    assert math.isclose(angle, math.pi / 2, rel_tol=1e-9)

def test_perpendicular_negative_components():
    angle = _vector.calculate_angle(-1, 0, 0, -1)
    assert math.isclose(angle, math.pi / 2, rel_tol=1e-9)

# Special cases
def test_identical_vectors_angle_zero():
    angle = _vector.calculate_angle(1, 1, 1, 1)
    assert math.isclose(angle, 0, rel_tol=1e-9)

def test_opposite_vectors_angle_pi():
    angle = _vector.calculate_angle(1, 1, -1, -1)
    assert math.isclose(angle, math.pi, rel_tol=1e-8)

def test_zero_length_first_vector():
    angle = _vector.calculate_angle(0, 0, 1, 1)
    assert math.isnan(angle)

def test_zero_length_second_vector():
    angle = _vector.calculate_angle(1, 1, 0, 0)
    assert math.isnan(angle)

def test_zero_length_both_vectors():
    angle = _vector.calculate_angle(0, 0, 0, 0)
    assert math.isnan(angle)

# Angles other than basic geometric relationships
def test_acute_angle_between_vectors():
    angle = _vector.calculate_angle(1, 2, 2, 3)
    assert angle > 0 and angle < math.pi / 2

def test_obtuse_angle_between_vectors():
    angle = _vector.calculate_angle(1, 0, -1, 1)
    assert angle > math.pi / 2 and angle < math.pi

def test_quarter_pi_angle_first_quadrant():
    angle = _vector.calculate_angle(1, 1, 1, 0)
    assert math.isclose(angle, math.pi / 4, rel_tol=1e-9)

def test_quarter_pi_angle_second_quadrant():
    angle = _vector.calculate_angle(1, 1, 0, 1)
    assert math.isclose(angle, math.pi / 4, rel_tol=1e-9)


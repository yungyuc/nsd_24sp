import _vector
import pytest
import math

def test_radian_angle():
    # Test case with valid vectors
    angle = _vector.radian_angle((1.0, 0.0), (0.0, 1.0))
    assert abs(angle -math.pi / 2) < 1e-9

    # Test case with oposite direction
    angle = _vector.radian_angle((1.0, 0.0), (-1.0, 0.0))
    assert abs(angle - math.pi) < 1e-9

    # Test case with zero vector
    angle = _vector.radian_angle((0.0, 0.0), (1.0, 1.0))
    # assert angle == -1
    assert abs(angle + 1) < 1e-9

    # Test case with zero angle
    angle = _vector.radian_angle((0.0, 1.0), (0.0, 1.0))
    # assert angle == -1
    assert abs(angle) < 1e-9

    # Test case with zero lenght 2 vector
    angle = _vector.radian_angle((0.0, 0.0), (0.0, 0.0))
    assert abs(angle + 1) < 1e-9



if __name__ == "__main__":
    test_radian_angle()
 
import pytest
from _vector import Vector2D


# =============================================================================
# Requirements: 
# Test for zero-length 2-vector (invalid input).
# Test for zero angle.
# Test for right angle (90-deg).
# Test for one other angle.
# =============================================================================

# Test for zero-length 2-vector (invalid input)
def testZeroLengthVector():
    with pytest.raises(ValueError):
        v1, v2 = Vector2D(0, 0), Vector2D(0, 0)
        v1.angleBetween(v2)
        

# Test for zero angle
def testZeroAngle():
    v1, v2 = Vector2D(1, 0), Vector2D(1, 0)
    assert v1.angleBetween(v2) == 0.0

# Test for right angle (90-deg)
def testRightAngle():
    v1, v2 = Vector2D(1, 0), Vector2D(0, 1)
    assert v1.angleBetween(v2) == pytest.approx(1.5708, abs=1e-4)

# Test for one other angle
def testOtherAngle():
    v1, v2 = Vector2D(1, 0), Vector2D(1, 1)
    assert v1.angleBetween(v2) == pytest.approx(0.7853, abs=1e-4)

if __name__ == "__main__":
    pytest.main([__file__])

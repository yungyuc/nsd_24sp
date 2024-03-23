from _vector import angle
import pytest
import math

# Function to calculate angle between two vectors
def dot_product(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1]

def vector_magnitude(v):
    return math.sqrt(v[0]**2 + v[1]**2)

def angle_between_vectors(v1, v2):
    dot = dot_product(v1, v2)
    mag1 = vector_magnitude(v1)
    mag2 = vector_magnitude(v2)
    cos_theta = dot / (mag1 * mag2)

    # Ensure cos_theta is within [-1, 1] to avoid math domain errors
    cos_theta = max(min(cos_theta, 1.0), -1.0)

    # Calculate the angle in radians
    theta_rad = math.acos(cos_theta)
    
    return theta_rad

class TestAngle:
    @pytest.mark.parametrize(
        ("a", "b", "c", "d"),
        [
            (3, 1, 4, 2),
            (-1, 2, 2, -5),
            (0, -3, 4.2, 0),
            (1, 1, 3, 3),
        ],
    )
    def test(self, a, b, c, d):
        assert angle(a, b, c, d) == pytest.approx(angle_between_vectors([a, b], [c, d]))

class TestAngleVauleError:
    @pytest.mark.parametrize(
        ("a", "b", "c", "d"),
        [
            (1, 1, 0, 0),
            (0, 0, 1, 1)
        ],
    )
    def test(self, a, b, c, d):
        with pytest.raises(ValueError):
            angle(a, b, c, d)

if __name__ == "__main__":
    print(angle_between_vectors([1, 1], [3, 3]))
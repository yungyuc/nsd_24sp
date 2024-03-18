import pytest
from angle import calculate_angle
import math
import random
def test_zero_len():
    with pytest.raises(ValueError):
        calculate_angle([0, 0], [0, 0])
    with pytest.raises(ValueError):
        calculate_angle([0, 0], [0, 1])
    with pytest.raises(ValueError):
        calculate_angle([0, 0], [1, 0])
    with pytest.raises(ValueError):
        calculate_angle([0, 1], [0, 0])
    with pytest.raises(ValueError):
        calculate_angle([1, 0], [0, 0])

def test_zero_angle():
    x, y, ratio = 1, 1, 2
    assert calculate_angle([x, y], [x*ratio, y*ratio]) == 0
    assert calculate_angle([x*ratio, y*ratio], [x, y]) == 0
    x, y, ratio = 1, 1, 1
    assert calculate_angle([x, y], [x*ratio, y*ratio]) == 0
    assert calculate_angle([x*ratio, y*ratio], [x, y]) == 0
    x, y, ratio = 3.8, 4.5, 0.5
    assert calculate_angle([x, y], [x*ratio, y*ratio]) == 0
    assert calculate_angle([x*ratio, y*ratio], [x, y]) == 0
    x, y, ratio = -3.8, 4.5, -1.5
    assert calculate_angle([x, y], [x*ratio, y*ratio]) == 0
    assert calculate_angle([x*ratio, y*ratio], [x, y]) == 0

def test_angle():
    x1, y1, x2, y2 = 2, 0, math.sqrt(3), 1
    assert calculate_angle([x1, y1], [x2, y2]) == pytest.approx(math.pi/6)# 30
    x1, y1, x2, y2 = 1, 0, 2, 2
    assert calculate_angle([x1, y1], [x2, y2]) == pytest.approx(math.pi/4)# 45
    x1, y1, x2, y2 = 1, 0, 1, math.sqrt(3)
    assert calculate_angle([x1, y1], [x2, y2]) == pytest.approx(math.pi/3)# 60
    x1, y1, x2, y2 = 1, 0, 0, 1
    assert calculate_angle([x1, y1], [x2, y2]) == pytest.approx(math.pi/2)# 90
    x1, y1, x2, y2 = 1, 0, -1, 0
    assert calculate_angle([x1, y1], [x2, y2]) == pytest.approx(math.pi)# 180
    

    
    
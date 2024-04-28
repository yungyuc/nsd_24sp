import torch
from torch.nn.modules.utils import _pair

class MyConv2d(torch.nn.modules.conv._ConvNd): 
    def __init__(self, in_channels, out_channels, kernel_size, stride=1,
                 padding=0, dilation=1, groups=1,
                 bias=True, padding_mode='zeros'):
        pass
    
    def conv2d_forward(self, input, weight):
        pass
    
    def forward(self, input):
        pass
    
def myconv2d(input, weight, bias=None, stride=1, padding=0, dilation=1, groups=1):
    pass



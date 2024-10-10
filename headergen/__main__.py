import sys
from json2daisy import generate_header
import types
import json
import os

if len(sys.argv) != 2:
    print("Example:", sys.argv[0], "earth")
    exit(0)

def copy_func(f, name=None):
    '''
    return a function with same code, globals, defaults, closure but run in this directory
    '''
    f.__globals__['__file__'] = __file__
    fn = types.FunctionType(f.__code__, f.__globals__, f.__name__, f.__defaults__, f.__closure__)
    return fn

if __name__ == "__main__":
    # this is incredibly stupid, but they way they wrote the library makes this neccesary
    genh = copy_func(generate_header)

    # run buisness as usual
    root = os.path.dirname(sys.argv[0])
    device = os.path.join(root, sys.argv[1] + ".json")

    with open(device, 'rb') as file:
        daisy_description = json.load(file)
        header = genh(daisy_description)[0]

    with open('board.h', 'w') as file:
        file.write(header)
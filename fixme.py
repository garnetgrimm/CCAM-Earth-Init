'''
This python script is used to fix the broken cmake file in DaisySP-LGPL
This can be deleted after my PR has merged https://github.com/electro-smith/DaisySP-LGPL/pull/5
I *could* just fork each of the repos and point to those, but I'd rather get it fixed upstream ;)
'''

broken_cmake = 'DaisySP/DaisySP-LGPL/CMakeLists.txt'

with open(broken_cmake) as file:
    lines = file.readlines()

lines = [line.replace('../../Source', '../Source') for line in lines]

with open(broken_cmake, 'w') as file:
    for line in lines:
        file.write(line)
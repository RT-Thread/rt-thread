#!/usr/bin/env python
import sys
from timeit import Timer
from stations import locator

call = sys.argv[1]
print repr(call)
D = {}

for line in file('stations.dat'):
    c, l = [x.strip() for x in line.split(',')]
    D[c] = l

def test1(c):
    return D[c]

print repr(test1(call))
t = Timer("test1(%r)" % call, "from __main__ import test1")
print t.timeit()

# -----

def test2(c):
    return locator(c)

print repr(test2(call))
t = Timer("test2(%r)" % call, "from __main__ import test2")
print t.timeit()

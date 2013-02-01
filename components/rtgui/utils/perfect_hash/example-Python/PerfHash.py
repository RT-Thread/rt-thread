#!/usr/bin/env python
"""
This example shows how to use the class PerfHash.

This class is designed for creating perfect hash tables at run time,
which should be avoided, in particulat inserting new keys is
prohibitively expensive since a new perfect hash table needs to be
constructed.  However, this class can be usefull for testing.

For practical programming purposes in Python the class PerfHash
should never be used because Python's built-in dictionary is very
efficient and always faster than PerfHash.
"""

import sys

sys.path.append('..')
from perfect_hash import PerfHash


month = dict(zip('jan feb mar apr may jun jul aug sep oct mov dec'.split(),
                 range(1, 13)))

d = PerfHash(month)


for m in month:
    assert month[m] == d[m]

d[True] = False

assert d[True] == False

for i in xrange(10):  # very expensive
    d[i] = 2*i*i + 3*i -7

assert d[4] == 37


print 'OK'

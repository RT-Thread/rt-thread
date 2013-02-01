#!/usr/bin/env python
"""
This example shows how to use the function generate_hash.

generate_hash(kdic, Hash)

returns hash functions f1 and f2, and G for a perfect minimal hash.
Input is dictionary 'kdic' with the keys and desired hash values.
'Hash' is a random hash function generator, that means Hash(N) returns a
returns a random hash function which returns hash values from 0..N-1.
"""

import sys
import random, string

sys.path.append('..')
from perfect_hash import generate_hash



month = dict(zip('jan feb mar apr may jun jul aug sep oct mov dec'.split(),
                 range(1, 13)))

def mkRandHash(N):
    """
    Return a random hash function which returns hash values from 0..N-1.
    """
    junk = "".join(random.choice(string.letters + string.digits)
                   for i in xrange(10))
    return lambda key: hash(junk + str(key)) % N


f1, f2, G = generate_hash(month, mkRandHash)

for k, h in month.items():
    assert h == ( G[f1(k)] + G[f2(k)] ) % len(G)

print 'OK'

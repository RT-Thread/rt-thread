#!/usr/bin/env python

# ./mk_rnd_keys.py 10000 | sort | uniq | shuf >keywords.txt

import sys
from random import choice, randint
from string import digits, uppercase, lowercase

def key():
    return ''.join(choice(uppercase + lowercase + digits)
                   for i in xrange(randint(6, 20)))

N = int(sys.argv[1])


for n in xrange(N):
    print key()

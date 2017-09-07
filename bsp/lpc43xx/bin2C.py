#!/bin/env python

import sys

fi = open(sys.argv[1], 'rb')
fo = open(sys.argv[2], 'wb')

idx = 0
for i in fi.read():
    idx += 1
    fo.write('0x%02x, ' % ord(i))
    if idx % 16 == 0:
        fo.write('\n')
fo.write('\n')

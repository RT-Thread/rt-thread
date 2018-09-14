#!/usr/bin/env python

import struct
import sys
import time
import os
import re

def main():
    with open('blocks/config') as file:
        s = struct.unpack('<LLLL', file.read())
        print 'read_size: %d' % s[0]
        print 'prog_size: %d' % s[1]
        print 'block_size: %d' % s[2]
        print 'block_size: %d' % s[3]

    print 'real_size: %d' % sum(
        os.path.getsize(os.path.join('blocks', f))
        for f in os.listdir('blocks') if re.match('\d+', f))

    with open('blocks/stats') as file:
        s = struct.unpack('<QQQ', file.read())
        print 'read_count: %d' % s[0]
        print 'prog_count: %d' % s[1]
        print 'erase_count: %d' % s[2]

    print 'runtime: %.3f' % (time.time() - os.stat('blocks').st_ctime)

if __name__ == "__main__":
    main(*sys.argv[1:])

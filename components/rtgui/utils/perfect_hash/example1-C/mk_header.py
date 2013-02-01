#!/usr/bin/env python

for line in file('states.dat'):
    line = line.strip()
    if line.startswith('#'):
        continue
    
    row = tuple(entry.strip() for entry in line.split('|'))

    print '  { "%s", "%s", %s },' % row 

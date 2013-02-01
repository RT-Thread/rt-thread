#!/usr/bin/env python
import re

def convert(line, head = False):
    pat = re.compile(r'([$]\S*)')
    line = pat.sub(r'<code>\1</code>', line)
    
    row = [x.strip() for x in line.split('|')]
    fmt = '  <tr><td>%s</td><td>%s</td></tr>'
    if head:
        fmt = fmt.replace('td', 'th')
    print fmt % tuple(row)


f = file('parameters.txt')

print '<table>'
convert(f.readline(), head = True)
f.readline()
for line in f:
    convert(line)
print '</table>'

import re
import sys

fsrc = "rtthread.dll"
fname ="rtthread.def"
prefix = "__vs_rtm_"

if len(sys.argv) >= 2:
    fsrc = sys.argv[1]
    fname = sys.argv[2]

#restr = r"__vs_rtm_.*?\0"
restr = prefix + r".*?\0"
s = open(fsrc, 'rb').read()
l = re.findall(restr, s, re.S)
lines = [i[len(prefix):-1] for i in l]

s = '\n'.join(lines)

fout = open(fname, 'w')
fout.write('EXPORTS\n')
fout.write('main\n')
fout.write(s)

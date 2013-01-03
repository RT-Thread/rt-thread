import os
import sys

BSP_ROOT = '../bsp'

unsupported = """
bf533
dev3210
jz47xx
ls1bdev
m16c62p
microblaze
mini4020
nuc140
nios_ii
pic32ethernet
upd70f3454
wh44b0
xplorer4330
"""

failed = """
stm32f0x
"""

avr = """
avr32uc3b0
"""

ppc = """
taihu
"""

x86 = """
simulator
x86
"""

arm = """
at91sam9260
efm32
lm3s8962
lm3s9b9x
lm4f232
lpc1114
lpc122x
lpc176x
lpc178x
lpc2148
lpc2478
mb9bf500r
mb9bf506r
mini2440
sam7s
sam7x
stm32f107
stm32f10x
stm32f20x
stm32f40x
""".split()

for item in arm:
    project_dir = os.path.join(BSP_ROOT, item)
    if os.path.isfile(os.path.join(project_dir, 'SConstruct')):
        if os.system('scons --directory=' + project_dir) != 0:
            print 'build failed!!'
            sys.exit(1)

sys.exit(0)

import os
import sys

bsp_to_cpu = {
    'bf533': 'unknown',
    'dev3210': 'unknown',
    'jz47xx': 'unknown',
    'ls1bdev': 'unknown',
    'm16c62p': 'unknown',
    'microblaze': 'unknown',
    'mini4020': 'unknown',
    'nuc140': 'unknown',
    'nios_ii': 'unknown',
    'pic32ethernet': 'unknown',
    'upd70f3454': 'unknown',
    'wh44b0': 'unknown',
    'xplorer4330': 'unknown',
    'avr32uc3b0': 'avr',
    'taihu': 'ppc',
    'simulator': 'x86',
    'x86': 'x86',
    'at91sam9260': 'arm',
    'efm32': 'arm',
    'lm3s8962': 'arm',
    'lm3s9b9x': 'arm',
    'lm4f232': 'arm',
    'lpc1114': 'arm',
    'lpc122x': 'arm',
    'lpc176x': 'arm',
    'lpc178x': 'arm',
    'lpc2148': 'arm',
    'lpc2478': 'arm',
    'mb9bf500r': 'arm',
    'mb9bf506r': 'arm',
    'mini2440': 'arm',
    'sam7s': 'arm',
    'sam7x': 'arm',
    'stm32f0x': 'arm',
    'stm32f107': 'arm',
    'stm32f10x': 'arm',
    'stm32f20x': 'arm',
    'stm32f40x': 'arm',
}

results = {
    'success': [],
    'fail': [],
    'ignore': []
}

fail = False

BSP_ROOT = '../bsp'

for bsp,cpu in bsp_to_cpu.iteritems():
    project_dir = os.path.join(BSP_ROOT, bsp)
    if os.getenv('RTT_CPU') == cpu and os.path.isfile(os.path.join(project_dir, 'SConstruct')):
        if os.system('scons --directory=' + project_dir) != 0:
            results['fail'].append(bsp)
            fail = True
        else:
            results['success'].append(bsp)
    else:
        results['ignore'].append(bsp)

for result,bsp_list in results.iteritems():
    print "## {0}: {1}\n".format(result, len(bsp_list))
    for bsp in bsp_list:
        print "* " + bsp

if fail:
    sys.exit(1)
else:
    sys.exit(0)

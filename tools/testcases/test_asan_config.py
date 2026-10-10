#!/usr/bin/env python3
# Copyright (c) 2006-2026, RT-Thread Development Team
# SPDX-License-Identifier: Apache-2.0

"""Check ASan lock dependencies using the repository's real Kconfig tree.

Run with: python -m unittest discover -s tools/testcases -p test_asan_config.py
Requires kconfiglib, also used by the configuration tools.
"""

import itertools
import os
from pathlib import Path
import unittest

import kconfiglib


class AsanConfigTest(unittest.TestCase):
    def test_heap_lock_combinations(self):
        bsp = Path(__file__).resolve().parents[2] / 'bsp/qemu-vexpress-a9'
        previous = Path.cwd()
        try:
            os.chdir(bsp)
            for smp, mutex, isr in itertools.product((0, 2), repeat=3):
                with self.subTest(smp=smp, mutex=mutex, isr=isr):
                    config = kconfiglib.Kconfig('Kconfig', warn=False)
                    # Start without optional subsystems that select mutexes.
                    for symbol in config.unique_defined_syms:
                        if symbol.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                            symbol.set_value(0)
                    for name in ('RT_USING_SMALL_MEM',
                                 'RT_USING_SMALL_MEM_AS_HEAP'):
                        config.syms[name].set_value(2)
                    for name, value in (('RT_USING_SMP', smp),
                                        ('RT_USING_MUTEX', mutex),
                                        ('RT_USING_HEAP_ISR', isr)):
                        config.syms[name].set_value(value)
                        self.assertEqual(config.syms[name].tri_value, value)
                    config.syms['RT_USING_ASAN'].set_value(2)
                    expected = 2 if not smp or mutex or isr else 0
                    self.assertEqual(config.syms['RT_USING_ASAN'].tri_value,
                                     expected)
        finally:
            os.chdir(previous)


if __name__ == '__main__':
    unittest.main()

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import importlib.util
import os
import unittest


MODULE_PATH = os.path.join(os.path.dirname(__file__), "..", "gen_ksym.py")
SPEC = importlib.util.spec_from_file_location("gen_ksym", MODULE_PATH)
GEN_KSYM = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GEN_KSYM)


class GenKsymTest(unittest.TestCase):
    def test_parse_local_global_weak_and_aliases(self):
        sections = """\
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000080  00001000  00001000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000010  00002000  00002000  000000b4  2**2
                  CONTENTS, ALLOC, LOAD, DATA
"""
        symbols = """\
SYMBOL TABLE:
00001000 l    F .text 00000010 static_func
00001000 g    F .text 00000010 public_alias
00001020 w    F .text 00000020 weak_func
00002000 g    O .data 00000004 data_object
00000000 g    F *UND* 00000000 undefined_func
"""

        executable = GEN_KSYM.parse_executable_sections(sections)
        parsed = GEN_KSYM.parse_symbols(symbols, executable)

        self.assertEqual(parsed, [
            (0x1000, 0x10, "public_alias", ".text"),
            (0x1020, 0x20, "weak_func", ".text"),
        ])

    def test_function_at_zero_is_kept(self):
        sections = """\
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000020  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
"""
        symbols = """\
SYMBOL TABLE:
00000000 l    F .text 00000010 function_at_zero
"""

        executable = GEN_KSYM.parse_executable_sections(sections)
        parsed = GEN_KSYM.parse_symbols(symbols, executable)

        self.assertEqual(parsed, [
            (0x0, 0x10, "function_at_zero", ".text"),
        ])

    def test_arm32_elf_detection(self):
        for architecture in ("arm", "armv7", "armv7e-m"):
            file_text = ("file format elf32-littlearm\n"
                         "architecture: %s, flags 0x0:" % architecture)
            self.assertTrue(GEN_KSYM.is_32bit_arm_elf(file_text))

        self.assertFalse(GEN_KSYM.is_32bit_arm_elf(
            "file format elf64-littleaarch64\n"
            "architecture: aarch64, flags 0x0:"))

    def test_zero_size_uses_same_section_boundary(self):
        symbols = GEN_KSYM.resolve_symbol_sizes([
            (0x1000, 0, "first", ".text"),
            (0x1020, 0, "middle", ".text"),
            (0x1040, 0, "last_text", ".text"),
            (0x8000, 0x30, "ramfunc", ".ramfunc"),
        ])

        self.assertEqual(symbols, [
            (0x1000, 0x20, "first"),
            (0x1020, 0x20, "middle"),
            (0x1040, 0, "last_text"),
            (0x8000, 0x30, "ramfunc"),
        ])

    def test_generated_table_uses_relative_addresses_and_size(self):
        source = GEN_KSYM.generate_source(
            [(0x1000, 0x10, "first"), (0x1020, 0, "last")], 0x1000)

        self.assertIn("rt_ksym_first_addr = 0x1000", source)
        self.assertIn("{0x20, 6, 0x0}", source)
        self.assertIn("{0x0, 0, 0x10}", source)

    def test_arm_thumb_addresses_are_canonicalized(self):
        symbols = GEN_KSYM.parse_symbols(
            "00001001 l F .text 00000010 thumb_func\n",
            {".text": (".text", 0x1000, 0x20)},
            normalize_arm=True)

        self.assertEqual(symbols[0][0], 0x1000)


if __name__ == "__main__":
    unittest.main()

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
"""Generate the compact RT-Thread kernel function symbol table."""

import argparse
import os
import re
import subprocess
import sys


UINT32_MAX = 0xffffffff


def is_32bit_arm_elf(file_text):
    """Return whether objdump reports a 32-bit ARM ELF image."""
    return bool(re.search(r"file format\s+elf32-(?:little|big)arm\b",
                          file_text))


def _run_objdump(objdump, option, elf):
    try:
        result = subprocess.run([objdump, option, elf], check=True,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                universal_newlines=True)
    except (OSError, subprocess.CalledProcessError) as exc:
        message = getattr(exc, "stderr", "") or str(exc)
        raise RuntimeError("failed to run %s %s: %s" %
                           (objdump, option, message.strip())) from exc
    return result.stdout


def parse_executable_sections(text):
    """Return executable section ranges from GNU objdump -h output."""
    sections = {}
    current = None

    for line in text.splitlines():
        match = re.match(
            r"^\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+"
            r"([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+",
            line)
        if match:
            name = match.group(1)
            size = int(match.group(2), 16)
            address = int(match.group(3), 16)
            current = (name, address, size)
            continue

        if current and "CODE" in line and "ALLOC" in line:
            sections[current[0]] = current
            current = None

    return sections


def parse_symbols(text, executable_sections, normalize_arm=False):
    """Parse function symbols from GNU objdump -t output."""
    symbols = []

    for line in text.splitlines():
        fields = line.split()
        if len(fields) < 6:
            continue
        if not re.fullmatch(r"[0-9a-fA-F]+", fields[0]):
            continue
        if fields[2] != "F" or fields[3] not in executable_sections:
            continue

        address = int(fields[0], 16)
        size = int(fields[4], 16)
        if normalize_arm:
            address &= ~1
        name_index = 5
        if fields[name_index] in (".hidden", ".weak", ".protected"):
            name_index += 1
        if name_index >= len(fields):
            continue
        name = fields[name_index]
        if not name:
            continue
        symbols.append((address, size, name, fields[3]))

    if not symbols:
        raise RuntimeError("no executable function symbols found in ELF")

    # A single address can have aliases. Keep a deterministic canonical name;
    # the runtime resolver still handles duplicate addresses in hand-built data.
    symbols.sort(key=lambda item: (item[0], item[2]))
    unique = []
    index = 0
    while index < len(symbols):
        address = symbols[index][0]
        aliases = []
        while index < len(symbols) and symbols[index][0] == address:
            aliases.append(symbols[index])
            index += 1

        canonical = min(aliases, key=lambda item: item[2])
        size = max(item[1] for item in aliases)
        unique.append((address, size, canonical[2], canonical[3]))
    return unique


def resolve_symbol_sizes(symbols, executable_sections=None):
    """Fill zero-sized functions from the next symbol in the same section."""
    resolved = []

    for index, (address, size, name, section) in enumerate(symbols):
        if size == 0:
            for next_address, _, _, next_section in symbols[index + 1:]:
                if next_section == section and next_address > address:
                    section_info = (executable_sections or {}).get(section)
                    if not section_info or next_address < section_info[1] + section_info[2]:
                        size = next_address - address
                    break
        resolved.append((address, size, name))

    return resolved


def collect_symbols(elf, objdump):
    section_text = _run_objdump(objdump, "-h", elf)
    executable_sections = parse_executable_sections(section_text)
    if not executable_sections:
        raise RuntimeError("no executable sections found in ELF")

    file_text = _run_objdump(objdump, "-f", elf)
    normalize_arm = is_32bit_arm_elf(file_text)
    symbols = parse_symbols(_run_objdump(objdump, "-t", elf),
                            executable_sections, normalize_arm)
    symbols = resolve_symbol_sizes(symbols, executable_sections)
    first = symbols[0][0]
    if max(symbol[0] - first for symbol in symbols) > UINT32_MAX:
        raise RuntimeError("kernel symbol address span does not fit uint32_t")
    if any(symbol[1] > UINT32_MAX for symbol in symbols):
        raise RuntimeError("kernel symbol size does not fit uint32_t")

    return symbols, first


def generate_source(symbols, first):
    names = bytearray()
    name_offsets = {}
    entries = []

    for address, size, name in symbols:
        if name not in name_offsets:
            name_offsets[name] = len(names)
            names.extend(name.encode("utf-8"))
            names.append(0)
        entries.append((address - first, name_offsets[name], size))

    name_literal = "".join("\\x%02x" % value for value in names)
    lines = [
        "/* Generated by tools/gen_ksym.py. Do not edit. */",
        "#include <rtthread.h>",
        "",
        'rt_used rt_section(".rodata.rt_ksym")',
        "const rt_uintptr_t rt_ksym_first_addr = 0x%x;" % first,
        'rt_used rt_section(".rodata.rt_ksym")',
        "const rt_uint32_t rt_ksym_count = %d;" % len(entries),
        'rt_used rt_section(".rodata.rt_ksym")',
        "const rt_uint32_t rt_ksym_entries[][3] = {",
    ]
    lines.extend("    {0x%x, %d, 0x%x}," % entry for entry in entries)
    lines.extend([
        "};",
        'rt_used rt_section(".rodata.rt_ksym")',
        "const char rt_ksym_names[] = \"%s\";" % name_literal,
        "",
    ])
    return "\n".join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", required=True)
    parser.add_argument("--objdump", default="objdump")
    parser.add_argument("--output")
    parser.add_argument("--verify", action="store_true")
    parser.add_argument("--table")
    args = parser.parse_args(argv)

    if args.verify and not args.table:
        parser.error("--verify requires --table")
    if not args.verify and not args.output:
        parser.error("--output is required unless --verify is used")

    try:
        symbols, first = collect_symbols(args.elf, args.objdump)
        source = generate_source(symbols, first)

        if args.verify:
            with open(args.table, "r", encoding="utf-8") as table:
                actual = table.read()
            if actual != source:
                raise RuntimeError("ksym table did not converge after final link")
        else:
            output_dir = os.path.dirname(os.path.abspath(args.output))
            os.makedirs(output_dir, exist_ok=True)
            with open(args.output, "w", encoding="utf-8", newline="\n") as table:
                table.write(source)
    except (OSError, RuntimeError) as exc:
        print("gen_ksym.py: %s" % exc, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

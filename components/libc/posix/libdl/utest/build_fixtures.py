#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Build ARM test modules from source; never commit generated ELF/header files."""
import argparse
from pathlib import Path
import shlex
import struct
import subprocess


def verify_fixture(name, data):
    """Check the ELF shape so a compiler change cannot silently remove a test."""
    if data[:6] != b'\x7fELF\x01\x01':
        raise RuntimeError(name + ': expected little-endian ELF32')
    kind, machine = struct.unpack_from('<HH', data, 16)
    if machine != 40 or kind != (3 if name in ('dg_dyn', 'dg_imp') else 1):
        raise RuntimeError(name + ': incorrect ARM ELF type')
    offset = struct.unpack_from('<I', data, 32)[0]
    stride, count, strings = struct.unpack_from('<HHH', data, 46)
    sections = [struct.unpack_from('<10I', data, offset + i * stride) for i in range(count)]
    names = data[sections[strings][4]:sections[strings][4] + sections[strings][5]]
    section_names = [names[s[0]:].split(b'\0', 1)[0].decode() for s in sections]
    symbols = {}
    for section in sections:
        if section[1] != 2:
            continue
        strings = sections[section[6]]
        table = data[strings[4]:strings[4] + strings[5]]
        for pos in range(section[4], section[4] + section[5], 16):
            symbol = struct.unpack_from('<IIIBBH', data, pos)
            label = table[symbol[0]:].split(b'\0', 1)[0].decode()
            if label:
                symbols[label] = symbol
    if name == 'dg_rel':
        assert symbols['common_value'][5] == 0xfff2
        assert symbols['aligned_value'][5] == 0xfff2 and symbols['aligned_value'][1] == 16
    elif name == 'dc_ptr':
        assert symbols['common_value'][5] == 0xfff2
        assert any(s[1] == 9 and section_names[s[7]] == '.data' and s[5] > 0 for s in sections)
    elif name == 'db_multi':
        assert section_names[symbols['bss_value'][5]] == '.bss'
        assert section_names[symbols['common_value'][5]] == '.common'
        assert sections[symbols['bss_value'][5]][1] == 8
        assert sections[symbols['common_value'][5]][1] == 8
    elif name == 'dn_addr':
        assert sections[symbols['probe'][5]][3] == 0x1000 and symbols['probe'][1] == 0
        assert sections[symbols['initialized'][5]][3] == 0x2000
    elif name == 'dd_dbg':
        assert any(s[1] == 9 and section_names[s[7]].startswith('.debug') for s in sections)
    elif name == 'dt_text':
        assert symbols['first'][5] != symbols['second'][5]
        assert symbols['first'][1] == symbols['second'][1] == 0
    elif name in ('du_sym', 'dz_none'):
        assert symbols['external_func'][5] == 0 and symbols['external_func'][3] == 0x12
        if name == 'dz_none':
            assert not any(s[3] == 0x12 and s[5] != 0 for s in symbols.values())
    elif name == 'dg_imp':
        # Dynamic symbols are in .dynsym; inspect the string table as well.
        assert b'rt_kprintf\0' in data


def build(cc, output):
    sources = Path(__file__).resolve().parent / 'fixtures'
    directory = output.parent / 'dlmodule-fixtures'
    directory.mkdir(parents=True, exist_ok=True)
    # ARMv5 literal-pool relocations are supported by libdl/arch/arm.c.
    # Cortex-A9 also executes these instructions; avoid unsupported MOVW/MOVT relocations.
    flags = ['-marm', '-mcpu=arm926ej-s', '-O0', '-fcommon', '-fno-pic',
             '-fno-stack-protector', '-fno-unwind-tables', '-fno-asynchronous-unwind-tables']
    modules = [
        ('dg_rel', 'globals', [], []),
        ('dg_dyn', 'globals', ['-fPIC', '-mlong-calls', '-DDYNAMIC_FIXTURE'], ['-shared']),
        ('dg_imp', 'globals', ['-fPIC', '-mlong-calls', '-DDYNAMIC_FIXTURE', '-DKERNEL_IMPORT'], ['-shared']),
        ('dc_ptr', 'common_target', [], []),
        ('db_multi', 'multi_bss', [], ['-Wl,-d,-T,' + str(sources / 'multi_bss.ld')]),
        ('dn_addr', 'sections', [], ['-Wl,-T,' + str(sources / 'nonzero.ld')]),
        ('dd_dbg', 'sections', ['-g'], []),
        ('dt_text', 'multi_text', [], []),
        ('du_sym', 'undefined', [], []),
        ('dz_none', 'undefined', ['-DZERO_EXPORTS'], []),
    ]
    lines = ['/* Generated ELF fixtures; do not edit. */',
             'struct dlmodule_fixture { const char *name; const unsigned char *data; unsigned size; };']
    for name, source, extra, link in modules:
        obj = directory / (name + '.o')
        elf = directory / (name + '.mo')
        subprocess.run(cc + flags + extra + ['-c', str(sources / (source + '.c')), '-o', str(obj)], check=True)
        mode = [] if '-shared' in link else ['-r']
        subprocess.run(cc + ['-nostdlib'] + mode + link + [str(obj), '-o', str(elf)], check=True)
        data = elf.read_bytes()
        verify_fixture(name, data)
        lines.append('static const unsigned char ' + name + '[] = {')
        for offset in range(0, len(data), 16):
            lines.append('    ' + ', '.join('0x%02x' % byte for byte in data[offset:offset + 16]) + ',')
        lines.append('};')
    lines.append('static const struct dlmodule_fixture dlmodule_fixtures[] = {')
    for name, _, _, _ in modules:
        lines.append('    {"%s.mo", %s, sizeof(%s)},' % (name, name, name))
    lines.append('};')
    output.write_text('\n'.join(lines) + '\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    build(shlex.split(args.cc), args.output.resolve())

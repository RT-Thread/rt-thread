# -*- coding: utf-8 -*-
#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
"""SCons integration for the generated RT-Thread kernel symbol table."""

import os
import subprocess
import sys

import rtconfig


def _run_generator(target, source, env):
    command = [sys.executable,
               os.path.join(env['RTT_ROOT'], 'tools', 'gen_ksym.py'),
               '--elf', source[0].abspath,
               '--output', target[0].abspath,
               '--objdump', rtconfig.OBJDUMP]
    return subprocess.call(command, env=dict(env['ENV']))


def BuildWithKSym(env, target, objects, end_building):
    """Build preliminary links, generate tables, then link and verify final ELF."""
    target_name = str(target)
    target_base = os.path.basename(target_name)
    target_stem, target_ext = os.path.splitext(target_base)
    artifact_dir = os.path.join('build', 'ksym')
    pre1_name = os.path.join(artifact_dir, target_stem + '.pre1' + target_ext)
    pre2_name = os.path.join(artifact_dir, target_stem + '.pre2' + target_ext)
    table1_name = os.path.join(artifact_dir, target_stem + '.pre1.c')
    table2_name = os.path.join(artifact_dir, target_stem + '.final.c')
    object1_name = os.path.join(artifact_dir, target_stem + '.pre1.o')
    object2_name = os.path.join(artifact_dir, target_stem + '.final.o')

    pre1 = env.Program(pre1_name, objects)
    table1 = env.Command(table1_name, pre1, _run_generator)
    object1 = env.Object(object1_name, table1)
    pre2 = env.Program(pre2_name, objects + [object1])
    table2 = env.Command(table2_name, pre2, _run_generator)
    object2 = env.Object(object2_name, table2)
    program = env.Program(target, objects + [object2])

    # SCons post actions run in registration order, so verification precedes
    # the normal binary/size post action installed by EndBuilding().
    def verify_final(target, source, env):
        command = [sys.executable,
                   os.path.join(env['RTT_ROOT'], 'tools', 'gen_ksym.py'),
                   '--verify',
                   '--elf', target[0].abspath,
                   '--table', table2[0].abspath,
                   '--objdump', rtconfig.OBJDUMP]
        return subprocess.call(command, env=dict(env['ENV']))

    env.AddPostAction(program, verify_final)
    end_building(target, program)
    return program

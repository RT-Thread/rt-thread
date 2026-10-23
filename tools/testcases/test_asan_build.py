#!/usr/bin/env python3
# Copyright (c) 2006-2026, RT-Thread Development Team
# SPDX-License-Identifier: Apache-2.0

"""Exercise ASan's SConscript with the flag representations used by BSPs.

Run with: python -m unittest discover -s tools/testcases -p test_asan_build.py
Requires SCons, also used to build the BSPs.
"""

import ast
import operator
import os
from pathlib import Path
from types import ModuleType, SimpleNamespace
import unittest
from unittest.mock import patch

from SCons.Script import Environment
from SCons.Util import CLVar


class AsanBuildTest(unittest.TestCase):
    def prepare(self, cflags, cxxflags, enabled=True, wrappers=True,
                platform='gcc', linkflags='-Wl,--gc-sections', earlier_flags=False):
        script = (Path(__file__).resolve().parents[2] /
                  'components/utilities/asan/SConscript')
        env = Environment(tools=['mingw'], CFLAGS=cflags, CXXFLAGS=cxxflags,
                          LINKFLAGS=linkflags)
        groups = []
        module = ModuleType('building')
        module.Import = lambda *names: None
        module.Return = lambda *names: None
        module.GetCurrentDir = lambda: str(script.parent)

        def get_depend(name):
            if isinstance(name, list):
                return all(get_depend(item) for item in name)
            return enabled if name == 'RT_USING_ASAN' else enabled and wrappers

        module.GetDepend = get_depend
        module.Glob = lambda pattern: ['asan.c', 'asan_heap.c', 'asan_libc.c']
        module.SrcRemove = lambda src, names: src.__setitem__(
            slice(None), [name for name in src if name not in names])
        module.SConscript = lambda name: []

        # Execute the real builder functions without importing BSP setup or
        # registering SCons command-line options. Stub unrelated group actions.
        builder = script.parents[3] / 'tools/building.py'
        names = {'_AppendGroupFlags', '_PretreatListParameters', 'DefineGroup'}
        tree = ast.parse(builder.read_text(), filename=str(builder))
        selected = ast.Module(body=[node for node in tree.body
                                    if isinstance(node, ast.FunctionDef) and
                                    node.name in names], type_ignores=[])
        module.Env = env
        module.Projects = groups
        module.CLVar = CLVar
        module.File = lambda sources: sources
        module.GetOption = lambda name: False
        module.utils = SimpleNamespace(GCCC99Patch=lambda value: value)
        module.rtconfig = SimpleNamespace(PLATFORM=platform)
        module.operator = operator
        module.os = os
        exec(compile(selected, str(builder), 'exec'), module.__dict__)
        self.define_group = module.DefineGroup
        if earlier_flags:
            module.DefineGroup('previous', [], ['RT_USING_ASAN'],
                               CXXFLAGS=' -fno-exceptions -fno-rtti')
        with patch.dict('sys.modules', {'building': module}):
            exec(compile(script.read_text(), str(script), 'exec'),
                 dict(env=env, rtconfig=SimpleNamespace(PLATFORM=platform)))
        return env, [group for group in groups if group['name'] == 'asan']

    def test_arguments_are_separate_for_each_bsp_representation(self):
        for kind in (str, list, CLVar):
            for other_kind in (str, list, CLVar):
                for link_kind in (str, list, CLVar):
                    for wrappers in (False, True):
                        self.check_arguments(kind, other_kind, link_kind, wrappers)

    def check_arguments(self, kind, other_kind, link_kind, wrappers):
        with self.subTest(cflags=kind, cxxflags=other_kind,
                          linkflags=link_kind, wrappers=wrappers):
            cflags = '-O2 -g' if kind is str else kind(['-O2', '-g'])
            cxxflags = ('-O2 -g' if other_kind is str else
                        other_kind(['-O2', '-g']))
            linkflags = ('-Wl,--gc-sections' if link_kind is str else
                         link_kind(['-Wl,--gc-sections']))
            env, groups = self.prepare(cflags, cxxflags,
                                       wrappers=wrappers,
                                       linkflags=linkflags)
            for flag in ('CFLAGS', 'CXXFLAGS'):
                tokens = [str(token) for token in
                          env.subst_list('$' + flag)[0]]
                self.assertIn('-O2', tokens)
                self.assertIn('-g', tokens)
                self.assertIn('-fsanitize=kernel-address', tokens)
                self.assertIn('-fno-omit-frame-pointer', tokens)
                self.assertEqual(
                    sum(t.startswith('-fno-builtin-') for t in tokens),
                    13 if wrappers else 0)
            self.assertEqual('asan_libc.c' in groups[0]['src'],
                             wrappers)
            tokens = [str(t) for t in
                      env.subst_list('$LINKFLAGS')[0]]
            self.assertEqual(
                sum(t.startswith('-Wl,--wrap=') for t in tokens),
                13 if wrappers else 0)
            runtime = env.Clone(CFLAGS=env['CFLAGS'] +
                                groups[0]['LOCAL_CFLAGS'])
            self.assertEqual(str(runtime.subst_list('$CFLAGS')[0][-1]),
                             '-fno-sanitize=kernel-address')

    def test_structured_arguments_preserve_spaces_and_nested_lists(self):
        for wrappers in (False, True):
            for kind in (list, CLVar):
                with self.subTest(kind=kind, wrappers=wrappers):
                    flags = kind(['-O2', ['-g', '-DMESSAGE=hello world'],
                                  '-include', 'directory with spaces/header.h'])
                    linkflags = kind(['-Wl,--gc-sections',
                                      ['-Ldirectory with spaces', '-nostartfiles']])
                    before = Environment(tools=['mingw'], CFLAGS=flags,
                                         CXXFLAGS=flags, LINKFLAGS=linkflags)
                    env, groups = self.prepare(flags, flags, wrappers=wrappers,
                                               linkflags=linkflags)
                    for name in ('CFLAGS', 'CXXFLAGS', 'LINKFLAGS'):
                        original = [str(token) for token in
                                    before.subst_list('$' + name)[0]]
                        actual = [str(token) for token in
                                  env.subst_list('$' + name)[0]]
                        self.assertEqual(actual[:len(original)], original)
                        self.assertIn('-fsanitize=kernel-address', actual)
                    runtime = env.Clone(CFLAGS=env['CFLAGS'] +
                                        groups[0]['LOCAL_CFLAGS'])
                    self.assertEqual(
                        str(runtime.subst_list('$CFLAGS')[0][-1]),
                        '-fno-sanitize=kernel-address')

    def test_disabled_component_preserves_environment(self):
        env, groups = self.prepare(['-O2'], CLVar('-g'), enabled=False)
        self.assertEqual(env['CFLAGS'], ['-O2'])
        self.assertEqual(env['CXXFLAGS'], CLVar('-g'))
        self.assertEqual(env['LINKFLAGS'], '-Wl,--gc-sections')
        self.assertEqual(groups, [])

    def test_later_groups_can_append_multiple_options(self):
        flags = ['-O2', ['-g', '-DMESSAGE=hello world']]
        env, groups = self.prepare(flags, CLVar(flags),
                                   linkflags=CLVar('-Wl,--gc-sections'), earlier_flags=True)
        self.define_group('later', [], ['RT_USING_ASAN'], CFLAGS=' -ffunction-sections -fdata-sections',
                         CXXFLAGS=' -fno-exceptions -fno-rtti',
                         LINKFLAGS=' -static -nostartfiles')
        for name, options in (
                ('CFLAGS', ['-ffunction-sections', '-fdata-sections']),
                ('CXXFLAGS', ['-fno-exceptions', '-fno-rtti']),
                ('LINKFLAGS', ['-static', '-nostartfiles'])):
            actual = [str(token) for token in env.subst_list('$' + name)[0]]
            for option in options:
                self.assertIn(option, actual)
            if name != 'LINKFLAGS':
                self.assertIn('-DMESSAGE=hello world', actual)
        runtime = env.Clone(CFLAGS=env['CFLAGS'] + groups[0]['LOCAL_CFLAGS'])
        self.assertEqual(str(runtime.subst_list('$CFLAGS')[0][-1]),
                         '-fno-sanitize=kernel-address')

    def test_unsupported_toolchain_is_rejected(self):
        with self.assertRaisesRegex(RuntimeError, 'GCC and GNU ld'):
            self.prepare('', '', platform='armcc')


if __name__ == '__main__':
    unittest.main()

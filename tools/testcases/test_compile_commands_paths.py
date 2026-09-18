#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json
import os
import shutil
import sys
import tempfile

TOOLS_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, TOOLS_DIR)

from compile_commands import get_minimal_dist_paths
from compile_commands import _get_entry_arguments
from compile_commands import _extract_include_paths
import mkdist


def test_arguments_and_relative_paths():
    tmp = tempfile.mkdtemp(prefix="rtthread_ccdb_test_")
    try:
        rt_root = os.path.join(tmp, "rt-thread")
        src_dir = os.path.join(rt_root, "components", "foo")
        inc_dir = os.path.join(src_dir, "include")
        os.makedirs(inc_dir, exist_ok=True)

        with open(os.path.join(src_dir, "foo.c"), "w", encoding="utf-8") as f:
            f.write("int foo(void) { return 0; }\n")

        with open(os.path.join(inc_dir, "foo.h"), "w", encoding="utf-8") as f:
            f.write("#define FOO 1\n")

        ccdb = os.path.join(tmp, "compile_commands.json")
        with open(ccdb, "w", encoding="utf-8") as f:
            json.dump([
                {
                    "directory": rt_root,
                    "arguments": [
                        "gcc",
                        "-I",
                        "components/foo/include",
                        "-c",
                        "components/foo/foo.c"
                    ],
                    "file": "components/foo/foo.c"
                }
            ], f)

        paths = get_minimal_dist_paths(ccdb, rt_root)

        expected = [
            os.path.join("components", "foo"),
            os.path.join("components", "foo", "include")
        ]

        missing = [path for path in expected if path not in paths]
        if missing:
            print("FAILED: missing expected paths:", missing)
            print("actual paths:", paths)
            return False

        print("PASSED: arguments and relative paths are handled")
        return True
    finally:
        shutil.rmtree(tmp)


def test_mkdist_strip_keeps_sources_when_used_paths_empty():
    tmp = tempfile.mkdtemp(prefix="rtthread_mkdist_strip_test_")
    old_mkdist = mkdist.MkDist
    old_zip_dist = mkdist.zip_dist

    try:
        bsp_root = os.path.join(tmp, "bsp")
        rt_root = os.path.join(tmp, "rt-thread")
        dist_dir = os.path.join(tmp, "dist_project")
        source_dir = os.path.join(dist_dir, "rt-thread", "components", "foo")
        source_file = os.path.join(source_dir, "foo.c")

        os.makedirs(bsp_root, exist_ok=True)
        os.makedirs(rt_root, exist_ok=True)

        def fake_mkdist(program, BSP_ROOT, RTT_ROOT, env, project_name, project_path=None):
            os.makedirs(source_dir, exist_ok=True)
            with open(source_file, "w", encoding="utf-8") as f:
                f.write("int foo(void) { return 0; }\n")

        def fake_zip_dist(dist_dir, project_name):
            return None

        mkdist.MkDist = fake_mkdist
        mkdist.zip_dist = fake_zip_dist

        mkdist.MkDist_Strip(None, bsp_root, rt_root, None, "dist_project", dist_dir)

        if not os.path.exists(source_file):
            print("FAILED: MkDist_Strip removed sources when used_paths is empty")
            return False

        print("PASSED: MkDist_Strip keeps sources when used_paths is empty")
        return True
    finally:
        mkdist.MkDist = old_mkdist
        mkdist.zip_dist = old_zip_dist
        shutil.rmtree(tmp)


def test_command_string_keeps_windows_backslashes():
    command = r"gcc -IC:\rt-thread\components\foo\include -c C:\rt-thread\components\foo\foo.c"
    args = _get_entry_arguments({"command": command})
    include_paths = _extract_include_paths(args)
    expected = r"C:\rt-thread\components\foo\include"

    if expected not in include_paths:
        print("FAILED: Windows include path was not preserved")
        print("args:", args)
        print("include_paths:", include_paths)
        return False

    print("PASSED: Windows include path is preserved")
    return True


def main():
    success = True

    if not test_arguments_and_relative_paths():
        success = False

    if not test_mkdist_strip_keeps_sources_when_used_paths_empty():
        success = False

    if not test_command_string_keeps_windows_backslashes():
        success = False

    if success:
        return 0
    return 1


if __name__ == "__main__":
    sys.exit(main())

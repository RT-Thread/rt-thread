#
# File      : env_package.py
# This file is part of RT-Thread RTOS
#
# SPDX-License-Identifier: GPL-2.0+
#
# Change Logs:
# Date           Author       Notes
# 2026-06-12     CYFS         Add shared package path helpers
#

import fnmatch
import os


def _same_path(path_a, path_b):
    return os.path.normcase(os.path.abspath(path_a)) == os.path.normcase(os.path.abspath(path_b))


def _format_path(path, relative_to=None, pathsep=None):
    if relative_to:
        path = os.path.relpath(path, relative_to)

    if pathsep:
        path = path.replace(os.path.sep, pathsep)
        if os.path.altsep:
            path = path.replace(os.path.altsep, pathsep)

    return path


def _marker_exists(package_path, marker):
    if not marker:
        return True

    if isinstance(marker, (list, tuple)):
        for item in marker:
            if not _marker_exists(package_path, item):
                return False
        return True

    return os.path.exists(os.path.join(package_path, marker))


def _unique_paths(paths):
    unique_paths = []
    seen = set()

    for path in paths:
        if not path:
            continue

        key = os.path.normcase(os.path.abspath(path))
        if key in seen:
            continue

        seen.add(key)
        unique_paths.append(path)

    return unique_paths


def package_root_candidates(bsp_root):
    bsp_root = os.path.abspath(bsp_root)
    ancestors = []
    current = bsp_root

    while True:
        if _is_rt_thread_bsp_dir(current):
            break

        ancestors.append(current)

        parent = os.path.dirname(current)
        if _same_path(parent, current):
            break

        current = parent

    library_roots = [os.path.join(root, 'libraries') for root in ancestors]
    package_roots = [os.path.join(root, 'packages') for root in ancestors]

    return _unique_paths(library_roots + package_roots)


def package_candidates(bsp_root, package_name, extra_candidates=None):
    candidates = []
    for root in package_root_candidates(bsp_root):
        candidates.append(os.path.join(root, package_name))

    if extra_candidates:
        candidates.extend(extra_candidates)

    return _unique_paths(candidates)


def find_package_path(bsp_root, package_name, marker=None, extra_candidates=None,
                      relative_to=None, pathsep=None):
    candidates = package_candidates(bsp_root, package_name, extra_candidates)
    existing_paths = []

    for path in candidates:
        if not os.path.isdir(path):
            continue

        existing_paths.append(path)
        if _marker_exists(path, marker):
            return _format_path(path, relative_to, pathsep)

    if existing_paths:
        return _format_path(existing_paths[0], relative_to, pathsep)

    fallback_path = os.path.join(os.path.abspath(bsp_root), 'packages', package_name)
    return _format_path(fallback_path, relative_to, pathsep)


def package_exists(bsp_root, package_name, marker=None):
    path = find_package_path(bsp_root, package_name, marker=marker)
    return os.path.isdir(path) and _marker_exists(path, marker)


def packages_available(bsp_root, package_names):
    for package_name in package_names:
        if not package_exists(bsp_root, package_name):
            return False

    return True


def _package_name_match(name, package_name=None, package_prefix=None, package_pattern=None):
    if package_name and name != package_name:
        return False

    if package_prefix and not name.startswith(package_prefix):
        return False

    if package_pattern and not fnmatch.fnmatch(name, package_pattern):
        return False

    return True


def find_package_root(bsp_root, package_name=None, package_prefix=None,
                      package_pattern=None, marker=None):
    for root in package_root_candidates(bsp_root):
        if not os.path.isdir(root):
            continue

        if package_name:
            package_path = os.path.join(root, package_name)
            if os.path.isdir(package_path) and _marker_exists(package_path, marker):
                return root
            continue

        try:
            names = os.listdir(root)
        except OSError:
            continue

        for name in names:
            package_path = os.path.join(root, name)
            if not os.path.isdir(package_path):
                continue
            if not _package_name_match(name, package_name, package_prefix, package_pattern):
                continue
            if _marker_exists(package_path, marker):
                return root

    return None


def is_libraries_package(package_path):
    return os.path.basename(os.path.dirname(os.path.abspath(package_path))).lower() == 'libraries'


def _get_existing_libraries_path(root):
    exact_path = os.path.join(root, 'libraries')
    if os.path.isdir(exact_path):
        return exact_path

    try:
        for name in os.listdir(root):
            path = os.path.join(root, name)
            if name.lower() == 'libraries' and os.path.isdir(path):
                return path
    except OSError:
        pass

    return None


def _is_rt_thread_bsp_dir(path):
    parent = os.path.dirname(path)
    return (
        os.path.basename(path).lower() == 'bsp'
        and os.path.isdir(os.path.join(parent, 'bsp'))
        and os.path.isfile(os.path.join(parent, 'include', 'rtdef.h'))
    )


def find_libraries_path_upward(bsp_root):
    current = os.path.abspath(bsp_root)

    while True:
        libraries_path = _get_existing_libraries_path(current)
        if libraries_path:
            return libraries_path

        if _is_rt_thread_bsp_dir(current):
            return None

        parent = os.path.dirname(current)
        if _same_path(parent, current):
            return None

        current = parent


def is_hal_sdk_package_bridge(package_path):
    if os.path.isdir(os.path.join(package_path, '.git')):
        return False

    sconscript_path = os.path.join(package_path, 'SConscript')
    if not os.path.isfile(sconscript_path):
        return False

    try:
        with open(sconscript_path, 'r') as f:
            content = f.read()
        return (
            'hal-sdk package source not found' in content
            and (
                'source_candidates' in content
                or '_find_hal_sdk_libraries_path' in content
                or 'libraries_path_prefix' in content
            )
        )
    except Exception:
        return False

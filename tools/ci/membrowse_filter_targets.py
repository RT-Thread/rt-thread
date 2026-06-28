#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import argparse
import json
import os


GLOBAL_FILES = {
    ".github/membrowse-targets.json",
    ".github/workflows/membrowse-report.yml",
    "Kconfig",
}

GLOBAL_PREFIXES = (
    "components/",
    "include/",
    "libcpu/",
    "src/",
    "tools/",
)

def normalize_path(path):
    return path.replace("\\", "/").strip().lstrip("./")


def is_ignored_change(path):
    name = path.rsplit("/", 1)[-1]
    return name.lower().startswith("readme") or (path.startswith("bsp/") and "/docs/" in path)


def is_under(path, prefix):
    path = normalize_path(path)
    prefix = normalize_path(prefix).rstrip("/")
    return path == prefix or path.startswith(prefix + "/")


def read_changed_files(path):
    with open(path, "r", encoding="utf-8") as file:
        return [
            changed_file
            for changed_file in (normalize_path(line) for line in file if line.strip())
            if not is_ignored_change(changed_file)
        ]


def is_global_change(path):
    return path in GLOBAL_FILES or any(path.startswith(prefix) for prefix in GLOBAL_PREFIXES)


def target_related_prefixes(target):
    return [
        normalize_path(prefix)
        for prefix in target.get("watch_paths", [target["bsp_path"]])
    ]


def select_targets(targets, changed_files):
    if not changed_files:
        return []

    if any(is_global_change(path) for path in changed_files):
        return targets

    selected = []
    for target in targets:
        related_prefixes = target_related_prefixes(target)
        if any(
            is_under(changed_file, related_prefix)
            for changed_file in changed_files
            for related_prefix in related_prefixes
        ):
            selected.append(target)

    return selected


def write_github_output(matrix, output_path):
    if not output_path:
        return

    with open(output_path, "a", encoding="utf-8") as output:
        output.write("matrix={}\n".format(json.dumps(matrix, separators=(",", ":"))))
        output.write("target_count={}\n".format(len(matrix)))


def main():
    parser = argparse.ArgumentParser(description="Filter MemBrowse targets by changed files.")
    parser.add_argument("--targets", required=True, help="Path to membrowse-targets.json.")
    parser.add_argument("--changed-files", required=True, help="Path to a newline-delimited changed file list.")
    args = parser.parse_args()

    with open(args.targets, "r", encoding="utf-8") as file:
        targets = json.load(file)

    changed_files = read_changed_files(args.changed_files)
    selected_targets = select_targets(targets, changed_files)

    print("Changed files:")
    for changed_file in changed_files:
        print("  {}".format(changed_file))

    print("Selected MemBrowse targets:")
    for target in selected_targets:
        print("  {}".format(target["target_name"]))

    print("Selected {}/{} MemBrowse targets".format(len(selected_targets), len(targets)))
    write_github_output(selected_targets, os.getenv("GITHUB_OUTPUT"))


if __name__ == "__main__":
    main()

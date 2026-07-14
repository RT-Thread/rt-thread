#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2026-07-07     RT-Thread    add clang-format CI check
#

import argparse
import fnmatch
import logging
import re
import subprocess
import sys
from pathlib import Path


SOURCE_EXTENSIONS = (
    ".c",
    ".h",
    ".cpp",
    ".hpp",
    ".cc",
    ".hh",
    ".C",
    ".H",
    ".cp",
    ".cxx",
    ".hxx",
    ".inc",
    ".inl",
    ".ipp",
    ".tpp",
    ".txx",
)


HUNK_HEADER = re.compile(r"^@@ -\d+(?:,\d+)? \+(\d+)(?:,(\d+))? @@")


def init_logger():
    logging.basicConfig(level=logging.INFO, format="[%(filename)s %(lineno)d %(levelname)s] %(message)s ")


def run_git(args, check=True):
    result = subprocess.run(["git"] + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if check and result.returncode != 0:
        raise RuntimeError(result.stderr.decode("utf-8", errors="replace"))
    return result


def ensure_remote(remote, repo):
    result = run_git(["remote", "get-url", remote], check=False)
    if result.returncode == 0:
        run_git(["remote", "set-url", remote, repo])
    else:
        run_git(["remote", "add", remote, repo])


def split_git_paths(output):
    paths = []
    for item in output.split(b"\0"):
        if item:
            paths.append(item.decode("utf-8", errors="surrogateescape"))
    return paths


def get_changed_files(repo, branch, remote):
    ensure_remote(remote, repo)
    run_git(["fetch", "--no-tags", remote, branch])

    merge_base = run_git(["merge-base", "FETCH_HEAD", "HEAD"]).stdout.decode("utf-8", errors="replace").strip()
    if not merge_base:
        raise RuntimeError("git merge-base FETCH_HEAD HEAD returned no commit")

    diff_range = [merge_base, "HEAD"]
    result = run_git(["diff", "--name-only", "-z", "--diff-filter=ACMR", "--no-renames"] + diff_range + ["--"])
    return split_git_paths(result.stdout), diff_range


def merge_line_ranges(ranges):
    if not ranges:
        return []

    merged = []
    for start, end in sorted(ranges):
        if not merged or start > merged[-1][1] + 1:
            merged.append([start, end])
        else:
            merged[-1][1] = max(merged[-1][1], end)
    return [(start, end) for start, end in merged]


def parse_changed_line_ranges(diff_text):
    ranges = []
    for line in diff_text.splitlines():
        match = HUNK_HEADER.match(line)
        if not match:
            continue

        start = int(match.group(1))
        count = int(match.group(2) or "1")
        if count == 0:
            continue
        ranges.append((start, start + count - 1))

    return merge_line_ranges(ranges)


def get_changed_line_ranges(diff_range, files):
    line_ranges = {}
    for file_path in files:
        result = run_git(["diff", "--unified=0", "--diff-filter=ACMR", "--no-renames"] + diff_range + ["--", file_path])
        line_ranges[file_path] = parse_changed_line_ranges(result.stdout.decode("utf-8", errors="replace"))
    return line_ranges


def normalize_path(path):
    return path.as_posix().strip("/")


def match_path(path, pattern):
    return fnmatch.fnmatchcase(path, pattern) or fnmatch.fnmatchcase("/" + path, pattern)


def ignore_pattern_matches(pattern, relative_file):
    pattern = pattern.strip()
    if not pattern or pattern.startswith("#"):
        return False

    pattern = pattern.lstrip("/")
    dir_only = pattern.endswith("/")
    pattern = pattern.rstrip("/")
    if not pattern:
        return False

    relative_file = relative_file.strip("/")
    if dir_only:
        parts = relative_file.split("/")
        dirs = ["/".join(parts[:index]) for index in range(1, len(parts))]
        return match_path(relative_file, pattern) or any(match_path(directory, pattern) for directory in dirs)

    if "/" not in pattern:
        return any(fnmatch.fnmatchcase(part, pattern) for part in relative_file.split("/"))

    return match_path(relative_file, pattern)


def is_ignored_by_clang_format(root, file_path):
    absolute_file = (root / file_path).resolve()
    try:
        relative_to_root = absolute_file.relative_to(root)
    except ValueError:
        return False

    current_dir = absolute_file.parent
    ignore_files = []
    while True:
        ignore_file = current_dir / ".clang-format-ignore"
        if ignore_file.exists():
            ignore_files.append(ignore_file)
        if current_dir == root:
            break
        current_dir = current_dir.parent

    for ignore_file in reversed(ignore_files):
        try:
            ignore_dir = ignore_file.parent.relative_to(root)
            if str(ignore_dir) == ".":
                relative_file = normalize_path(relative_to_root)
            else:
                relative_file = normalize_path(relative_to_root.relative_to(ignore_dir))
        except ValueError:
            continue
        with open(ignore_file, "r", encoding="utf-8") as ignore:
            for line in ignore:
                if ignore_pattern_matches(line, relative_file):
                    logging.info("ignore file by %s: %s", ignore_file.relative_to(root).as_posix(), file_path)
                    return True
    return False


def filter_source_files(root, files):
    source_files = []
    for file_path in files:
        path = root / file_path
        if not path.is_file():
            continue
        if not file_path.endswith(SOURCE_EXTENSIONS):
            continue
        if is_ignored_by_clang_format(root, Path(file_path)):
            continue
        source_files.append(file_path)
    return source_files


def check_clang_format(files, clang_format, line_ranges=None):
    failed_files = []
    for file_path in files:
        invocation = [clang_format, "--dry-run", "--Werror", "--style=file"]
        if line_ranges is not None:
            ranges = line_ranges.get(file_path, [])
            if not ranges:
                logging.info("skip clang-format, no changed lines -> %s", file_path)
                continue
            for start, end in ranges:
                invocation.append("--lines={}:{}".format(start, end))

        invocation.append(file_path)
        logging.info("check clang-format -> %s", file_path)
        result = subprocess.run(
            invocation,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
        )
        if result.stdout:
            sys.stdout.write(result.stdout)
        if result.stderr:
            sys.stderr.write(result.stderr)
        if result.returncode != 0:
            failed_files.append(file_path)

    if failed_files:
        logging.error("clang-format check failed, please run clang-format on the files above.")
        return False
    return True


def main():
    parser = argparse.ArgumentParser(description="Check changed source files with clang-format.")
    parser.add_argument("--repo", default="https://github.com/RT-Thread/rt-thread")
    parser.add_argument("--branch", default="master")
    parser.add_argument("--remote", default="rtt_repo")
    parser.add_argument("--clang-format-executable", default="clang-format")
    parser.add_argument("files", nargs="*", help="files to check; git diff is used when omitted")
    args = parser.parse_args()

    init_logger()
    root = Path.cwd().resolve()
    if args.files:
        files = args.files
        line_ranges = None
    else:
        files, diff_range = get_changed_files(args.repo, args.branch, args.remote)
        line_ranges = get_changed_line_ranges(diff_range, files)

    source_files = filter_source_files(root, files)
    if line_ranges is not None:
        line_ranges = {file_path: line_ranges.get(file_path, []) for file_path in source_files}

    if not source_files:
        logging.warning("There are no source files to check format.")
        return 0

    if not check_clang_format(source_files, args.clang_format_executable, line_ranges):
        return 1

    logging.info("clang-format check success.")
    return 0


if __name__ == "__main__":
    sys.exit(main())

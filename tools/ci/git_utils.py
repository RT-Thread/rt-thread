#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import locale
import subprocess


def _default_encoding():
    return locale.getpreferredencoding()


def _decode_output(data, encoding=None):
    if data is None:
        return ""

    if encoding is None:
        encoding = _default_encoding()

    return data.decode(encoding, errors="replace")


def _run_git(args, encoding=None):
    result = subprocess.run(
        ["git"] + args,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )
    stdout = _decode_output(getattr(result, "stdout", b""), encoding)
    stderr = _decode_output(getattr(result, "stderr", b""), encoding)
    returncode = getattr(result, "returncode", 0)

    if returncode != 0:
        raise RuntimeError(
            "git {} failed with code {}: {}".format(
                " ".join(args),
                returncode,
                stderr.strip(),
            )
        )

    return stdout


def split_nonempty_lines(output):
    return [line.strip() for line in output.splitlines() if line.strip()]


def get_changed_files(base, head, diff_filter="ACMR", no_renames=True, full_index=True, encoding=None):
    args = [
        "diff",
        "--name-only",
        base,
        head,
        "--diff-filter={}".format(diff_filter),
    ]

    if no_renames:
        args.append("--no-renames")
    if full_index:
        args.append("--full-index")

    output = _run_git(args, encoding=encoding)
    return split_nonempty_lines(output)


def get_name_status_lines(base, head="HEAD", encoding=None):
    output = _run_git(
        ["diff", "--name-status", base, head],
        encoding=encoding,
    )
    return split_nonempty_lines(output)


def get_merge_base(target_branch, head="HEAD", encoding=None):
    output = _run_git(
        ["merge-base", target_branch, head],
        encoding=encoding,
    )
    return output.strip()


def _parse_ls_tree_size(output, encoding=None):
    text = _decode_output(output, encoding).strip()
    if not text:
        return 0

    fields = text.split(None, 4)
    if len(fields) < 4:
        return 0

    try:
        return int(fields[3])
    except ValueError:
        return 0


def get_blob_size(ref, path, encoding=None):
    result = subprocess.run(
        ["git", "ls-tree", "-l", ref, "--", path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )

    if result.returncode != 0:
        return 0

    return _parse_ls_tree_size(result.stdout, encoding)

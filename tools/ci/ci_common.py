#
# Copyright (c) 2006-2025, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2026-07-08     yan hu       add read-only changed-file helpers
#

"""Shared read-only helpers for the tools/ci scripts.

Changed-file detection must never modify repository state (HEAD, index or
working tree) or leave temporary files behind.
"""

import os
import logging
import subprocess
from collections import namedtuple

# Structured result of a git invocation; ``cmd`` keeps the exact argument list.
GitResult = namedtuple("GitResult", ["returncode", "stdout", "stderr", "cmd"])

DEFAULT_TARGET_REF = "origin/master"
TARGET_REF_ENV_VAR = "RTT_CI_TARGET_REF"
DEFAULT_DIFF_FILTER = "ACMR"


def run_git(args, cwd=None):
    """Run a git command (no shell) and return a GitResult.

    A non-zero git exit code is reported via ``returncode``, not raised.
    """
    cmd = ["git"] + list(args)
    try:
        completed = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            cwd=cwd,
        )
    except OSError as e:
        logging.error("failed to execute {}: {}".format(" ".join(cmd), e))
        return GitResult(returncode=127, stdout="", stderr=str(e), cmd=cmd)

    return GitResult(
        returncode=completed.returncode,
        stdout=completed.stdout or "",
        stderr=completed.stderr or "",
        cmd=cmd,
    )


def resolve_target_ref(default_ref=DEFAULT_TARGET_REF, env_var=TARGET_REF_ENV_VAR):
    """Return the baseline ref to diff against.

    Uses ``RTT_CI_TARGET_REF`` when set (for fork/CI setups), otherwise the
    default. Read-only.
    """
    ref = os.environ.get(env_var)
    if ref:
        ref = ref.strip()
        if ref:
            return ref
    return default_ref


def normalize_changed_files(output):
    """Split output into lines, drop empties and normalise separators to ``/``."""
    files = []
    for line in output.splitlines():
        line = line.strip()
        if not line:
            continue
        files.append(line.replace("\\", "/"))
    return files


def get_merge_base(target_ref=DEFAULT_TARGET_REF, head_ref="HEAD", cwd=None):
    """Return the merge base of the two refs, or ``None`` on failure. Read-only."""
    result = run_git(["merge-base", target_ref, head_ref], cwd=cwd)
    if result.returncode != 0:
        logging.error(
            "git merge-base {} {} failed: {}".format(
                target_ref, head_ref, result.stderr.strip()
            )
        )
        return None
    base = result.stdout.strip()
    if not base:
        logging.error(
            "git merge-base {} {} returned no commit".format(target_ref, head_ref)
        )
        return None
    return base


def get_changed_files_between(base_ref, head_ref="HEAD",
                              diff_filter=DEFAULT_DIFF_FILTER, cwd=None):
    """Files changed between two refs. ``None`` on failure, ``[]`` on empty diff."""
    args = [
        "diff",
        "--name-only",
        "--diff-filter={}".format(diff_filter),
        "--no-renames",
        "--full-index",
        base_ref,
        head_ref,
    ]
    result = run_git(args, cwd=cwd)
    if result.returncode != 0:
        logging.error(
            "git diff {}..{} failed: {}".format(
                base_ref, head_ref, result.stderr.strip()
            )
        )
        return None
    return normalize_changed_files(result.stdout)


def get_changed_files(target_ref=DEFAULT_TARGET_REF, head_ref="HEAD",
                      diff_filter=DEFAULT_DIFF_FILTER, cwd=None):
    """Files changed on ``head_ref`` vs the merge base with ``target_ref``.

    Read-only. ``None`` on git failure, ``[]`` on empty diff.
    """
    base = get_merge_base(target_ref, head_ref, cwd=cwd)
    if base is None:
        return None
    return get_changed_files_between(base, head_ref, diff_filter=diff_filter, cwd=cwd)


def maybe_fetch_remote(remote_name, remote_url=None, cwd=None):
    """Ensure ``remote_name`` points at ``remote_url`` and fetch its refs.

    Adds the remote when missing, or updates its URL when it already exists but
    differs. Touches ``.git/config`` and ``FETCH_HEAD`` only, never HEAD, the
    index or the working tree. Returns ``True`` on success, ``False`` on any
    failure so callers stop instead of diffing against a stale baseline.
    """
    existing = run_git(["remote"], cwd=cwd)
    if existing.returncode != 0:
        logging.error("git remote failed: {}".format(existing.stderr.strip()))
        return False

    remotes = normalize_changed_files(existing.stdout)
    if remote_name not in remotes:
        if not remote_url:
            logging.error(
                "remote '{}' does not exist and no url was provided".format(remote_name)
            )
            return False
        added = run_git(["remote", "add", remote_name, remote_url], cwd=cwd)
        if added.returncode != 0:
            logging.error(
                "git remote add {} failed: {}".format(remote_name, added.stderr.strip())
            )
            return False
    elif remote_url:
        current = run_git(["remote", "get-url", remote_name], cwd=cwd)
        if current.returncode != 0:
            logging.error(
                "git remote get-url {} failed: {}".format(
                    remote_name, current.stderr.strip()
                )
            )
            return False
        if current.stdout.strip() != remote_url:
            updated = run_git(["remote", "set-url", remote_name, remote_url], cwd=cwd)
            if updated.returncode != 0:
                logging.error(
                    "git remote set-url {} failed: {}".format(
                        remote_name, updated.stderr.strip()
                    )
                )
                return False

    fetched = run_git(["fetch", remote_name], cwd=cwd)
    if fetched.returncode != 0:
        logging.error(
            "git fetch {} failed: {}".format(remote_name, fetched.stderr.strip())
        )
        return False

    return True

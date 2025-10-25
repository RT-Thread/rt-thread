#!/usr/bin/env python
'''
convert rtt_root + "\\**\\.ignore_format.yml" to .clang-format-ignore
'''

import os
import yaml
import argparse


def convert_ignore_format(ignore_format_yml):
    if not os.path.exists(ignore_format_yml):
        return

    try:
        # read .ignore_format.yml
        with open(ignore_format_yml) as f:
            ignore_config = yaml.safe_load(f.read())
            file_ignore = ignore_config.get("file_path", [])
            dirs_ignore = ignore_config.get("dir_path", [])

        # delete .ignore_format.yml
        # os.remove(ignore_format_yml)

        # write .clang-format-ignore
        clang_format_ignore = os.path.join(os.path.dirname(ignore_format_yml), ".clang-format-ignore")
        with open(clang_format_ignore, "w", encoding='utf-8') as f:
            f.write(
                """
# You can create .clang-format-ignore (https://clang.llvm.org/docs/ClangFormat.html#clang-format-ignore) files to make clang-format ignore certain files. A .clang-format-ignore file consists of patterns of file path names. It has the following format:
# - A blank line is skipped.
# - Leading and trailing spaces of a line are trimmed.
# - A line starting with a hash (#) is a comment.
# - A non-comment line is a single pattern.
# - The slash (/) is used as the directory separator.
# - A pattern is relative to the directory of the .clang-format-ignore file (or the root directory if the pattern starts with a slash). Patterns containing drive names (e.g. C:) are not supported.
# - Patterns follow the rules specified in POSIX 2.13.1, 2.13.2, and Rule 1 of 2.13.3.
# - Bash globstar (**) is supported.
# - A pattern is negated if it starts with a bang (!).
# To match all files in a directory, use e.g. foo/bar/*. To match all files in the directory of the .clang-format-ignore file, use *. Multiple .clang-format-ignore files are supported similar to the .clang-format files, with a lower directory level file voiding the higher level ones.
#
"""
            )
            for item in file_ignore:
                f.write(item + "\n")
            for item in dirs_ignore:
                f.write(item + "/**\n")

    except Exception as e:
        pass


def main():
    # get rtt_root
    rtt_root = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "../"))
    # walk rtt_root find .ignore_format.yml
    for root, folders, files in os.walk(rtt_root):
        if ".ignore_format.yml" in files:
            print("process " + os.path.join(root, ".ignore_format.yml"))
            convert_ignore_format(os.path.join(root, ".ignore_format.yml"))


if __name__ == "__main__":
    main()

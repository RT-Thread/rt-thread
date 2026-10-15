import importlib.util
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock


def load_module(module_name, path):
    path = Path(path)
    repo_root = path.parents[2]
    module_dir = path.parent

    for item in (str(repo_root), str(module_dir)):
        if item not in sys.path:
            sys.path.insert(0, item)

    spec = importlib.util.spec_from_file_location(module_name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class CIDiffPathParsingTestCase(unittest.TestCase):
    def setUp(self):
        self.repo_root = Path(__file__).resolve().parents[2]
        self.old_cwd = os.getcwd()

    def tearDown(self):
        os.chdir(self.old_cwd)

    def test_git_utils_splits_empty_diff_output(self):
        module = load_module(
            "git_utils",
            self.repo_root / "tools" / "ci" / "git_utils.py",
        )

        self.assertEqual(module.split_nonempty_lines(""), [])
        self.assertEqual(module.split_nonempty_lines("\n\r\n"), [])
        self.assertEqual(module.split_nonempty_lines("a.c\n\n b.c \n"), ["a.c", "b.c"])

    def test_format_ignore_returns_empty_list_for_empty_diff(self):
        module = load_module(
            "format_ignore",
            self.repo_root / "tools" / "ci" / "format_ignore.py",
        )

        if hasattr(module, "get_changed_files"):
            patcher = mock.patch.object(module, "get_changed_files", return_value=[])
        else:
            class FakeResult:
                returncode = 0
                stdout = b""
                stderr = b""

            patcher = mock.patch.object(module.subprocess, "run", return_value=FakeResult())

        with patcher:
            files = module.CheckOut().get_new_file()

        self.assertEqual(files, [])

    def test_compile_bsp_diff_returns_empty_set_for_empty_diff(self):
        module = load_module(
            "compile_bsp_with_drivers",
            self.repo_root / "tools" / "ci" / "compile_bsp_with_drivers.py",
        )

        if hasattr(module, "get_changed_files"):
            patcher = mock.patch.object(module, "get_changed_files", return_value=[])
        else:
            class FakeResult:
                returncode = 0
                stdout = b""
                stderr = b""

            patcher = mock.patch.object(module.subprocess, "run", return_value=FakeResult())

        with patcher:
            dirs = module.diff()

        self.assertEqual(dirs, set())

    def test_git_diff_show_handles_paths_with_spaces(self):
        if shutil.which("git") is None:
            self.skipTest("git is not available")

        module = load_module(
            "git_diff_show",
            self.repo_root / "tools" / "ci" / "git_diff_show.py",
        )

        tempdir = tempfile.mkdtemp()
        workdir = Path(tempdir)

        try:
            def run(cmd):
                result = subprocess.run(
                    cmd,
                    cwd=str(workdir),
                    text=True,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    check=False,
                )
                self.assertEqual(
                    result.returncode,
                    0,
                    msg="command failed: {}\nstdout:\n{}\nstderr:\n{}".format(
                        " ".join(cmd),
                        result.stdout,
                        result.stderr,
                    ),
                )
                return result

            run(["git", "init"])
            run(["git", "checkout", "-b", "master"])

            space_dir = workdir / "dir with space"
            space_dir.mkdir()
            file_path = space_dir / "file with space.txt"
            file_path.write_text("old\n", encoding="utf-8")

            run(["git", "add", "."])
            run(
                [
                    "git",
                    "-c",
                    "user.name=Test",
                    "-c",
                    "user.email=test@example.com",
                    "commit",
                    "-m",
                    "base",
                ]
            )

            run(["git", "checkout", "-b", "feature"])
            file_path.write_text("old\nnew content\n", encoding="utf-8")
            run(["git", "add", "."])
            run(
                [
                    "git",
                    "-c",
                    "user.name=Test",
                    "-c",
                    "user.email=test@example.com",
                    "commit",
                    "-m",
                    "modify space path",
                ]
            )

            os.chdir(workdir)
            diffs = module.GitDiffAnalyzer("master").get_diff_files()
        finally:
            os.chdir(self.old_cwd)
            shutil.rmtree(workdir, ignore_errors=True)

        self.assertEqual(len(diffs), 1)
        self.assertEqual(diffs[0].path, "dir with space/file with space.txt")
        self.assertEqual(diffs[0].status, "M")
        self.assertEqual(diffs[0].old_size, len("old\n".encode("utf-8")))
        self.assertEqual(diffs[0].new_size, len("old\nnew content\n".encode("utf-8")))
        self.assertEqual(
            diffs[0].size_change,
            len("old\nnew content\n".encode("utf-8")) - len("old\n".encode("utf-8")),
        )


if __name__ == "__main__":
    unittest.main()

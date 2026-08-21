import os
import shutil
import subprocess
import sys
import tempfile
import textwrap
import unittest
from pathlib import Path


class MkromfsCodeGenerationTestCase(unittest.TestCase):
    def setUp(self):
        self.repo_root = Path(__file__).resolve().parents[2]
        self.mkromfs = self.repo_root / "tools" / "mkromfs.py"
        self.tempdir = tempfile.TemporaryDirectory()
        self.workdir = Path(self.tempdir.name)
        self.rootdir = self.workdir / "root"
        self.include_dir = self.workdir / "include"
        self.rootdir.mkdir()
        self.include_dir.mkdir()

        (self.include_dir / "rtthread.h").write_text(
            "typedef unsigned char rt_uint8_t;\n",
            encoding="utf-8",
        )
        (self.include_dir / "dfs_romfs.h").write_text(
            textwrap.dedent(
                """\
                #define ROMFS_DIRENT_FILE 0
                #define ROMFS_DIRENT_DIR 1
                #define RT_NULL ((void *)0)
                struct romfs_dirent
                {
                    int type;
                    const char *name;
                    rt_uint8_t *data;
                    unsigned int size;
                };
                """
            ),
            encoding="utf-8",
        )

    def tearDown(self):
        self.tempdir.cleanup()

    def run_mkromfs(self, output):
        return subprocess.run(
            [sys.executable, str(self.mkromfs), str(self.rootdir), str(output)],
            cwd=str(self.repo_root),
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=False,
        )

    def compile_c_file(self, source):
        if shutil.which("gcc") is None:
            self.skipTest("gcc is not available")
        return subprocess.run(
            [
                "gcc",
                "-fsyntax-only",
                "-I",
                str(self.include_dir),
                str(source),
            ],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=False,
        )

    def test_special_file_names_generate_valid_c_code(self):
        test_files = {
            "foo-bar.txt": "hyphen\n",
            "a b.txt": "space\n",
        }
        if os.name != "nt":
            test_files.update(
                {
                    'a"b.txt': "quote\n",
                    r"a\b.txt": "backslash\n",
                }
            )

        for name, content in test_files.items():
            (self.rootdir / name).write_text(content, encoding="utf-8")

        output = self.workdir / "romfs.c"
        mkromfs_result = self.run_mkromfs(output)
        self.assertEqual(
            mkromfs_result.returncode,
            0,
            msg=mkromfs_result.stderr,
        )

        generated = output.read_text(encoding="utf-8")
        self.assertIn('"foo-bar.txt"', generated)
        self.assertIn('"a b.txt"', generated)
        if os.name != "nt":
            self.assertIn(r'"a\"b.txt"', generated)
            self.assertIn(r'"a\\b.txt"', generated)

        compile_result = self.compile_c_file(output)
        self.assertEqual(
            compile_result.returncode,
            0,
            msg=compile_result.stderr,
        )

    def test_empty_file_with_special_name_generates_valid_null_entry(self):
        (self.rootdir / "empty-file.txt").write_bytes(b"")

        output = self.workdir / "romfs.c"
        mkromfs_result = self.run_mkromfs(output)
        self.assertEqual(
            mkromfs_result.returncode,
            0,
            msg=mkromfs_result.stderr,
        )

        generated = output.read_text(encoding="utf-8")
        self.assertIn('"empty-file.txt"', generated)
        self.assertIn("RT_NULL, 0", generated)

        compile_result = self.compile_c_file(output)
        self.assertEqual(
            compile_result.returncode,
            0,
            msg=compile_result.stderr,
        )


if __name__ == "__main__":
    unittest.main()

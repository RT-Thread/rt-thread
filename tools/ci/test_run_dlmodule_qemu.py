# SPDX-License-Identifier: Apache-2.0
"""Exercise runner exit conditions without requiring a board or QEMU."""
from contextlib import redirect_stdout
import importlib.util
import io
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest

spec = importlib.util.spec_from_file_location('dlmodule_runner', Path(__file__).with_name('run_dlmodule_qemu.py'))
runner = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runner)


class RunnerTests(unittest.TestCase):
    def execute(self, lines, delay=0, timeout=3):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fake = root / 'qemu'
            fake.write_text('#!/usr/bin/env python3\nimport time\n'
                            + f'for line in {lines!r}: print(line, flush=True)\n'
                            + f'time.sleep({delay})\n')
            fake.chmod(0o755)
            args = SimpleNamespace(qemu=str(fake), kernel=root/'kernel', disk=root/'disk',
                                   log=root/'log', timeout=timeout)
            with redirect_stdout(io.StringIO()):
                runner.run(args)

    def passing_lines(self):
        return [f'[==========] utest unit name: ({name})' for name in sorted(runner.CASES)] + [
            '[  PASSED  ] [ result   ] testcase (' + runner.PREFIX + 'regression)',
            '[==========] [ utest    ] finished']

    def test_all_cases_required(self):
        self.execute(self.passing_lines())

    def test_empty_suite_fails(self):
        with self.assertRaisesRegex(RuntimeError, 'Missing passing tests'):
            self.execute(['[==========] [ utest    ] finished'])

    def test_missing_unit_fails(self):
        with self.assertRaisesRegex(RuntimeError, 'Missing passing tests'):
            self.execute(self.passing_lines()[1:])

    def test_failure_before_success_fails(self):
        with self.assertRaisesRegex(RuntimeError, 'failure'):
            self.execute(['[  FAILED  ] [ result   ] testcase (broken)'] + self.passing_lines())

    def test_suite_success_required(self):
        lines = self.passing_lines()
        del lines[-2]
        with self.assertRaisesRegex(RuntimeError, 'did not report success'):
            self.execute(lines)

    def test_early_exit_fails(self):
        with self.assertRaisesRegex(RuntimeError, 'exited'):
            self.execute([])

    def test_cpu_exception_fails(self):
        with self.assertRaisesRegex(RuntimeError, 'exception'):
            self.execute(['data abort: exception'])

    def test_timeout_fails(self):
        with self.assertRaisesRegex(RuntimeError, 'timeout'):
            self.execute([], delay=10, timeout=0.2)


if __name__ == '__main__':
    unittest.main()

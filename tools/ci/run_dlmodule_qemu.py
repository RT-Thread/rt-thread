#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Run the ARM dlmodule suite, requiring every expected utest to pass."""
import argparse
from pathlib import Path
import re
import selectors
import subprocess
import time


CASES = {
    'globals_rel', 'globals_dyn', 'kernel_import', 'common_target', 'multi_nobits',
    'nonzero_sections', 'debug_sections', 'multi_text', 'undefined_symbol', 'zero_exports',
}
PREFIX = 'components.libc.posix.libdl.'


def run(args):
    command = [args.qemu, '-M', 'vexpress-a9', '-smp', '2', '-m', '128M',
               '-kernel', str(args.kernel.resolve()), '-nographic', '-monitor', 'none',
               '-drive', f'file={args.disk.resolve()},if=sd,format=raw']
    args.log.parent.mkdir(parents=True, exist_ok=True)
    process = subprocess.Popen(command, stdin=subprocess.DEVNULL,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    units = set()
    passed = False
    deadline = time.monotonic() + args.timeout
    pending = b''
    selector = selectors.DefaultSelector()
    selector.register(process.stdout, selectors.EVENT_READ)
    try:
        with args.log.open('w', encoding='utf-8') as log:
            while time.monotonic() < deadline:
                for key, _ in selector.select(timeout=0.2):
                    chunk = key.fileobj.read1(4096)
                    if not chunk:
                        raise RuntimeError('QEMU exited before the test completion marker')
                    pending += chunk
                    while b'\n' in pending:
                        raw, pending = pending.split(b'\n', 1)
                        line = raw.decode('utf-8', errors='replace').rstrip('\r')
                        print(line, flush=True)
                        log.write(line + '\n')
                        log.flush()
                        if '[  FAILED  ]' in line or re.search(
                                r'assert(?:ion)? failed|data abort|prefetch abort|undefined instruction',
                                line, re.IGNORECASE):
                            raise RuntimeError('Test failure or CPU exception detected')
                        match = re.search(r'\[==========\] utest unit name: \(([^)]*)\)', line)
                        if match:
                            units.add(match.group(1))
                        if '[  PASSED  ] [ result   ] testcase (' + PREFIX + 'regression)' in line:
                            passed = True
                        if '[==========] [ utest    ] finished' in line:
                            missing = CASES - units
                            if missing:
                                raise RuntimeError('Missing passing tests: ' + ', '.join(sorted(missing)))
                            if not passed:
                                raise RuntimeError('The dlmodule suite did not report success')
                            print(f'DLMODULE_QEMU_PASS cases={len(CASES)}', flush=True)
                            return
            raise RuntimeError(f'QEMU test timeout after {args.timeout} seconds')
    finally:
        selector.close()
        if process.poll() is None:
            process.terminate()
            try:
                process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait()
        process.stdout.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--kernel', type=Path, required=True)
    parser.add_argument('--disk', type=Path, required=True)
    parser.add_argument('--log', type=Path, default=Path('qemu_output_arm.log'))
    parser.add_argument('--qemu', default='qemu-system-arm')
    parser.add_argument('--timeout', type=float, default=120)
    arguments = parser.parse_args()
    try:
        run(arguments)
    except (OSError, RuntimeError) as error:
        parser.exit(1, f'dlmodule QEMU test failed: {error}\n')

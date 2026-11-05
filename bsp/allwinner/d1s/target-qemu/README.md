# D1s on QEMU (for humans and AI agents)

This directory boots the `bsp/allwinner/d1s` image on the d1s QEMU machine
(<https://github.com/cms19859230182-lang/d1s-qemu>). It's written as a short
step-by-step guide that an AI coding agent can follow without guessing.

## 1. Prepare the QEMU environment

```sh
git clone https://github.com/cms19859230182-lang/d1s-qemu
cd d1s-qemu
# follow its README to build; the result must provide an executable ./run.sh
export D1S_QEMU_DIR=$PWD
```

Check: `test -x "$D1S_QEMU_DIR/run.sh" && echo ok`.

## 2. Build the BSP

```sh
cd rt-thread/bsp/allwinner/d1s
export RTT_EXEC_PATH=/path/to/riscv64-unknown-elf/bin   # RISC-V toolchain
scons -j$(nproc)
```

Check: `rtthread.bin` exists in `bsp/allwinner/d1s/`. `sbi.bin` and
`u-boot.dtb` are already in the BSP directory, and `run.sh` uses them.

## 3. Run

Interactive:

```sh
./target-qemu/run-qemu.sh
```

Non-interactive smoke test (recommended for agents, always set a timeout):

```sh
QEMU_TIMEOUT=30 ./target-qemu/run-qemu.sh < /dev/null > qemu.log 2>&1 || true
```

Extra arguments are passed through to d1s-qemu's `run.sh`.

## 4. Pass/fail criteria

- **Pass:** `qemu.log` contains the RT-Thread banner (` \ | /`) and the
  `msh />` prompt.
- Optional interactive check: at `msh />` run `list_thread` and `version`.
- Exit code 124 just means the timeout was reached. That's normal for a
  smoke test, so judge the run by the log, not the exit code.

```sh
grep -q 'msh />' qemu.log && echo PASS || echo FAIL
```

## 5. Common failures

| Symptom | Cause / fix |
|---|---|
| `please set D1S_QEMU_DIR ...` | Export `D1S_QEMU_DIR` pointing at a *built* d1s-qemu checkout. |
| `rtthread.bin not found` | Run `scons` in `bsp/allwinner/d1s` first. |
| No output at all | Wrong console: this BSP uses UART0, and the script already passes `--console uart0`. Also check that the build succeeded and isn't stale. |
| Hangs after OpenSBI banner | `sbi.bin` or `u-boot.dtb` is missing or mismatched in the BSP directory, or the image was linked for the wrong address. |
| Agent session hangs | You forgot `QEMU_TIMEOUT`. Always set it when running non-interactively. |

The old entry point `bsp/allwinner/d1s/qemu-d1s.sh` still works as a thin
wrapper around this script.

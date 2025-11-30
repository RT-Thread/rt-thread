import os
import subprocess


def _parse_cflags(cflags: str):
    info = {
        "march": None,
        "mabi": None,
        "rv_bits": None,  # 32 or 64
        "has_f": False,
        "has_d": False,
    }

    if not cflags:
        return info

    parts = cflags.split()
    for flag in parts:
        if flag.startswith("-march="):
            info["march"] = flag.split("=", 1)[1]
            if "rv32" in info["march"]:
                info["rv_bits"] = 32
            elif "rv64" in info["march"]:
                info["rv_bits"] = 64
            # crude feature detection
            m = info["march"]
            if m:
                info["has_f"] = ("f" in m)
                info["has_d"] = ("d" in m)
        elif flag.startswith("-mabi="):
            info["mabi"] = flag.split("=", 1)[1]
            if info["mabi"] in ("ilp32d", "ilp32f", "lp64d", "lp64f"):
                # floating-point ABI implies FPU availability
                info["has_f"] = True
                info["has_d"] = info["mabi"].endswith("d")

    return info


def detect_rust_target(has, rtconfig):
    """
    Decide the Rust target triple based on RT-Thread Kconfig and rtconfig.*.
    `has` is a callable: has("SYMBOL") -> bool
    """
    # ARM Cortex-M
    if has("ARCH_ARM"):
        # FPU hints from flags/macros
        cflags = getattr(rtconfig, "CFLAGS", "")
        hard_float = "-mfloat-abi=hard" in cflags or has("ARCH_ARM_FPU") or has("ARCH_FPU_VFP")

        if has("ARCH_ARM_CORTEX_M3"):
            return "thumbv7m-none-eabi"
        if has("ARCH_ARM_CORTEX_M4") or has("ARCH_ARM_CORTEX_M7"):
            return "thumbv7em-none-eabihf" if hard_float else "thumbv7em-none-eabi"
        if has("ARCH_ARM_CORTEX_M33"):
            # v8m.main
            return "thumbv8m.main-none-eabi"
        if has("ARCH_ARM_CORTEX_A"):
            return "armv7a-none-eabi"

    # AArch64
    if has("ARCH_AARCH64") or has("ARCH_ARMV8") or has("ARCH_ARM64"):
        if has("ARCH_CPU_FLOAT_ABI_SOFT"):
            return "aarch64-unknown-none-softfloat"
        return "aarch64-unknown-none"
    
    # RISC-V
    if has("ARCH_RISCV32") or has("ARCH_RISCV64"):
        cflags = getattr(rtconfig, "CFLAGS", "")
        info = _parse_cflags(cflags)

        # fallback to Kconfig hint if march not present
        rv_bits = info["rv_bits"] or (32 if has("ARCH_RISCV32") else 64)

        # ABI must carry f/d to actually use hard-float calling convention
        abi = info["mabi"] or ""
        abi_has_fp = abi.endswith("f") or abi.endswith("d")

        if rv_bits == 32:
            # Only pick *f* target when ABI uses hard-float; otherwise use soft-float even if core has F/D
            return "riscv32imafc-unknown-none-elf" if abi_has_fp else "riscv32imac-unknown-none-elf"
        else:
            # rv64: prefer gc (includes fd) only when ABI uses hard-float
            return "riscv64gc-unknown-none-elf" if abi_has_fp else "riscv64imac-unknown-none-elf"

    # Fallback by ARCH string or CFLAGS
    arch = getattr(rtconfig, "ARCH", None)
    if arch:
        arch_l = arch.lower()
        if "aarch64" in arch_l:
            return "aarch64-unknown-none"
        if "arm" == arch_l or "armv7" in arch_l:
            return "armv7a-none-eabi"
        if "riscv32" in arch_l:
            return "riscv32imac-unknown-none-elf"
        if "riscv64" in arch_l or "risc-v" in arch_l:
            # Many BSPs use "risc-v" token; assume 64-bit for virt64
            return "riscv64imac-unknown-none-elf"

    # Parse CFLAGS for hints
    cflags = getattr(rtconfig, "CFLAGS", "")
    if "-mcpu=cortex-m3" in cflags:
        return "thumbv7m-none-eabi"
    if "-mcpu=cortex-m4" in cflags or "-mcpu=cortex-m7" in cflags:
        if "-mfpu=" in cflags and "-mfloat-abi=hard" in cflags:
            return "thumbv7em-none-eabihf"
        return "thumbv7em-none-eabi"
    if "-march=rv32" in cflags:
        march_val = None
        mabi_val = None
        for flag in cflags.split():
            if flag.startswith("-march="):
                march_val = flag[len("-march="):]
            elif flag.startswith("-mabi="):
                mabi_val = flag[len("-mabi="):]
        has_f_or_d = False
        if march_val and any(x in march_val for x in ("f", "d")):
            has_f_or_d = True
        if mabi_val and any(x in mabi_val for x in ("f", "d")):
            has_f_or_d = True
        return "riscv32imafc-unknown-none-elf" if has_f_or_d else "riscv32imac-unknown-none-elf"
    if "-march=rv64" in cflags:
        march_val = None
        mabi_val = None
        for flag in cflags.split():
            if flag.startswith("-march="):
                march_val = flag[len("-march="):]
            elif flag.startswith("-mabi="):
                mabi_val = flag[len("-mabi="):]
        has_f_or_d = False
        if mabi_val and (("lp64d" in mabi_val) or ("lp64f" in mabi_val)):
            has_f_or_d = True
        if march_val and any(x in march_val for x in ("f", "d")):
            has_f_or_d = True
        if mabi_val and any(x in mabi_val for x in ("f", "d")):
            has_f_or_d = True
        if has_f_or_d:
            return "riscv64gc-unknown-none-elf"
        return "riscv64imac-unknown-none-elf"

    return None


def make_rustflags(rtconfig, target: str):
    rustflags = [
        "-C", "opt-level=z",
        "-C", "panic=abort",
        "-C", "relocation-model=static",
    ]

    if "riscv" in target:
        rustflags += [
            "-C", "code-model=medium",
            "-C", "link-dead-code",
        ]
        # propagate march/mabi for consistency (use link-arg for staticlib builds – harmless)
        cflags = getattr(rtconfig, "CFLAGS", "")
        for flag in cflags.split():
            if flag.startswith("-march=") or flag.startswith("-mabi="):
                rustflags += ["-C", f"link-arg={flag}"]

    if "thumb" in target or "aarch64" in target:
        rustflags += ["-C", "link-arg=-nostartfiles"]

    return " ".join(rustflags)


def collect_features(has):
    feats = []
    if has("RT_USING_SMP"):
        feats.append("smp")
    return feats


def verify_rust_toolchain():
    try:
        r1 = subprocess.run(["rustc", "--version"], capture_output=True, text=True)
        r2 = subprocess.run(["cargo", "--version"], capture_output=True, text=True)
        return r1.returncode == 0 and r2.returncode == 0
    except Exception:
        return False


def ensure_rust_target_installed(target: str):
    try:
        result = subprocess.run(["rustup", "target", "list", "--installed"], capture_output=True, text=True)
        if result.returncode == 0 and target in result.stdout:
            return True
        print(f"Rust target '{target}' is not installed.")
        print(f"Please install it with: rustup target add {target}")
    except Exception:
        print("Warning: Failed to check rustup target list (rustup missing?)")
    return False


def cargo_build_staticlib(rust_dir: str, target: str, features, debug: bool, rustflags: str = None):
    build_root = os.path.join((os.path.abspath(os.path.join(rust_dir, os.pardir, os.pardir))), "build", "rust")
    target_dir = os.path.join(build_root, "target")
    os.makedirs(build_root, exist_ok=True)

    env = os.environ.copy()
    if rustflags:
        prev = env.get("RUSTFLAGS", "").strip()
        env["RUSTFLAGS"] = (prev + " " + rustflags).strip() if prev else rustflags
    env["CARGO_TARGET_DIR"] = target_dir

    cmd = ["cargo", "build", "--target", target, "--manifest-path", os.path.join(rust_dir, "Cargo.toml")]
    if not debug:
        cmd.insert(2, "--release")
    if features:
        cmd += ["--no-default-features", "--features", ",".join(features)]

    print("Building Rust component (cargo)…")
    res = subprocess.run(cmd, cwd=rust_dir, env=env, capture_output=True, text=True)
    if res.returncode != 0:
        print("Warning: Rust build failed")
        if res.stderr:
            print(res.stderr)
        return None

    mode = "debug" if debug else "release"
    lib_path = os.path.join(target_dir, target, mode, "librt_rust.a")
    if os.path.exists(lib_path):
        print("Rust component built successfully")
        return lib_path
    print("Warning: Library not found at expected location")
    return None


def clean_rust_build(bsp_root: str, artifact_type: str = "rust"):
    """Return the build directory path for SCons Clean operation"""
    build_dir = os.path.join(bsp_root, "build", artifact_type)
    return build_dir
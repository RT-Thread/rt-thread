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

        if has("ARCH_ARM_CORTEX_M0") or has("ARCH_ARM_CORTEX_M0PLUS"):
            return "thumbv6m-none-eabi"
        if has("ARCH_ARM_CORTEX_M3"):
            return "thumbv7m-none-eabi"
        if has("ARCH_ARM_CORTEX_M4") or has("ARCH_ARM_CORTEX_M7"):
            return "thumbv7em-none-eabihf" if hard_float else "thumbv7em-none-eabi"
        if has("ARCH_ARM_CORTEX_M23"):
            return "thumbv8m.base-none-eabi"
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
        if "riscv64" in arch_l:
            return "riscv64imac-unknown-none-elf"
        if "risc-v" in arch_l:
            info = _parse_cflags(getattr(rtconfig, "CFLAGS", ""))
            abi = info["mabi"] or ""
            abi_has_fp = abi.endswith("f") or abi.endswith("d")
            if info["rv_bits"] == 32:
                return "riscv32imafc-unknown-none-elf" if abi_has_fp else "riscv32imac-unknown-none-elf"
            if info["rv_bits"] == 64:
                return "riscv64gc-unknown-none-elf" if abi_has_fp else "riscv64imac-unknown-none-elf"
            # Many BSPs use "risc-v" token; assume 64-bit for virt64 when CFLAGS do not specify width
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
        info = _parse_cflags(cflags)
        abi = info["mabi"] or ""
        abi_has_fp = abi.endswith("f") or abi.endswith("d")
        return "riscv32imafc-unknown-none-elf" if abi_has_fp else "riscv32imac-unknown-none-elf"
    if "-march=rv64" in cflags:
        info = _parse_cflags(cflags)
        abi = info["mabi"] or ""
        abi_has_fp = abi.endswith("f") or abi.endswith("d")
        if abi_has_fp:
            return "riscv64gc-unknown-none-elf"
        return "riscv64imac-unknown-none-elf"

    return None


def uses_short_wchar_abi(rtconfig, target: str):
    if not isinstance(target, str) or not target:
        return False
    if not (target.startswith("thumb") or target.startswith("arm")):
        return False

    cflags = getattr(rtconfig, "CFLAGS", "")
    return "-fshort-wchar" in cflags.split()


def make_cargo_build_std_args(rtconfig, target: str):
    if uses_short_wchar_abi(rtconfig, target):
        return ["-Z", "build-std=core,alloc"]
    return []


def make_rustflags(rtconfig, target: str):
    if not isinstance(target, str) or not target:
        arch = getattr(rtconfig, "ARCH", None)
        cflags = getattr(rtconfig, "CFLAGS", "")
        raise ValueError(
            "Unsupported Rust target: unable to detect a Rust target "
            f"for ARCH={arch!r}, CFLAGS={cflags!r}"
        )

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

    if uses_short_wchar_abi(rtconfig, target):
        rustflags += ["-Zllvm_module_flag=wchar_size:u32:2:error"]

    return " ".join(rustflags)


def collect_features(has):
    cargo_toml_path = os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "core", "Cargo.toml")
    )
    if not os.path.isfile(cargo_toml_path):
        raise RuntimeError(f"Rust core Cargo.toml not found: {cargo_toml_path}")

    try:
        import toml
    except ImportError as e:
        raise RuntimeError("Missing toml module required to parse Rust core Cargo.toml") from e

    try:
        with open(cargo_toml_path, "r") as f:
            cargo_data = toml.load(f)
    except OSError as e:
        raise RuntimeError(f"Failed to read Rust core Cargo.toml {cargo_toml_path}: {e}") from e
    except Exception as e:
        raise RuntimeError(f"Failed to parse Rust core Cargo.toml {cargo_toml_path}: {e}") from e

    declared_features = cargo_data.get("features")
    if not isinstance(declared_features, dict):
        raise RuntimeError("Invalid Rust core Cargo.toml: [features] must be a table")

    package = cargo_data.get("package")
    metadata = package.get("metadata") if isinstance(package, dict) else None
    rt_thread = metadata.get("rt-thread") if isinstance(metadata, dict) else None
    feature_mappings = rt_thread.get("features") if isinstance(rt_thread, dict) else None
    if not isinstance(feature_mappings, dict):
        raise RuntimeError(
            "Invalid Rust core feature metadata: package.metadata.rt-thread.features must be a table"
        )

    for feature in feature_mappings:
        if feature not in declared_features:
            raise RuntimeError(
                f"Rust core feature metadata references undeclared Cargo feature: {feature}"
            )

    feats = []
    for feature in declared_features:
        if feature == "default" or feature not in feature_mappings:
            continue

        mapping = feature_mappings[feature]
        if not isinstance(mapping, dict):
            raise RuntimeError(f"Invalid Rust core feature metadata for '{feature}': expected a table")
        if set(mapping) != {"all"}:
            raise RuntimeError(
                f"Invalid Rust core feature metadata for '{feature}': only 'all' is supported"
            )

        symbols = mapping["all"]
        if not isinstance(symbols, list):
            raise RuntimeError(f"Invalid Rust core feature metadata for '{feature}': 'all' must be a list")
        if not symbols:
            raise RuntimeError(f"Invalid Rust core feature metadata for '{feature}': 'all' must not be empty")
        if any(not isinstance(symbol, str) or not symbol for symbol in symbols):
            raise RuntimeError(
                f"Invalid Rust core feature metadata for '{feature}': 'all' must contain only non-empty strings"
            )

        if all(has(symbol) for symbol in symbols):
            feats.append(feature)
    return feats


def verify_rust_toolchain():
    try:
        r1 = subprocess.run(["rustc", "--version"], capture_output=True, text=True)
        r2 = subprocess.run(["cargo", "--version"], capture_output=True, text=True)
        return r1.returncode == 0 and r2.returncode == 0
    except Exception:
        return False


def parse_installed_rust_targets(output):
    return {line.strip() for line in output.splitlines() if line.strip()}


def get_staticlib_artifact_name(rust_dir):
    cargo_toml_path = os.path.join(rust_dir, "Cargo.toml")
    lib_name = "rt_rust"

    try:
        import toml
        with open(cargo_toml_path, "r") as f:
            cargo_data = toml.load(f)

        package_name = cargo_data.get("package", {}).get("name")
        lib_name = cargo_data.get("lib", {}).get("name") or package_name or lib_name
    except Exception as e:
        print(f"Warning: Failed to parse Rust static library metadata from {cargo_toml_path}: {e}")

    if not isinstance(lib_name, str) or not lib_name:
        lib_name = "rt_rust"

    lib_name = lib_name.replace("-", "_")
    return f"lib{lib_name}.a"


def get_staticlib_link_name(rust_dir):
    cargo_toml_path = os.path.join(rust_dir, "Cargo.toml")
    lib_name = "rt_rust"

    try:
        import toml
        with open(cargo_toml_path, "r") as f:
            cargo_data = toml.load(f)

        package_name = cargo_data.get("package", {}).get("name")
        lib_name = cargo_data.get("lib", {}).get("name") or package_name or lib_name
    except Exception as e:
        print(f"Warning: Failed to parse Rust static library metadata from {cargo_toml_path}: {e}")

    if not isinstance(lib_name, str) or not lib_name:
        lib_name = "rt_rust"

    return lib_name.replace("-", "_")


def ensure_rust_target_installed(target: str):
    if not isinstance(target, str) or not target:
        print("Invalid Rust target: expected a non-empty string")
        return False

    try:
        result = subprocess.run(["rustup", "target", "list", "--installed"], capture_output=True, text=True)
        installed_targets = parse_installed_rust_targets(result.stdout)
        if result.returncode == 0 and target in installed_targets:
            return True
        print(f"Rust target '{target}' is not installed.")
        print(f"Please install it with: rustup target add {target}")
    except Exception:
        print("Warning: Failed to check rustup target list (rustup missing?)")
    return False


def cargo_build_staticlib(rust_dir: str, target: str, features, debug: bool, rustflags: str = None, build_root: str = None, cargo_extra_args=None):
    if build_root is None:
        build_root = os.path.join((os.path.abspath(os.path.join(rust_dir, os.pardir, os.pardir))), "build", "rust")
    else:
        build_root = os.path.abspath(os.fspath(build_root))
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
    if cargo_extra_args:
        cmd[2:2] = cargo_extra_args
    if features:
        cmd += ["--no-default-features", "--features", ",".join(features)]

    print("Building Rust component (cargo)…")
    try:
        res = subprocess.run(cmd, cwd=rust_dir, env=env, capture_output=True, text=True)
    except FileNotFoundError:
        print("Error: cargo executable not found. Please install Rust/Cargo and ensure it is in PATH.")
        return None
    if res.returncode != 0:
        print("Warning: Rust build failed")
        if res.stderr:
            print(res.stderr)
        return None

    mode = "debug" if debug else "release"
    artifact_name = get_staticlib_artifact_name(rust_dir)
    lib_path = os.path.join(target_dir, target, mode, artifact_name)
    if os.path.isfile(lib_path) and os.path.getsize(lib_path) > 0:
        print("Rust component built successfully")
        return lib_path
    print(f"Warning: Rust static library artifact not found, is not a file, or is empty: {lib_path}")
    return None


def clean_rust_build(bsp_root: str, artifact_type: str = "rust"):
    """Return the build directory path for SCons Clean operation"""
    build_dir = os.path.join(bsp_root, "build", artifact_type)
    return build_dir

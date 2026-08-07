import os
import subprocess
from SCons.Subst import quote_spaces


# Configuration to feature mapping table for components
# This table defines which RT-Thread configurations should enable which component features
# All feature configurations are now defined in feature_config_component.py
CONFIG_COMPONENT_FEATURE_MAP = {
}


class ComponentBuildError(Exception):
    pass


def load_toml_module():
    try:
        import toml
        return toml
    except ImportError as e:
        raise ComponentBuildError("Missing toml module required to parse component Cargo.toml") from e


def normalize_component_build_root(build_root, cwd):
    """
    Normalize the component build root directory.

    Args:
        build_root: Optional build root directory
        cwd: Current working directory (component directory)

    Returns:
        str: Absolute build root path
    """
    if build_root is None:
        if not cwd:
            raise ComponentBuildError("Invalid build_root: cwd is required when build_root is None")
        build_root = os.path.join(cwd, "build", "rust", "component")

    try:
        build_root = os.fspath(build_root)
    except TypeError:
        raise ComponentBuildError("Invalid build_root: expected a non-empty path")

    if not isinstance(build_root, str) or not build_root:
        raise ComponentBuildError("Invalid build_root: expected a non-empty path")

    return os.path.abspath(build_root)


def get_component_staticlib_artifact_name(rust_dir):
    cargo_toml_path = os.path.join(rust_dir, "Cargo.toml")
    lib_name = "em_component_registry"

    try:
        import toml
        with open(cargo_toml_path, "r") as f:
            cargo_data = toml.load(f)

        package_name = cargo_data.get("package", {}).get("name")
        lib_name = cargo_data.get("lib", {}).get("name") or package_name or lib_name
    except Exception as e:
        print(f"Warning: Failed to parse Rust component static library metadata from {cargo_toml_path}: {e}")

    if not isinstance(lib_name, str) or not lib_name:
        lib_name = "em_component_registry"

    lib_name = lib_name.replace("-", "_")
    return f"lib{lib_name}.a"


def get_component_staticlib_link_name(rust_dir):
    cargo_toml_path = os.path.join(rust_dir, "Cargo.toml")
    lib_name = "em_component_registry"

    try:
        import toml
        with open(cargo_toml_path, "r") as f:
            cargo_data = toml.load(f)

        package_name = cargo_data.get("package", {}).get("name")
        lib_name = cargo_data.get("lib", {}).get("name") or package_name or lib_name
    except Exception as e:
        print(f"Warning: Failed to parse Rust component static library metadata from {cargo_toml_path}: {e}")

    if not isinstance(lib_name, str) or not lib_name:
        lib_name = "em_component_registry"

    return lib_name.replace("-", "_")


def get_staticlib_link_name_from_artifact(lib_path):
    """
    Derive the linker library name from the actual staticlib artifact file name.

    Args:
        lib_path: Path to the built staticlib artifact

    Returns:
        str: Link name (artifact name without the leading 'lib' and trailing
             '.a'), or None if the artifact does not follow that convention.
    """
    artifact_name = os.path.basename(os.fspath(lib_path))
    if artifact_name.startswith("lib") and artifact_name.endswith(".a"):
        return artifact_name[3:-2]
    return None


def get_component_export_symbols(features):
    enabled_features = set(features or [])
    symbols = []
    for config_info in CONFIG_COMPONENT_FEATURE_MAP.values():
        if config_info['feature'] in enabled_features:
            export_symbols = config_info.get('export_symbols', [])
            if not export_symbols:
                raise ComponentBuildError(
                    f"No link anchor metadata registered for enabled component feature '{config_info['feature']}'"
                )
            symbols.extend(export_symbols)
    return symbols


def check_component_dependencies(component_dir, required_dependencies):
    """
    Check if a component has the required dependencies
    
    Args:
        component_dir: Component directory path
        required_dependencies: List of dependency names to check
        
    Returns:
        bool: True if all required dependencies are present
    """
    if not component_dir or not required_dependencies:
        return True
    
    cargo_toml_path = os.path.join(component_dir, 'Cargo.toml')
    if not os.path.exists(cargo_toml_path):
        return False
    
    try:
        import toml
        with open(cargo_toml_path, 'r') as f:
            cargo_data = toml.load(f)
        
        dependencies = cargo_data.get('dependencies', {})
        
        # Check if all required dependencies are present
        for dep in required_dependencies:
            if dep not in dependencies:
                return False
        
        return True
        
    except Exception as e:
        print(f"Warning: Failed to parse {cargo_toml_path}: {e}")
        return False


def collect_component_features(has_func, component_dir=None):
    """
    Collect component features based on RT-Thread configuration using extensible mapping table
    
    Args:
        has_func: Function to check if a configuration is enabled
        component_dir: Component directory to check dependencies (optional)
        
    Returns:
        list: List of features to enable
    """
    features = []
    
    # Iterate through all configured mappings
    for config_name, config_info in CONFIG_COMPONENT_FEATURE_MAP.items():
        # Check if this RT-Thread configuration is enabled
        if has_func(config_name) or has_func('RT_RUST_BUILD_ALL_EXAMPLES'):
            feature_name = config_info['feature']
            required_deps = config_info.get('dependencies', [])
            
            # If component_dir is provided, check dependencies
            if component_dir:
                if check_component_dependencies(component_dir, required_deps):
                    features.append(feature_name)
                    print(f"Enabling component feature '{feature_name}' for {config_name} in {os.path.basename(component_dir)}")
            else:
                # If no component_dir provided, enable for all (backward compatibility)
                features.append(feature_name)
                print(f"Enabling component feature '{feature_name}' for {config_name}")
    
    return features


def declared_component_features(component_dir):
    cargo_toml_path = os.path.join(component_dir, 'Cargo.toml')
    if not os.path.isfile(cargo_toml_path):
        raise ComponentBuildError(f"Component Cargo.toml not found: {cargo_toml_path}")

    toml = load_toml_module()
    try:
        with open(cargo_toml_path, 'r') as f:
            cargo_data = toml.load(f)
        return set(cargo_data.get('features', {}).keys())
    except Exception as e:
        raise ComponentBuildError(f"Failed to parse component features from {cargo_toml_path}: {e}") from e


def filter_declared_component_features(component_dir, features):
    declared_features = declared_component_features(component_dir)
    return [feature for feature in features if feature in declared_features]


def cargo_build_component_staticlib(rust_dir, target, features, debug, rustflags=None, build_root=None, cargo_extra_args=None):
    """
    Build a Rust component as a static library using Cargo.
    
    Args:
        rust_dir: Directory containing the Rust component
        target: Rust target architecture
        features: List of features to enable
        debug: Whether this is a debug build
        rustflags: Additional Rust compilation flags
        build_root: Build root directory
        
    Returns:
        str: Path to the built library file, or None if build failed
    """
    build_root = normalize_component_build_root(build_root, None)
    os.makedirs(build_root, exist_ok=True)

    env = os.environ.copy()
    if rustflags:
        prev = env.get("RUSTFLAGS", "").strip()
        env["RUSTFLAGS"] = (prev + " " + rustflags).strip() if prev else rustflags
    env["CARGO_TARGET_DIR"] = build_root

    cmd = [
        "cargo", "build", 
        "--target", target, 
        "--manifest-path", os.path.join(rust_dir, "Cargo.toml")
    ]
    
    if not debug:
        cmd.insert(2, "--release")
    if cargo_extra_args:
        cmd[2:2] = cargo_extra_args
    
    if features:
        cmd += ["--no-default-features", "--features", ",".join(features)]

    print("Building example component log (cargo)…")
    try:
        res = subprocess.run(cmd, cwd=rust_dir, env=env, capture_output=True, text=True)
    except FileNotFoundError:
        print("Error: cargo executable not found. Please install Rust/Cargo and ensure it is in PATH.")
        return None
    
    if res.returncode != 0:
        print(f"Warning: Example component build failed for {rust_dir}")
        print(f"Target: {target}")
        print(f"Command: {' '.join(cmd)}")
        print(f"Return code: {res.returncode}")
        if res.stdout:
            print(res.stdout)
        if res.stderr:
            print(res.stderr)
        return None

    mode = "debug" if debug else "release"
    
    # Try target-specific path first, then fallback to direct path
    artifact_name = get_component_staticlib_artifact_name(rust_dir)
    lib_path = os.path.join(build_root, target, mode, artifact_name)
    if os.path.isfile(lib_path) and os.path.getsize(lib_path) > 0:
        print("Example component log built successfully")
        return lib_path
    
    print("Warning: Rust component static library artifact not found, is not a file, or is empty")
    print(f"Expected: {lib_path}")
    return None


def build_example_component(cwd, has_func, rtconfig, build_root=None):
    """
    Build the example component.
    
    Args:
        cwd: Current working directory (component directory)
        has_func: Function to check if a configuration is enabled
        rtconfig: RT-Thread configuration module
        build_root: Optional build root directory
        
    Returns:
        tuple: (LIBS, LIBPATH, LINKFLAGS) for SCons
    """
    LIBS = []
    LIBPATH = []
    LINKFLAGS = []

    # Import build support functions
    import sys
    tools_dir = os.path.abspath(os.path.join(cwd, '..', '..', 'tools'))
    if tools_dir not in sys.path:
        sys.path.append(tools_dir)
    from build_support import (
        detect_rust_target,
        ensure_rust_target_installed,
        collect_features,
        make_rustflags,
        make_cargo_build_std_args,
    )
    
    target = detect_rust_target(has_func, rtconfig)
    if not target:
        raise ComponentBuildError(f'Could not detect Rust target for example component build in {cwd}')
    
    # Build mode and features
    debug = bool(has_func('RUST_DEBUG_BUILD'))
    features = collect_features(has_func)
    
    # Build the component registry
    registry_dir = os.path.join(cwd, 'component_registry')
    features += collect_component_features(has_func, registry_dir)
    features = filter_declared_component_features(registry_dir, features)
    
    rustflags = make_rustflags(rtconfig, target)
    cargo_extra_args = make_cargo_build_std_args(rtconfig, target)
    build_root = normalize_component_build_root(build_root, cwd)
    if not ensure_rust_target_installed(target):
        raise ComponentBuildError(f"Rust target '{target}' is not installed; example component build failed")
    
    rust_lib = cargo_build_component_staticlib(
        rust_dir=registry_dir, 
        target=target, 
        features=features, 
        debug=debug, 
        rustflags=rustflags,
        build_root=build_root,
        cargo_extra_args=cargo_extra_args
    )
    
    if rust_lib:
        lib_dir = os.path.dirname(rust_lib)
        # Derive the link name from the actual artifact so it always matches
        # the file that was built. Only fall back to re-parsing Cargo.toml when
        # the artifact name does not follow the lib<name>.a convention.
        link_lib_name = get_staticlib_link_name_from_artifact(rust_lib)
        if not link_lib_name:
            link_lib_name = get_component_staticlib_link_name(registry_dir)
        LIBS = [link_lib_name]
        LIBPATH = [lib_dir]
        platform = getattr(rtconfig, 'PLATFORM', None)
        if platform == 'armclang':
            if not (os.path.isfile(rust_lib) and os.path.getsize(rust_lib) > 0):
                raise ComponentBuildError(
                    f"ArmClang Rust component link requires a non-empty archive, but got: {rust_lib}"
                )
            anchors = get_component_export_symbols(features)
            LINKFLAGS = [f"--undefined={symbol}" for symbol in anchors]
            LINKFLAGS.append(quote_spaces(os.fspath(rust_lib)))
            LINKFLAGS = " " + " ".join(LINKFLAGS)
            LIBS = []
            LIBPATH = []
        else:
            LINKFLAGS = [
                quote_spaces(f"-L{os.fspath(lib_dir)}"),
                "-Wl,--whole-archive",
                f"-l{link_lib_name}",
                "-Wl,--no-whole-archive",
                "-Wl,--allow-multiple-definition",
            ]
            LINKFLAGS = " " + " ".join(LINKFLAGS)
        print('Example component registry library linked successfully')
    else:
        raise ComponentBuildError(f"Failed to build example component registry library in {registry_dir} for target {target}")
    
    return LIBS, LIBPATH, LINKFLAGS

import os
import subprocess


# Configuration to feature mapping table for components
# This table defines which RT-Thread configurations should enable which component features
# All feature configurations are now defined in feature_config_component.py
CONFIG_COMPONENT_FEATURE_MAP = {}


class ComponentBuildError(Exception):
    pass


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
        if has_func(config_name):
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

def cargo_build_component_staticlib(rust_dir, target, features, debug, rustflags=None, build_root=None):
    """
    Build a Rust component as a static library using Cargo.
    
    Args:
        rust_dir: Directory containing the Rust component
        target: Rust target architecture
        features: List of features to enable
        debug: Whether this is a debug build
        rustflags: Additional Rust compilation flags
        build_root: Build root directory (if not provided, will raise error)
        
    Returns:
        str: Path to the built library file, or None if build failed
    """
    if not build_root:
        raise ComponentBuildError("build_root parameter is required")
    
    build_root = os.path.abspath(build_root)
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
    
    if features:
        cmd += ["--no-default-features", "--features", ",".join(features)]

    print("Building example component log (cargo)…")
    res = subprocess.run(cmd, cwd=rust_dir, env=env, capture_output=True, text=True)
    
    if res.returncode != 0:
        print("Warning: Example component build failed")
        if res.stderr:
            print(res.stderr)
        return None

    mode = "debug" if debug else "release"
    
    # Try target-specific path first, then fallback to direct path
    lib_path = os.path.join(build_root, target, mode, "libem_component_registry.a")
    if os.path.exists(lib_path):
        print("Example component log built successfully")
        return lib_path
    
    print("Warning: Library not found at expected location")
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
    LINKFLAGS = ""
    
    # Import build support functions
    import sys
    sys.path.append(os.path.join(cwd, '../rust/tools'))
    from build_support import (
        detect_rust_target,
        make_rustflags,
    )
    
    target = detect_rust_target(has_func, rtconfig)
    
    # Build mode and features
    debug = bool(has_func('RUST_DEBUG_BUILD'))
    
    # Build the component registry
    registry_dir = os.path.join(cwd, 'component_registry')
    features = collect_component_features(has_func, registry_dir)
    
    rustflags = make_rustflags(rtconfig, target)
    
    rust_lib = cargo_build_component_staticlib(
        rust_dir=registry_dir, 
        target=target, 
        features=features, 
        debug=debug, 
        rustflags=rustflags,
        build_root=build_root
    )
    
    if rust_lib:
        LIBS = ['em_component_registry']
        LIBPATH = [os.path.dirname(rust_lib)]
        # Add LINKFLAGS to ensure component is linked into final binary
        LINKFLAGS += " -Wl,--whole-archive -lem_component_registry -Wl,--no-whole-archive"
        LINKFLAGS += " -Wl,--allow-multiple-definition"
        print('Example component registry library linked successfully')
    else:
        print('Warning: Failed to build example component registry library')
    
    return LIBS, LIBPATH, LINKFLAGS
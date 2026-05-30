import os
import subprocess
import toml
import shutil


# Configuration to feature mapping table
# This table defines which RT-Thread configurations should enable which Rust features
# All feature configurations are now defined in feature_config_examples.py
CONFIG_FEATURE_MAP = {}

# Application directory to Kconfig mapping table
# This table defines which Kconfig options control which application directories
APP_CONFIG_MAP = {
    'fs': 'RT_RUST_EXAMPLE_FS',
    'loadlib': 'RT_RUST_EXAMPLE_LOADLIB', 
    'mutex': 'RT_RUST_EXAMPLE_MUTEX',
    'param': 'RT_RUST_EXAMPLE_PARAM',
    'queue': 'RT_RUST_EXAMPLE_QUEUE',
    'semaphore': 'RT_RUST_EXAMPLE_SEMAPHORE',
    'thread': 'RT_RUST_EXAMPLE_THREAD'
}


def should_build_app(app_dir, has_func):
    """
    Check if an application should be built based on Kconfig configuration
    
    Args:
        app_dir: Application directory path
        has_func: Function to check if a configuration is enabled
        
    Returns:
        bool: True if the application should be built
    """
    # Get the application name from the directory
    app_name = os.path.basename(app_dir)
    
    # Check if there's a specific Kconfig option for this app
    if app_name in APP_CONFIG_MAP:
        config_option = APP_CONFIG_MAP[app_name]
        return has_func(config_option)
    
    # If no specific config found, check if applications are enabled in general
    return has_func('RT_RUST_BUILD_APPLICATIONS')


def check_app_dependencies(app_dir, required_dependencies):
    """
    Check if an application has the required dependencies
    
    Args:
        app_dir: Application directory path
        required_dependencies: List of dependency names to check
        
    Returns:
        bool: True if all required dependencies are present
    """
    if not app_dir or not required_dependencies:
        return True
    
    cargo_toml_path = os.path.join(app_dir, 'Cargo.toml')
    if not os.path.exists(cargo_toml_path):
        return False
    
    try:
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


def collect_features(has_func, app_dir=None):
    """
    Collect Rust features based on RT-Thread configuration using extensible mapping table
    
    Args:
        has_func: Function to check if a configuration is enabled
        app_dir: Application directory to check dependencies (optional)
        
    Returns:
        list: List of features to enable
    """
    features = []
    
    # Iterate through all configured mappings
    for config_name, config_info in CONFIG_FEATURE_MAP.items():
        # Check if this RT-Thread configuration is enabled
        if has_func(config_name):
            feature_name = config_info['feature']
            required_deps = config_info.get('dependencies', [])
            
            # If app_dir is provided, check dependencies
            if app_dir:
                if check_app_dependencies(app_dir, required_deps):
                    features.append(feature_name)
                    print(f"Enabling feature '{feature_name}' for {config_name} in {os.path.basename(app_dir)}")
            else:
                # If no app_dir provided, enable for all (backward compatibility)
                features.append(feature_name)
                print(f"Enabling feature '{feature_name}' for {config_name}")
    
    return features





class UserAppBuildError(Exception):
    """User application build error exception"""
    pass


def parse_cargo_toml(cargo_toml_path):
    """
    Parse Cargo.toml file to extract library name and library type
    
    Args:
        cargo_toml_path: Path to Cargo.toml file
        
    Returns:
        tuple: (lib_name, is_staticlib)
    """
    try:
        with open(cargo_toml_path, 'r') as f:
            cargo_data = toml.load(f)
        
        package_name = cargo_data.get('package', {}).get('name')
        if not package_name:
            raise UserAppBuildError(f"No package name found in {cargo_toml_path}")
        
        lib_config = cargo_data.get('lib', {})
        crate_type = lib_config.get('crate-type', [])
        is_staticlib = 'staticlib' in crate_type
        
        # Use lib name if specified, otherwise use package name
        lib_name = lib_config.get('name', package_name)
        
        return lib_name, is_staticlib
        
    except Exception as e:
        raise UserAppBuildError(f"Failed to parse {cargo_toml_path}: {e}")


def discover_user_apps(base_dir):
    """
    Discover all user application directories
    
    Args:
        base_dir: Base directory path
        
    Returns:
        list: List of directories containing Cargo.toml
    """
    user_apps = []
    
    for root, dirs, files in os.walk(base_dir):
        if 'Cargo.toml' in files:
            if 'target' in root or 'build' in root:
                continue
            user_apps.append(root)
    
    return user_apps


def build_user_app(app_dir, target, debug, rustflags, build_root, features=None):
    """
    Build a single user application
    
    Args:
        app_dir: Application directory
        target: Rust target architecture
        debug: Whether this is a debug build
        rustflags: Rust compilation flags
        build_root: Build root directory
        features: List of features to enable
        
    Returns:
        tuple: (success, lib_name, lib_path)
    """
    try:
        cargo_toml_path = os.path.join(app_dir, 'Cargo.toml')
        lib_name, is_staticlib = parse_cargo_toml(cargo_toml_path)
        
        if not is_staticlib:
            return False, None, None
        
        env = os.environ.copy()
        env['RUSTFLAGS'] = rustflags
        env['CARGO_TARGET_DIR'] = build_root
        
        cmd = ['cargo', 'build', '--target', target]
        if not debug:
            cmd.append('--release')
        
        # Add features if specified
        if features:
            cmd.extend(['--features', ','.join(features)])
        
        print(f"Building example user app {lib_name} (cargo)…")
        result = subprocess.run(cmd, cwd=app_dir, env=env, 
                              capture_output=True, text=True)
        
        if result.returncode != 0:
            print(f"Failed to build user app in {app_dir}")
            print(f"Command: {' '.join(cmd)}")
            print(f"Return code: {result.returncode}")
            print(f"STDOUT: {result.stdout}")
            print(f"STDERR: {result.stderr}")
            return False, None, None
        
        lib_file = find_library_file(build_root, target, lib_name, debug)
        if lib_file:
            # Return the library name for linking
            return True, lib_name, lib_file
        else:
            print(f"Library file not found for lib {lib_name}")
            return False, None, None
            
    except Exception as e:
        print(f"Exception occurred while building user app in {app_dir}: {e}")
        return False, None, None


def find_library_file(build_root, target, lib_name, debug):
    """
    Find the generated library file
    
    Args:
        build_root: Build root directory
        target: Rust target architecture
        lib_name: Library name
        debug: Whether this is a debug build
        
    Returns:
        str: Library file path, or None if not found
    """
    profile = "debug" if debug else "release"
    
    possible_names = [
        f"lib{lib_name}.a",
        f"lib{lib_name.replace('-', '_')}.a"
    ]
    
    search_paths = [
        os.path.join(build_root, target, profile),
        os.path.join(build_root, target, profile, "deps")
    ]
    
    for search_path in search_paths:
        if not os.path.exists(search_path):
            continue
                    
        for name in possible_names:
            lib_path = os.path.join(search_path, name)
            if os.path.exists(lib_path):
                return lib_path
    
    return None


def build_all_user_apps(base_dir, target, debug, rustflags, build_root, has_func):
    """
    Build all user applications
    
    Args:
        base_dir: User applications base directory
        target: Rust target architecture
        debug: Whether this is a debug build
        rustflags: Rust compilation flags
        build_root: Build root directory
        has_func: Function to check if a configuration is enabled
        
    Returns:
        tuple: (LIBS, LIBPATH, success_count, total_count)
    """
    LIBS = []
    LIBPATH = []
    success_count = 0
    
    user_apps = discover_user_apps(base_dir)
    total_count = len(user_apps)
    
    for app_dir in user_apps:
        # Check if this application should be built based on Kconfig
        if not should_build_app(app_dir, has_func):
            app_name = os.path.basename(app_dir)
            print(f"Skipping {app_name} (disabled in Kconfig)")
            continue
            
        # Collect features for this specific app
        features = collect_features(has_func, app_dir)
        success, lib_name, lib_path = build_user_app(app_dir, target, debug, rustflags, build_root, features)
        
        if success and lib_path:
            app_name = os.path.basename(app_dir)
            print(f"Example user app {app_name} built successfully")
            LIBS.append(lib_name)
            lib_dir = os.path.dirname(lib_path)
            if lib_dir not in LIBPATH:
                LIBPATH.append(lib_dir)
            success_count += 1
    
    return LIBS, LIBPATH, success_count, total_count


def generate_linkflags(LIBS, LIBPATH):
    """
    Generate link flags
    
    Args:
        LIBS: List of library names
        LIBPATH: List of library paths
        
    Returns:
        str: Link flags string
    """
    if not LIBS or not LIBPATH:
        return ""
    
    linkflags = f" -L{LIBPATH[0]} -Wl,--whole-archive"
    for lib in LIBS:
        linkflags += f" -l{lib}"
    linkflags += " -Wl,--no-whole-archive -Wl,--allow-multiple-definition"
    
    return linkflags


def clean_user_apps_build(build_root):
    """
    Clean user applications build artifacts
    
    Args:
        build_root: Build root directory
    """
    if os.path.exists(build_root):
        shutil.rmtree(build_root)


def build_example_usrapp(cwd, has_func, rtconfig, build_root=None):
    """
    Build the example user applications.
    
    Args:
        cwd: Current working directory (usrapp directory)
        has_func: Function to check if a configuration is enabled
        rtconfig: RT-Thread configuration module
        build_root: Optional build root directory
        
    Returns:
        tuple: (LIBS, LIBPATH, LINKFLAGS) for SCons
    """
    LIBS = []
    LIBPATH = []
    LINKFLAGS = ""
    
    try:
        # Import build support functions
        import sys
        sys.path.append(os.path.join(cwd, '../rust/tools'))
        import build_support as rust_build_support
        
        target = rust_build_support.detect_rust_target(has_func, rtconfig)
        debug = bool(has_func('RUST_DEBUG_BUILD'))
        rustflags = rust_build_support.make_rustflags(rtconfig, target)
        LIBS, LIBPATH, success_count, total_count = build_all_user_apps(
            cwd, target, debug, rustflags, build_root, has_func
        )
        
        if success_count == 0 and total_count > 0:
            print(f'Warning: Failed to build all {total_count} user applications')
        elif success_count > 0:
            LINKFLAGS = generate_linkflags(LIBS, LIBPATH)
            print(f'Example user apps linked successfully')
            
    except UserAppBuildError as e:
        print(f'Error: {e}')
    except Exception as e:
        print(f'Unexpected error during user apps build: {e}')
    
    return LIBS, LIBPATH, LINKFLAGS
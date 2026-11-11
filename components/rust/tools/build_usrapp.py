import os
import subprocess
import shutil
from SCons.Subst import quote_spaces


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

APP_DEPENDENCY_MAP = {
    'loadlib': ['RT_USING_MODULE'],
}

APP_EXPORT_SYMBOL_MAP = {
    'fs':        ['__rust_file_demo_cmd_seg'],
    'loadlib':   ['__rust_dl_demo_cmd_seg'],
    'mutex':     ['__rust_mutex_demo_cmd_seg'],
    'param':     ['__rust_param_demo_cmd_seg'],
    'queue':     ['__rust_queue_demo_cmd_seg'],
    'semaphore': ['__rust_sem_demo_cmd_seg'],
    'thread':    ['__rust_thread_demo_cmd_seg'],
}


def app_dependencies_satisfied(app_name, has_func):
    if app_name == 'fs':
        if has_func('RT_USING_POSIX_FS'):
            return True
        if not has_func('RT_USING_DFS'):
            return False
        return has_func('DFS_USING_POSIX') or has_func('RT_USING_DFS_V2')

    for dep in APP_DEPENDENCY_MAP.get(app_name, []):
        if not has_func(dep):
            return False

    return True


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

    if not app_dependencies_satisfied(app_name, has_func):
        return False

    if has_func('RT_RUST_BUILD_ALL_EXAMPLES'):
        return True
    
    # Check if there's a specific Kconfig option for this app
    if app_name in APP_CONFIG_MAP:
        config_option = APP_CONFIG_MAP[app_name]
        return has_func(config_option)
    
    # If no specific config found, check if applications are enabled in general
    return has_func('RT_RUST_BUILD_APPLICATIONS')


def get_app_export_symbols(app_dir):
    app_name = os.path.basename(app_dir)
    if app_name not in APP_EXPORT_SYMBOL_MAP:
        raise UserAppBuildError(
            f"No link anchor metadata registered for enabled user app '{app_name}'. "
            f"Path: {app_dir}. Add its export anchor to APP_EXPORT_SYMBOL_MAP."
        )
    return list(APP_EXPORT_SYMBOL_MAP[app_name])


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
        toml = load_toml_module()
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


def app_has_feature_dependency(app_dir, feature_name, dependency_name):
    cargo_toml_path = os.path.join(app_dir, 'Cargo.toml')
    if not os.path.exists(cargo_toml_path):
        return False

    try:
        toml = load_toml_module()
        with open(cargo_toml_path, 'r') as f:
            cargo_data = toml.load(f)

        features = cargo_data.get('features', {})
        dependencies = cargo_data.get('dependencies', {})
        return feature_name in features and dependency_name in dependencies

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

    if app_dir and os.path.basename(app_dir) == 'fs':
        if app_has_feature_dependency(app_dir, 'enable-log', 'em_component_log') and 'enable-log' not in features:
            features.append('enable-log')
    
    return features





class UserAppBuildError(Exception):
    """User application build error exception"""
    pass


def load_toml_module():
    try:
        import toml
        return toml
    except ImportError as e:
        raise UserAppBuildError("Missing toml module required to parse Cargo.toml") from e


def normalize_build_root(build_root, cwd):
    """
    Normalize the user application build root directory.

    Args:
        build_root: Optional build root directory
        cwd: Current working directory (usrapp directory)

    Returns:
        str: Absolute build root path
    """
    if build_root is None:
        if not cwd:
            raise UserAppBuildError("Invalid build_root: cwd is required when build_root is None")
        build_root = os.path.join(cwd, "build", "rust", "usrapp")

    try:
        build_root = os.fspath(build_root)
    except TypeError:
        raise UserAppBuildError("Invalid build_root: expected a non-empty path")

    if not isinstance(build_root, str) or not build_root:
        raise UserAppBuildError("Invalid build_root: expected a non-empty path")

    return os.path.abspath(build_root)


def parse_cargo_toml(cargo_toml_path):
    """
    Parse Cargo.toml file to extract library name and library type
    
    Args:
        cargo_toml_path: Path to Cargo.toml file
        
    Returns:
        tuple: (lib_name, is_staticlib)
    """
    try:
        toml = load_toml_module()
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
        dirs[:] = [d for d in dirs if d not in ("build", "target")]
        if 'Cargo.toml' in files:
            user_apps.append(root)
    
    return user_apps


def staticlib_candidates(lib_name):
    normalized_name = lib_name.replace('-', '_')
    candidates = [(f"lib{normalized_name}.a", normalized_name)]

    if normalized_name != lib_name:
        candidates.append((f"lib{lib_name}.a", lib_name))

    return candidates


def build_user_app(app_dir, target, debug, rustflags, build_root, features=None, cargo_extra_args=None):
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
    build_root = normalize_build_root(build_root, None)

    try:
        cargo_toml_path = os.path.join(app_dir, 'Cargo.toml')
        lib_name, is_staticlib = parse_cargo_toml(cargo_toml_path)
        
        if not is_staticlib:
            raise UserAppBuildError(f"User app in {app_dir} is not configured as a staticlib")
        
        env = os.environ.copy()
        previous_rustflags = env.get('RUSTFLAGS', '').strip()
        new_rustflags = rustflags.strip() if rustflags else ''
        if previous_rustflags and new_rustflags:
            env['RUSTFLAGS'] = f'{previous_rustflags} {new_rustflags}'
        elif new_rustflags:
            env['RUSTFLAGS'] = new_rustflags
        elif previous_rustflags:
            env['RUSTFLAGS'] = previous_rustflags
        env['CARGO_TARGET_DIR'] = build_root
        
        cmd = ['cargo', 'build', '--target', target]
        if cargo_extra_args:
            cmd[2:2] = cargo_extra_args
        if not debug:
            cmd.append('--release')
        
        # Add features if specified
        if features:
            cmd.extend(['--features', ','.join(features)])
        
        print(f"Building example user app {lib_name} (cargo)…")
        try:
            result = subprocess.run(cmd, cwd=app_dir, env=env,
                                  capture_output=True, text=True)
        except FileNotFoundError:
            print("Error: cargo executable not found. Please install Rust/Cargo and ensure it is in PATH.")
            raise UserAppBuildError(f"Cargo executable not found while building user app in {app_dir}")
        
        if result.returncode != 0:
            print(f"Failed to build user app in {app_dir}")
            print(f"Command: {' '.join(cmd)}")
            print(f"Return code: {result.returncode}")
            print(f"STDOUT: {result.stdout}")
            print(f"STDERR: {result.stderr}")
            raise UserAppBuildError(f"Failed to build user app in {app_dir}")
        
        lib_file, link_lib_name = find_library_file(build_root, target, lib_name, debug)
        if lib_file:
            # Return the library name for linking
            return True, link_lib_name, lib_file
        else:
            print(f"Library file not found for lib {lib_name}")
            raise UserAppBuildError(f"Library file not found for user app {lib_name}")
            
    except UserAppBuildError:
        raise
    except Exception as e:
        raise UserAppBuildError(f"Exception occurred while building user app in {app_dir}: {e}") from e


def find_library_file(build_root, target, lib_name, debug):
    """
    Find the generated library file
    
    Args:
        build_root: Build root directory
        target: Rust target architecture
        lib_name: Library name
        debug: Whether this is a debug build
        
    Returns:
        tuple: (library file path, link library name), or (None, None) if not found
    """
    build_root = normalize_build_root(build_root, None)
    profile = "debug" if debug else "release"

    search_paths = [
        os.path.join(build_root, target, profile),
        os.path.join(build_root, target, profile, "deps")
    ]
    
    for search_path in search_paths:
        if not os.path.exists(search_path):
            continue
                    
        for name, link_lib_name in staticlib_candidates(lib_name):
            lib_path = os.path.join(search_path, name)
            if os.path.exists(lib_path):
                if os.path.isfile(lib_path) and os.path.getsize(lib_path) > 0:
                    return lib_path, link_lib_name
                print(f"Warning: Rust user app static library artifact not found, is not a file, or is empty: {lib_path}")
    
    return None, None


def build_all_user_apps(base_dir, target, debug, rustflags, build_root, has_func, require_export_symbols=False, cargo_extra_args=None):
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
    LIBFILES = []
    UNDEFINED_SYMBOLS = []
    success_count = 0
    total_count = 0
    
    user_apps = discover_user_apps(base_dir)
    
    for app_dir in user_apps:
        # Check if this application should be built based on Kconfig
        if not should_build_app(app_dir, has_func):
            app_name = os.path.basename(app_dir)
            print(f"Skipping {app_name} (disabled in Kconfig)")
            continue

        total_count += 1
            
        # Collect features for this specific app
        features = collect_features(has_func, app_dir)
        success, lib_name, lib_path = build_user_app(app_dir, target, debug, rustflags, build_root, features, cargo_extra_args)
        
        if success and lib_path:
            app_name = os.path.basename(app_dir)
            print(f"Example user app {app_name} built successfully")
            LIBS.append(lib_name)
            LIBFILES.append(lib_path)
            if require_export_symbols:
                UNDEFINED_SYMBOLS.extend(get_app_export_symbols(app_dir))
            lib_dir = os.path.dirname(lib_path)
            if lib_dir not in LIBPATH:
                LIBPATH.append(lib_dir)
            success_count += 1
        else:
            raise UserAppBuildError(f"Failed to build enabled user app: {app_dir}")
    
    return LIBS, LIBPATH, LIBFILES, UNDEFINED_SYMBOLS, success_count, total_count


def generate_linkflags(LIBS, LIBPATH, platform, LIBFILES=None, UNDEFINED_SYMBOLS=None):
    """
    Generate link flags
    
    Args:
        LIBS: List of library names
        LIBPATH: List of library paths
        
    Returns:
        str: Link flags string
    """
    if platform == 'armclang':
        if not LIBFILES:
            raise UserAppBuildError(
                "ArmClang Rust link requires built static library archives, but none were produced"
            )
        for lib in LIBFILES:
            if not (os.path.isfile(lib) and os.path.getsize(lib) > 0):
                raise UserAppBuildError(
                    f"ArmClang Rust link requires a non-empty archive, but got: {lib}"
                )
        if not UNDEFINED_SYMBOLS:
            raise UserAppBuildError(
                "ArmClang Rust link requires at least one --undefined anchor symbol, but none were resolved"
            )
        linkflags = [f"--undefined={symbol}" for symbol in UNDEFINED_SYMBOLS]
        linkflags.extend(quote_spaces(os.fspath(lib)) for lib in LIBFILES)
        return " " + " ".join(linkflags)

    if not LIBS or not LIBPATH:
        return ""

    linkflags = []
    for path in LIBPATH:
        linkflags.append(quote_spaces(f"-L{os.fspath(path)}"))
    linkflags.append("-Wl,--whole-archive")
    for lib in LIBS:
        linkflags.append(f"-l{lib}")
    linkflags.extend([
        "-Wl,--no-whole-archive",
        "-Wl,--allow-multiple-definition",
    ])
    
    return " " + " ".join(linkflags)


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
        tools_dir = os.path.abspath(os.path.join(cwd, '..', '..', 'tools'))
        if tools_dir not in sys.path:
            sys.path.append(tools_dir)
        import build_support as rust_build_support

        build_root = normalize_build_root(build_root, cwd)
        enabled_apps = [
            app_dir for app_dir in discover_user_apps(cwd)
            if should_build_app(app_dir, has_func)
        ]
        if not enabled_apps:
            print('No user applications enabled for Rust build')
            return LIBS, LIBPATH, LINKFLAGS

        target = rust_build_support.detect_rust_target(has_func, rtconfig)
        if not target:
            raise UserAppBuildError('Could not detect Rust target for user application build')
        debug = bool(has_func('RUST_DEBUG_BUILD'))
        rustflags = rust_build_support.make_rustflags(rtconfig, target)
        cargo_extra_args = rust_build_support.make_cargo_build_std_args(rtconfig, target)
        if not rust_build_support.ensure_rust_target_installed(target):
            raise UserAppBuildError('Rust target is not installed; user application build failed')

        platform = getattr(rtconfig, 'PLATFORM', None)
        LIBS, LIBPATH, LIBFILES, UNDEFINED_SYMBOLS, success_count, total_count = build_all_user_apps(
            cwd, target, debug, rustflags, build_root, has_func, platform == 'armclang', cargo_extra_args
        )
        
        if success_count > 0:
            LINKFLAGS = generate_linkflags(LIBS, LIBPATH, platform, LIBFILES, UNDEFINED_SYMBOLS)
            if platform == 'armclang':
                LIBS = []
                LIBPATH = []
            print('Example user apps linked successfully')
        else:
            print('No user applications enabled for Rust build')
            
    except UserAppBuildError:
        raise
    except Exception as e:
        raise UserAppBuildError(f'Unexpected error during user apps build: {e}') from e
    
    return LIBS, LIBPATH, LINKFLAGS

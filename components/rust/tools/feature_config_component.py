import sys
import os
from building import *
cwd = GetCurrentDir()
sys.path.append(os.path.join(cwd, 'tools'))
from build_component import CONFIG_COMPONENT_FEATURE_MAP

def setup_all_component_features():
    """
    Setup all component feature mappings.
    This function configures which RT-Thread configurations should enable which component features.
    """
    
    CONFIG_COMPONENT_FEATURE_MAP.update({
        'RUST_LOG_COMPONENT': {
            'feature': 'enable-log',
            'dependencies': ['em_component_log'],
            'description': 'Enable Rust logging component integration'
        },
    })
    
    print("All component feature mappings have been configured!")


if __name__ == "__main__":
    setup_all_component_features()
    print(f"Total component configurations: {len(CONFIG_COMPONENT_FEATURE_MAP)}")
    print("Available component configurations:")
    for config, info in CONFIG_COMPONENT_FEATURE_MAP.items():
        print(f"  {config}: {info['feature']} - {info['description']}")
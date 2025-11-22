import sys
import os
from building import *
cwd = GetCurrentDir()
sys.path.append(os.path.join(cwd, 'tools'))
from build_usrapp import CONFIG_FEATURE_MAP

def setup_all_example_features():
    
    CONFIG_FEATURE_MAP.update({
        'RUST_LOG_COMPONENT': {
            'feature': 'enable-log',
            'dependencies': ['em_component_log'],
            'description': 'Enable Rust logging component integration'
        },
    })
    
    print("All example feature mappings have been configured!")


if __name__ == "__main__":
    setup_all_example_features()
    print(f"Total configurations: {len(CONFIG_FEATURE_MAP)}")
    print("Available configurations:")
    for config, info in CONFIG_FEATURE_MAP.items():
        print(f"  {config}: {info['feature']} - {info['description']}")
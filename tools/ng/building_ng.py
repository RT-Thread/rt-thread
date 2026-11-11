# -*- coding: utf-8 -*-
"""
Next Generation building.py with minimal modifications.

This file shows how to integrate the new OOP system with minimal changes to building.py.
The actual implementation would modify the original building.py file.
"""

# Import everything from original building.py
import sys
import os

# Add parent directory to path to import original building
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from building import *

# Import new OOP modules
from ng.adapter import (
    init_build_context,
    inject_environment_methods,
    load_rtconfig as ng_load_rtconfig,
    GenerateProject as ng_GenerateProject
)


# Override PrepareBuilding to integrate new system
_original_PrepareBuilding = PrepareBuilding

def PrepareBuilding(env, root_directory, has_libcpu=False, remove_components=[]):
    """
    Enhanced PrepareBuilding that integrates the new OOP system.
    
    This function wraps the original PrepareBuilding and adds OOP functionality.
    """
    # Initialize new build context
    context = init_build_context(root_directory)
    
    # Call original PrepareBuilding
    result = _original_PrepareBuilding(env, root_directory, has_libcpu, remove_components)
    
    # Inject new methods into environment
    inject_environment_methods(env)
    
    # Load configuration into new system
    ng_load_rtconfig('rtconfig.h')
    
    # Store context in environment for access
    env['_BuildContext'] = context
    
    return result


# Override DefineGroup to use new implementation
_original_DefineGroup = DefineGroup

def DefineGroup(name, src, depend, **parameters):
    """
    Enhanced DefineGroup that uses the new OOP implementation.
    
    This maintains backward compatibility while using the new system internally.
    """
    # Get environment from global Env
    global Env
    if Env and hasattr(Env, 'DefineGroup'):
        # Use new method if available
        return Env.DefineGroup(name, src, depend, **parameters)
    else:
        # Fallback to original
        return _original_DefineGroup(name, src, depend, **parameters)


# Override GetDepend to use new implementation
_original_GetDepend = GetDepend

def GetDepend(depend):
    """
    Enhanced GetDepend that uses the new OOP implementation.
    """
    global Env
    if Env and hasattr(Env, 'GetDepend'):
        # Use new method if available
        return Env.GetDepend(depend)
    else:
        # Fallback to original
        return _original_GetDepend(depend)


# Override DoBuilding to integrate project generation
_original_DoBuilding = DoBuilding

def DoBuilding(target, objects):
    """
    Enhanced DoBuilding that integrates new project generation.
    """
    # Call original DoBuilding
    _original_DoBuilding(target, objects)
    
    # Handle project generation with new system
    if GetOption('target'):
        target_name = GetOption('target')
        global Env, Projects
        
        # Use new generator if available
        try:
            ng_GenerateProject(target_name, Env, Projects)
        except Exception as e:
            print(f"Falling back to original generator: {e}")
            # Call original GenTargetProject
            from building import GenTargetProject
            GenTargetProject(Projects, program=target)


# Export enhanced functions
__all__ = ['PrepareBuilding', 'DefineGroup', 'GetDepend', 'DoBuilding'] + \
          [name for name in dir(sys.modules['building']) if not name.startswith('_')]
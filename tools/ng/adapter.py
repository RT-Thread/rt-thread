# -*- coding: utf-8 -*-
"""
Adapter module to integrate new OOP implementation with existing building.py.

This module provides the bridge between the legacy function-based API and the new
object-oriented implementation, ensuring backward compatibility.
"""

import os
from typing import List, Dict, Any, Optional

from .core import BuildContext
from .environment import RTEnv
from .generator import GeneratorConfig, GeneratorRegistry


# Global variables for compatibility
_context: Optional[BuildContext] = None


def init_build_context(root_directory: str) -> BuildContext:
    """
    Initialize the build context.
    
    This function should be called early in PrepareBuilding.
    
    Args:
        root_directory: RT-Thread root directory
        
    Returns:
        BuildContext instance
    """
    global _context
    _context = BuildContext(root_directory)
    return _context


def get_build_context() -> Optional[BuildContext]:
    """Get the current build context."""
    return _context


def inject_environment_methods(env) -> None:
    """
    Inject RT-Thread methods into SCons Environment.
    
    This should be called in PrepareBuilding after environment setup.
    
    Args:
        env: SCons Environment object
    """
    RTEnv.inject_methods(env)
    
    # Also set the environment in context
    if _context:
        _context.prepare_environment(env)


def load_rtconfig(config_file: str = 'rtconfig.h') -> Dict[str, Any]:
    """
    Load configuration from rtconfig.h.
    
    Args:
        config_file: Configuration file name
        
    Returns:
        Dictionary of build options
    """
    if _context:
        _context.load_configuration(config_file)
        return _context.build_options
    return {}


def DefineGroup(name: str, src: List[str], depend: Any = None, **kwargs) -> List:
    """
    Legacy DefineGroup function for backward compatibility.
    
    This function delegates to the environment method.
    
    Args:
        name: Group name
        src: Source files
        depend: Dependencies
        **kwargs: Additional parameters
        
    Returns:
        List of build objects
    """
    if _context and _context.environment:
        return _context.environment.DefineGroup(name, src, depend, **kwargs)
    else:
        # Fallback behavior
        print(f"Warning: DefineGroup called before environment setup for group '{name}'")
        return []


def GetDepend(depend: Any) -> bool:
    """
    Legacy GetDepend function for backward compatibility.
    
    Args:
        depend: Dependency to check
        
    Returns:
        True if dependency is satisfied
    """
    if _context:
        return _context.get_dependency(depend)
    return False


def GetCurrentDir() -> str:
    """
    Get current directory.
    
    Returns:
        Current directory path
    """
    return os.path.abspath('.')


def SrcRemove(src: List[str], remove: List[str]) -> None:
    """
    Remove files from source list.
    
    Args:
        src: Source list (modified in place)
        remove: Files to remove
    """
    if not isinstance(remove, list):
        remove = [remove]
        
    for item in remove:
        if item in src:
            src.remove(item)


def GetBuildOptions() -> Dict[str, Any]:
    """
    Get build options.
    
    Returns:
        Dictionary of build options
    """
    if _context:
        return _context.build_options
    return {}


def MergeGroups() -> List:
    """
    Merge all registered groups.
    
    Returns:
        List of all build objects
    """
    if _context:
        return _context.merge_groups()
    return []


def GenerateProject(target: str, env, projects: List) -> None:
    """
    Generate IDE project files.
    
    Args:
        target: Target type (mdk5, iar, vscode, etc.)
        env: SCons Environment
        projects: Project list
    """
    if not _context:
        print("Error: Build context not initialized")
        return
        
    # Get project info from registry
    project_info = _context.project_registry.get_project_info()
    
    # Create generator config
    config = GeneratorConfig(
        output_dir=os.getcwd(),
        project_name=os.path.basename(os.getcwd()),
        target_name="rtthread.elf"
    )
    
    # Create and run generator
    try:
        generator = _context.generator_registry.create_generator(target, config)
        if generator.generate(_context, project_info):
            print(f"Successfully generated {target} project files")
        else:
            print(f"Failed to generate {target} project files")
    except Exception as e:
        print(f"Error generating {target} project: {e}")


def PrepareModuleBuilding(env, root_directory, bsp_directory) -> None:
    """
    Prepare for building a module.
    
    This is a simplified version of PrepareBuilding for module compilation.
    
    Args:
        env: SCons Environment
        root_directory: RT-Thread root directory
        bsp_directory: BSP directory
    """
    # Initialize context
    context = init_build_context(root_directory)
    context.bsp_directory = bsp_directory
    
    # Inject methods
    inject_environment_methods(env)
    
    # Load configuration
    config_path = os.path.join(bsp_directory, 'rtconfig.h')
    if os.path.exists(config_path):
        load_rtconfig(config_path)
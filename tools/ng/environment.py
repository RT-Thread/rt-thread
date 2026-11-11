# -*- coding: utf-8 -*-
"""
Environment extensions for RT-Thread build system.

This module provides methods that are injected into the SCons Environment object
to provide RT-Thread-specific functionality.
"""

import os
from typing import List, Union, Dict, Any, Optional
from SCons.Script import *

from .core import BuildContext
from .project import ProjectGroup


class RTEnv:
    """
    RT-Thread environment extensions (RTEnv).
    
    This class provides methods that are added to the SCons Environment object.
    """
    
    @staticmethod
    def inject_methods(env):
        """
        Inject RT-Thread methods into SCons Environment.
        
        Args:
            env: SCons Environment object
        """
        # Core build methods
        env.AddMethod(RTEnv.DefineGroup, 'DefineGroup')
        env.AddMethod(RTEnv.GetDepend, 'GetDepend')
        env.AddMethod(RTEnv.SrcRemove, 'SrcRemove')
        env.AddMethod(RTEnv.GetCurrentDir, 'GetCurrentDir')
        env.AddMethod(RTEnv.BuildPackage, 'BuildPackage')
        
        # Utility methods
        env.AddMethod(RTEnv.Glob, 'GlobFiles')
        env.AddMethod(RTEnv.GetBuildOptions, 'GetBuildOptions')
        env.AddMethod(RTEnv.GetContext, 'GetContext')
        
        # Path utilities
        env.AddMethod(RTEnv.GetRTTRoot, 'GetRTTRoot')
        env.AddMethod(RTEnv.GetBSPRoot, 'GetBSPRoot')
        
    @staticmethod
    def DefineGroup(env, name: str, src: List[str], depend: Any = None, **kwargs) -> List:
        """
        Define a component group.
        
        This method maintains compatibility with the original DefineGroup function
        while using the new object-oriented implementation.
        
        Args:
            env: SCons Environment
            name: Group name
            src: Source file list
            depend: Dependency conditions
            **kwargs: Additional parameters (CPPPATH, CPPDEFINES, etc.)
            
        Returns:
            List of build objects
        """
        context = BuildContext.get_current()
        if not context:
            raise RuntimeError("BuildContext not initialized")
            
        # Check dependencies
        if depend and not env.GetDepend(depend):
            return []
            
        # Process source files
        if isinstance(src, str):
            src = [src]
            
        # Create project group
        group = ProjectGroup(
            name=name,
            sources=src,
            dependencies=depend if isinstance(depend, list) else [depend] if depend else [],
            environment=env
        )
        
        # Process parameters
        group.include_paths = kwargs.get('CPPPATH', [])
        group.defines = kwargs.get('CPPDEFINES', {})
        group.cflags = kwargs.get('CFLAGS', '')
        group.cxxflags = kwargs.get('CXXFLAGS', '')
        group.local_cflags = kwargs.get('LOCAL_CFLAGS', '')
        group.local_cxxflags = kwargs.get('LOCAL_CXXFLAGS', '')
        group.local_include_paths = kwargs.get('LOCAL_CPPPATH', [])
        group.local_defines = kwargs.get('LOCAL_CPPDEFINES', {})
        group.libs = kwargs.get('LIBS', [])
        group.lib_paths = kwargs.get('LIBPATH', [])
        
        # Build objects
        objects = group.build(env)
        
        # Register group
        context.register_project_group(group)
        
        return objects
        
    @staticmethod
    def GetDepend(env, depend: Any) -> bool:
        """
        Check if dependency is satisfied.
        
        Args:
            env: SCons Environment
            depend: Dependency name or list of names
            
        Returns:
            True if dependency is satisfied
        """
        context = BuildContext.get_current()
        if not context:
            # Fallback to checking environment variables
            if isinstance(depend, str):
                return env.get(depend, False)
            elif isinstance(depend, list):
                return all(env.get(d, False) for d in depend)
            return False
            
        return context.get_dependency(depend)
        
    @staticmethod
    def SrcRemove(env, src: List[str], remove: List[str]) -> None:
        """
        Remove files from source list.
        
        Args:
            env: SCons Environment
            src: Source file list (modified in place)
            remove: Files to remove
        """
        if not isinstance(remove, list):
            remove = [remove]
            
        for item in remove:
            # Handle both exact matches and pattern matches
            if item in src:
                src.remove(item)
            else:
                # Try pattern matching
                import fnmatch
                to_remove = [f for f in src if fnmatch.fnmatch(f, item)]
                for f in to_remove:
                    src.remove(f)
                    
    @staticmethod
    def GetCurrentDir(env) -> str:
        """
        Get current directory.
        
        Args:
            env: SCons Environment
            
        Returns:
            Current directory path
        """
        return Dir('.').abspath
        
    @staticmethod
    def BuildPackage(env, package_path: str = None) -> List:
        """
        Build package from package.json.
        
        Args:
            env: SCons Environment
            package_path: Path to package.json. If None, looks for package.json in current directory.
            
        Returns:
            List of build objects
        """
        # Import the existing package module
        import sys
        import os
        
        # Get the building module path
        building_path = os.path.dirname(os.path.abspath(__file__))
        tools_path = os.path.dirname(building_path)
        
        # Add to path if not already there
        if tools_path not in sys.path:
            sys.path.insert(0, tools_path)
        
        # Import and use the existing BuildPackage
        try:
            from package import BuildPackage as build_package_func
            
            # BuildPackage uses global functions, so we need to set up the context
            # Save current directory
            current_dir = os.getcwd()
            
            # Change to the directory where we want to build
            if package_path is None:
                work_dir = env.GetCurrentDir()
            elif os.path.isdir(package_path):
                work_dir = package_path
            else:
                work_dir = os.path.dirname(package_path)
                
            os.chdir(work_dir)
            
            try:
                # Call the original BuildPackage
                result = build_package_func(package_path)
            finally:
                # Restore directory
                os.chdir(current_dir)
                
            return result
            
        except ImportError:
            # Fallback if import fails
            context = BuildContext.get_current()
            if context:
                context.logger.error("Failed to import package module")
            return []
        
    @staticmethod
    def Glob(env, pattern: str) -> List[str]:
        """
        Enhanced glob with better error handling.
        
        Args:
            env: SCons Environment
            pattern: File pattern
            
        Returns:
            List of matching files
        """
        try:
            files = Glob(pattern, strings=True)
            return sorted(files)  # Sort for consistent ordering
        except Exception as e:
            context = BuildContext.get_current()
            if context:
                context.logger.warning(f"Glob pattern '{pattern}' failed: {e}")
            return []
            
    @staticmethod
    def GetBuildOptions(env) -> Dict[str, Any]:
        """
        Get build options.
        
        Args:
            env: SCons Environment
            
        Returns:
            Dictionary of build options
        """
        context = BuildContext.get_current()
        if context:
            return context.build_options
        return {}
        
    @staticmethod
    def GetContext(env) -> Optional[BuildContext]:
        """
        Get current build context.
        
        Args:
            env: SCons Environment
            
        Returns:
            BuildContext instance or None
        """
        return BuildContext.get_current()
        
    @staticmethod
    def GetRTTRoot(env) -> str:
        """
        Get RT-Thread root directory.
        
        Args:
            env: SCons Environment
            
        Returns:
            RT-Thread root path
        """
        return env.get('RTT_ROOT', '')
        
    @staticmethod
    def GetBSPRoot(env) -> str:
        """
        Get BSP root directory.
        
        Args:
            env: SCons Environment
            
        Returns:
            BSP root path
        """
        return env.get('BSP_ROOT', '')
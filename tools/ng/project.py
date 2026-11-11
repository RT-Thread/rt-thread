# -*- coding: utf-8 -*-
"""
Project and group management for RT-Thread build system.

This module provides classes for managing project groups and their compilation.
"""

import os
from typing import List, Dict, Any, Optional
from dataclasses import dataclass, field
from SCons.Script import *


@dataclass
class ProjectGroup:
    """
    Represents a project group (component).
    
    This class encapsulates the information from DefineGroup calls.
    """
    name: str
    sources: List[str]
    dependencies: List[str] = field(default_factory=list)
    environment: Any = None  # SCons Environment
    
    # Paths and defines
    include_paths: List[str] = field(default_factory=list)
    defines: Dict[str, str] = field(default_factory=dict)
    
    # Compiler flags
    cflags: str = ""
    cxxflags: str = ""
    asflags: str = ""
    ldflags: str = ""
    
    # Local options (only for this group)
    local_cflags: str = ""
    local_cxxflags: str = ""
    local_include_paths: List[str] = field(default_factory=list)
    local_defines: Dict[str, str] = field(default_factory=dict)
    
    # Libraries
    libs: List[str] = field(default_factory=list)
    lib_paths: List[str] = field(default_factory=list)
    
    # Build objects
    objects: List[Any] = field(default_factory=list)
    
    def build(self, env) -> List:
        """
        Build the group and return objects.
        
        Args:
            env: SCons Environment
            
        Returns:
            List of build objects
        """
        if not self.sources:
            return []
            
        # Clone environment if we have local options
        build_env = env
        if self._has_local_options():
            build_env = env.Clone()
            self._apply_local_options(build_env)
            
        # Apply global options
        self._apply_global_options(build_env)
        
        # Build objects
        self.objects = []
        for src in self.sources:
            if isinstance(src, str):
                # Build single file
                obj = build_env.Object(src)
                self.objects.extend(obj if isinstance(obj, list) else [obj])
            else:
                # Already a Node
                self.objects.append(src)
                
        return self.objects
        
    def _has_local_options(self) -> bool:
        """Check if group has local options."""
        return bool(
            self.local_cflags or
            self.local_cxxflags or
            self.local_include_paths or
            self.local_defines
        )
        
    def _apply_local_options(self, env) -> None:
        """Apply local options to environment."""
        if self.local_cflags:
            env.AppendUnique(CFLAGS=self.local_cflags.split())
            
        if self.local_cxxflags:
            env.AppendUnique(CXXFLAGS=self.local_cxxflags.split())
            
        if self.local_include_paths:
            paths = [os.path.abspath(p) for p in self.local_include_paths]
            env.AppendUnique(CPPPATH=paths)
            
        if self.local_defines:
            env.AppendUnique(CPPDEFINES=self.local_defines)
            
    def _apply_global_options(self, env) -> None:
        """Apply global options to environment."""
        # These options affect dependent groups too
        if self.include_paths:
            paths = [os.path.abspath(p) for p in self.include_paths]
            env.AppendUnique(CPPPATH=paths)
            
        if self.defines:
            env.AppendUnique(CPPDEFINES=self.defines)
            
        if self.cflags and 'CFLAGS' not in env:
            env['CFLAGS'] = self.cflags
            
        if self.cxxflags and 'CXXFLAGS' not in env:
            env['CXXFLAGS'] = self.cxxflags
            
        if self.libs:
            env.AppendUnique(LIBS=self.libs)
            
        if self.lib_paths:
            paths = [os.path.abspath(p) for p in self.lib_paths]
            env.AppendUnique(LIBPATH=paths)
            
    def get_info(self) -> Dict[str, Any]:
        """
        Get group information for project generators.
        
        Returns:
            Dictionary with group information
        """
        return {
            'name': self.name,
            'sources': self.sources,
            'include_paths': self.include_paths + self.local_include_paths,
            'defines': {**self.defines, **self.local_defines},
            'cflags': f"{self.cflags} {self.local_cflags}".strip(),
            'cxxflags': f"{self.cxxflags} {self.local_cxxflags}".strip(),
            'libs': self.libs,
            'lib_paths': self.lib_paths
        }


class ProjectRegistry:
    """
    Registry for all project groups.
    
    This class manages all registered project groups and provides
    methods for querying and merging them.
    """
    
    def __init__(self):
        self.groups: List[ProjectGroup] = []
        self._group_index: Dict[str, ProjectGroup] = {}
        
    def register_group(self, group: ProjectGroup) -> None:
        """
        Register a project group.
        
        Args:
            group: ProjectGroup instance
        """
        self.groups.append(group)
        self._group_index[group.name] = group
        
    def get_group(self, name: str) -> Optional[ProjectGroup]:
        """
        Get group by name.
        
        Args:
            name: Group name
            
        Returns:
            ProjectGroup or None
        """
        return self._group_index.get(name)
        
    def get_all_groups(self) -> List[ProjectGroup]:
        """Get all registered groups."""
        return self.groups.copy()
        
    def get_groups_by_dependency(self, dependency: str) -> List[ProjectGroup]:
        """
        Get groups that depend on a specific macro.
        
        Args:
            dependency: Dependency name
            
        Returns:
            List of matching groups
        """
        return [g for g in self.groups if dependency in g.dependencies]
        
    def merge_groups(self, env) -> List:
        """
        Merge all groups into a single list of objects.
        
        Args:
            env: SCons Environment
            
        Returns:
            List of all build objects
        """
        all_objects = []
        
        for group in self.groups:
            if group.objects:
                all_objects.extend(group.objects)
                
        return all_objects
        
    def get_project_info(self) -> Dict[str, Any]:
        """
        Get complete project information for generators.
        
        Returns:
            Dictionary with project information
        """
        # Collect all unique values
        all_sources = []
        all_includes = set()
        all_defines = {}
        all_libs = []
        all_lib_paths = set()
        
        for group in self.groups:
            info = group.get_info()
            
            # Sources
            all_sources.extend(info['sources'])
            
            # Include paths
            all_includes.update(info['include_paths'])
            
            # Defines
            all_defines.update(info['defines'])
            
            # Libraries
            all_libs.extend(info['libs'])
            all_lib_paths.update(info['lib_paths'])
            
        return {
            'groups': [g.get_info() for g in self.groups],
            'all_sources': all_sources,
            'all_includes': sorted(list(all_includes)),
            'all_defines': all_defines,
            'all_libs': all_libs,
            'all_lib_paths': sorted(list(all_lib_paths))
        }
        
    def clear(self) -> None:
        """Clear all registered groups."""
        self.groups.clear()
        self._group_index.clear()
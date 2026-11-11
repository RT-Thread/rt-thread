# -*- coding: utf-8 -*-
"""
Core module for RT-Thread build system.

This module provides the central BuildContext class that manages the build state
and coordinates between different components.
"""

import os
import logging
from typing import Dict, List, Optional, Any
from dataclasses import dataclass, field

from .config import ConfigManager
from .project import ProjectRegistry
from .toolchain import ToolchainManager
from .generator import GeneratorRegistry
from .utils import PathService


class BuildContext:
    """
    Central build context that manages all build-related state.
    
    This class replaces the global variables in building.py with a proper
    object-oriented design while maintaining compatibility.
    """
    
    # Class variable to store the current context (for backward compatibility)
    _current_context: Optional['BuildContext'] = None
    
    def __init__(self, root_directory: str):
        """
        Initialize build context.
        
        Args:
            root_directory: RT-Thread root directory path
        """
        self.root_directory = os.path.abspath(root_directory)
        self.bsp_directory = os.getcwd()
        
        # Initialize managers
        self.config_manager = ConfigManager()
        self.project_registry = ProjectRegistry()
        self.toolchain_manager = ToolchainManager()
        self.generator_registry = GeneratorRegistry()
        self.path_service = PathService(self.bsp_directory)
        
        # Build environment
        self.environment = None
        self.build_options = {}
        
        # Logging
        self.logger = self._setup_logger()
        
        # Set as current context
        BuildContext._current_context = self
        
    @classmethod
    def get_current(cls) -> Optional['BuildContext']:
        """Get the current build context."""
        return cls._current_context
        
    @classmethod
    def set_current(cls, context: Optional['BuildContext']) -> None:
        """Set the current build context."""
        cls._current_context = context
        
    def _setup_logger(self) -> logging.Logger:
        """Setup logger for build system."""
        logger = logging.getLogger('rtthread.build')
        if not logger.handlers:
            handler = logging.StreamHandler()
            formatter = logging.Formatter('[%(levelname)s] %(message)s')
            handler.setFormatter(formatter)
            logger.addHandler(handler)
            logger.setLevel(logging.INFO)
        return logger
        
    def prepare_environment(self, env) -> None:
        """
        Prepare the build environment.
        
        Args:
            env: SCons Environment object
        """
        self.environment = env
        
        # Set environment variables
        env['RTT_ROOT'] = self.root_directory
        env['BSP_ROOT'] = self.bsp_directory
        
        # Add to Python path
        import sys
        tools_path = os.path.join(self.root_directory, 'tools')
        if tools_path not in sys.path:
            sys.path.insert(0, tools_path)
            
        self.logger.debug(f"Prepared environment with RTT_ROOT={self.root_directory}")
        
    def load_configuration(self, config_file: str = 'rtconfig.h') -> None:
        """
        Load configuration from rtconfig.h.
        
        Args:
            config_file: Path to configuration file
        """
        config_path = os.path.join(self.bsp_directory, config_file)
        if os.path.exists(config_path):
            self.config_manager.load_from_file(config_path)
            self.build_options = self.config_manager.get_all_options()
            self.logger.info(f"Loaded configuration from {config_file}")
        else:
            self.logger.warning(f"Configuration file {config_file} not found")
            
    def get_dependency(self, depend: Any) -> bool:
        """
        Check if dependency is satisfied.
        
        Args:
            depend: Dependency name or list of names
            
        Returns:
            True if dependency is satisfied
        """
        return self.config_manager.get_dependency(depend)
        
    def register_project_group(self, group) -> None:
        """
        Register a project group.
        
        Args:
            group: ProjectGroup instance
        """
        self.project_registry.register_group(group)
        
    def merge_groups(self) -> List:
        """
        Merge all registered project groups.
        
        Returns:
            List of build objects
        """
        return self.project_registry.merge_groups(self.environment)


@dataclass
class BuildOptions:
    """Build options container."""
    verbose: bool = False
    strict: bool = False
    target: Optional[str] = None
    jobs: int = 1
    clean: bool = False
    
    
@dataclass 
class ProjectInfo:
    """Project information for generators."""
    name: str = "rtthread"
    target_name: str = "rtthread.elf"
    
    # File collections
    source_files: List[str] = field(default_factory=list)
    include_paths: List[str] = field(default_factory=list)
    defines: Dict[str, str] = field(default_factory=dict)
    
    # Compiler options
    cflags: str = ""
    cxxflags: str = ""
    asflags: str = ""
    ldflags: str = ""
    
    # Libraries
    libs: List[str] = field(default_factory=list)
    lib_paths: List[str] = field(default_factory=list)
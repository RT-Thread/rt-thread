# -*- coding: utf-8 -*-
"""
RT-Thread Next Generation Build System

This module provides an object-oriented implementation of the RT-Thread build system
while maintaining backward compatibility with the existing building.py interface.
"""

from .core import BuildContext
from .environment import RTEnv
from .config import ConfigManager
from .project import ProjectRegistry, ProjectGroup
from .toolchain import ToolchainManager
from .generator import GeneratorRegistry

__version__ = "1.0.0"
__all__ = [
    'BuildContext',
    'RTEnv', 
    'ConfigManager',
    'ProjectRegistry',
    'ProjectGroup',
    'ToolchainManager',
    'GeneratorRegistry'
]
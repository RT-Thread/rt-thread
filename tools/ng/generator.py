# -*- coding: utf-8 -*-
"""
Project generator framework for RT-Thread build system.

This module provides the base classes for project generators (MDK, IAR, VS Code, etc.).
"""

import os
import shutil
import json
import xml.etree.ElementTree as ET
from abc import ABC, abstractmethod
from typing import Dict, List, Any, Optional
from dataclasses import dataclass

from .utils import PathService


@dataclass
class GeneratorConfig:
    """Configuration for project generators."""
    output_dir: str
    project_name: str = "rtthread"
    target_name: str = "rtthread.elf"
    
    
class ProjectGenerator(ABC):
    """Abstract base class for project generators."""
    
    def __init__(self, config: GeneratorConfig):
        self.config = config
        self.path_service = PathService(os.getcwd())
        
    @abstractmethod
    def get_name(self) -> str:
        """Get generator name."""
        pass
        
    @abstractmethod
    def generate(self, context, project_info: Dict[str, Any]) -> bool:
        """
        Generate project files.
        
        Args:
            context: BuildContext instance
            project_info: Project information from registry
            
        Returns:
            True if successful
        """
        pass
        
    @abstractmethod
    def clean(self) -> bool:
        """
        Clean generated files.
        
        Returns:
            True if successful
        """
        pass
        
    def _ensure_output_dir(self) -> None:
        """Ensure output directory exists."""
        os.makedirs(self.config.output_dir, exist_ok=True)
        
    def _copy_template(self, template_name: str, output_name: str = None) -> str:
        """
        Copy template file to output directory.
        
        Args:
            template_name: Template file name
            output_name: Output file name (defaults to template_name)
            
        Returns:
            Output file path
        """
        if output_name is None:
            output_name = template_name
            
        template_dir = os.path.join(os.path.dirname(__file__), '..', 'targets')
        template_path = os.path.join(template_dir, template_name)
        output_path = os.path.join(self.config.output_dir, output_name)
        
        if os.path.exists(template_path):
            shutil.copy2(template_path, output_path)
            return output_path
        else:
            raise FileNotFoundError(f"Template not found: {template_path}")


class VscodeGenerator(ProjectGenerator):
    """Visual Studio Code project generator."""
    
    def get_name(self) -> str:
        return "vscode"
        
    def generate(self, context, project_info: Dict[str, Any]) -> bool:
        """Generate VS Code project files."""
        self._ensure_output_dir()
        
        # Create .vscode directory
        vscode_dir = os.path.join(self.config.output_dir, '.vscode')
        os.makedirs(vscode_dir, exist_ok=True)
        
        # Generate c_cpp_properties.json
        self._generate_cpp_properties(vscode_dir, context, project_info)
        
        # Generate tasks.json
        self._generate_tasks(vscode_dir, context)
        
        # Generate launch.json
        self._generate_launch(vscode_dir, context)
        
        # Generate settings.json
        self._generate_settings(vscode_dir)
        
        return True
        
    def clean(self) -> bool:
        """Clean VS Code files."""
        vscode_dir = os.path.join(self.config.output_dir, '.vscode')
        if os.path.exists(vscode_dir):
            shutil.rmtree(vscode_dir)
        return True
        
    def _generate_cpp_properties(self, vscode_dir: str, context, project_info: Dict) -> None:
        """Generate c_cpp_properties.json."""
        # Get toolchain info
        toolchain = context.toolchain_manager.get_current()
        compiler_path = ""
        if toolchain and toolchain.info:
            if toolchain.get_name() == "gcc":
                compiler_path = os.path.join(toolchain.info.path, toolchain.info.prefix + "gcc")
                
        config = {
            "configurations": [
                {
                    "name": "RT-Thread",
                    "includePath": [
                        "${workspaceFolder}/**"
                    ] + project_info.get('all_includes', []),
                    "defines": [f"{k}={v}" if v != '1' else k 
                              for k, v in project_info.get('all_defines', {}).items()],
                    "compilerPath": compiler_path,
                    "cStandard": "c99",
                    "cppStandard": "c++11",
                    "intelliSenseMode": "gcc-arm" if "arm" in compiler_path else "gcc-x64"
                }
            ],
            "version": 4
        }
        
        output_path = os.path.join(vscode_dir, 'c_cpp_properties.json')
        with open(output_path, 'w') as f:
            json.dump(config, f, indent=4)
            
    def _generate_tasks(self, vscode_dir: str, context) -> None:
        """Generate tasks.json."""
        tasks = {
            "version": "2.0.0",
            "tasks": [
                {
                    "label": "build",
                    "type": "shell",
                    "command": "scons",
                    "problemMatcher": "$gcc",
                    "group": {
                        "kind": "build",
                        "isDefault": True
                    }
                },
                {
                    "label": "clean",
                    "type": "shell",
                    "command": "scons -c",
                    "problemMatcher": "$gcc"
                },
                {
                    "label": "rebuild",
                    "type": "shell",
                    "command": "scons -c && scons",
                    "problemMatcher": "$gcc"
                }
            ]
        }
        
        output_path = os.path.join(vscode_dir, 'tasks.json')
        with open(output_path, 'w') as f:
            json.dump(tasks, f, indent=4)
            
    def _generate_launch(self, vscode_dir: str, context) -> None:
        """Generate launch.json."""
        launch = {
            "version": "0.2.0",
            "configurations": [
                {
                    "name": "Cortex Debug",
                    "type": "cortex-debug",
                    "request": "launch",
                    "servertype": "openocd",
                    "cwd": "${workspaceRoot}",
                    "executable": "${workspaceRoot}/" + self.config.target_name,
                    "device": "STM32F103C8",
                    "configFiles": [
                        "interface/stlink-v2.cfg",
                        "target/stm32f1x.cfg"
                    ]
                }
            ]
        }
        
        output_path = os.path.join(vscode_dir, 'launch.json')
        with open(output_path, 'w') as f:
            json.dump(launch, f, indent=4)
            
    def _generate_settings(self, vscode_dir: str) -> None:
        """Generate settings.json."""
        settings = {
            "files.associations": {
                "*.h": "c",
                "*.c": "c",
                "*.cpp": "cpp",
                "*.cc": "cpp",
                "*.cxx": "cpp"
            },
            "C_Cpp.errorSquiggles": "Enabled"
        }
        
        output_path = os.path.join(vscode_dir, 'settings.json')
        with open(output_path, 'w') as f:
            json.dump(settings, f, indent=4)


class CMakeGenerator(ProjectGenerator):
    """CMake project generator."""
    
    def get_name(self) -> str:
        return "cmake"
        
    def generate(self, context, project_info: Dict[str, Any]) -> bool:
        """Generate CMakeLists.txt."""
        self._ensure_output_dir()
        
        # Get toolchain info
        toolchain = context.toolchain_manager.get_current()
        
        lines = [
            "cmake_minimum_required(VERSION 3.10)",
            "",
            "# RT-Thread CMake Project",
            f"project({self.config.project_name} C CXX ASM)",
            "",
            "# C Standard",
            "set(CMAKE_C_STANDARD 99)",
            "set(CMAKE_CXX_STANDARD 11)",
            ""
        ]
        
        # Toolchain configuration
        if toolchain and toolchain.get_name() == "gcc":
            lines.extend([
                "# Toolchain",
                f"set(CMAKE_C_COMPILER {toolchain.info.prefix}gcc)",
                f"set(CMAKE_CXX_COMPILER {toolchain.info.prefix}g++)",
                f"set(CMAKE_ASM_COMPILER {toolchain.info.prefix}gcc)",
                ""
            ])
            
        # Include directories
        lines.extend([
            "# Include directories",
            "include_directories("
        ])
        for inc in project_info.get('all_includes', []):
            lines.append(f"    {inc}")
        lines.extend([")", ""])
        
        # Definitions
        lines.extend([
            "# Definitions",
            "add_definitions("
        ])
        for k, v in project_info.get('all_defines', {}).items():
            if v == '1':
                lines.append(f"    -D{k}")
            else:
                lines.append(f"    -D{k}={v}")
        lines.extend([")", ""])
        
        # Source files
        lines.extend([
            "# Source files",
            "set(SOURCES"
        ])
        for src in project_info.get('all_sources', []):
            lines.append(f"    {src}")
        lines.extend([")", ""])
        
        # Executable
        lines.extend([
            "# Executable",
            f"add_executable(${{PROJECT_NAME}} ${{SOURCES}})",
            ""
        ])
        
        # Libraries
        if project_info.get('all_libs'):
            lines.extend([
                "# Libraries",
                f"target_link_libraries(${{PROJECT_NAME}}"
            ])
            for lib in project_info['all_libs']:
                lines.append(f"    {lib}")
            lines.extend([")", ""])
            
        # Write file
        output_path = os.path.join(self.config.output_dir, 'CMakeLists.txt')
        with open(output_path, 'w') as f:
            f.write('\n'.join(lines))
            
        return True
        
    def clean(self) -> bool:
        """Clean CMake files."""
        files_to_remove = ['CMakeLists.txt', 'CMakeCache.txt']
        dirs_to_remove = ['CMakeFiles']
        
        for file in files_to_remove:
            file_path = os.path.join(self.config.output_dir, file)
            if os.path.exists(file_path):
                os.remove(file_path)
                
        for dir in dirs_to_remove:
            dir_path = os.path.join(self.config.output_dir, dir)
            if os.path.exists(dir_path):
                shutil.rmtree(dir_path)
                
        return True


class GeneratorRegistry:
    """Registry for project generators."""
    
    def __init__(self):
        self.generators: Dict[str, type] = {}
        self._register_default_generators()
        
    def _register_default_generators(self) -> None:
        """Register default generators."""
        self.register("vscode", VscodeGenerator)
        self.register("vsc", VscodeGenerator)  # Alias
        self.register("cmake", CMakeGenerator)
        
    def register(self, name: str, generator_class: type) -> None:
        """Register a generator class."""
        self.generators[name] = generator_class
        
    def create_generator(self, name: str, config: GeneratorConfig) -> ProjectGenerator:
        """Create a generator instance."""
        if name not in self.generators:
            raise ValueError(f"Unknown generator: {name}")
            
        return self.generators[name](config)
        
    def list_generators(self) -> List[str]:
        """List available generators."""
        return list(self.generators.keys())
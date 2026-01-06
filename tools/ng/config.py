# -*- coding: utf-8 -*-
"""
Configuration management for RT-Thread build system.

This module handles parsing and managing configuration from rtconfig.h files.
"""

import re
import os
from typing import Dict, List, Any, Optional, Union
from dataclasses import dataclass
from enum import Enum


class ConfigType(Enum):
    """Configuration value types."""
    BOOLEAN = "boolean"
    INTEGER = "integer"
    STRING = "string"
    UNDEFINED = "undefined"


@dataclass
class ConfigOption:
    """Configuration option with metadata."""
    name: str
    value: Any
    type: ConfigType
    line_number: int = 0
    comment: str = ""
    
    def as_bool(self) -> bool:
        """Get value as boolean."""
        if self.type == ConfigType.BOOLEAN:
            return bool(self.value)
        elif self.type == ConfigType.INTEGER:
            return self.value != 0
        elif self.type == ConfigType.STRING:
            return bool(self.value)
        return False
        
    def as_int(self) -> int:
        """Get value as integer."""
        if self.type == ConfigType.INTEGER:
            return self.value
        elif self.type == ConfigType.BOOLEAN:
            return 1 if self.value else 0
        elif self.type == ConfigType.STRING:
            try:
                return int(self.value)
            except ValueError:
                return 0
        return 0
        
    def as_str(self) -> str:
        """Get value as string."""
        if self.type == ConfigType.STRING:
            return self.value
        return str(self.value)


class ConfigParser:
    """Parser for rtconfig.h files."""
    
    # Regular expressions for parsing
    RE_DEFINE = re.compile(r'^\s*#\s*define\s+(\w+)(?:\s+(.*))?', re.MULTILINE)
    RE_UNDEF = re.compile(r'^\s*#\s*undef\s+(\w+)', re.MULTILINE)
    RE_IFDEF = re.compile(r'^\s*#\s*ifdef\s+(\w+)', re.MULTILINE)
    RE_IFNDEF = re.compile(r'^\s*#\s*ifndef\s+(\w+)', re.MULTILINE)
    RE_ENDIF = re.compile(r'^\s*#\s*endif', re.MULTILINE)
    RE_COMMENT = re.compile(r'/\*.*?\*/', re.DOTALL)
    RE_LINE_COMMENT = re.compile(r'//.*$', re.MULTILINE)
    
    def __init__(self):
        self.options: Dict[str, ConfigOption] = {}
        self.conditions: List[str] = []
        
    def parse_file(self, filepath: str) -> Dict[str, ConfigOption]:
        """
        Parse configuration file.
        
        Args:
            filepath: Path to rtconfig.h
            
        Returns:
            Dictionary of configuration options
        """
        if not os.path.exists(filepath):
            raise FileNotFoundError(f"Configuration file not found: {filepath}")
            
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
            
        return self.parse_content(content)
        
    def parse_content(self, content: str) -> Dict[str, ConfigOption]:
        """
        Parse configuration content.
        
        Args:
            content: File content
            
        Returns:
            Dictionary of configuration options
        """
        # Remove comments
        content = self.RE_COMMENT.sub('', content)
        content = self.RE_LINE_COMMENT.sub('', content)
        
        # Parse line by line
        lines = content.split('\n')
        for i, line in enumerate(lines):
            self._parse_line(line, i + 1)
            
        return self.options
        
    def _parse_line(self, line: str, line_number: int) -> None:
        """Parse a single line."""
        # Check for #define
        match = self.RE_DEFINE.match(line)
        if match:
            name = match.group(1)
            value = match.group(2) if match.group(2) else '1'
            
            # Parse value
            parsed_value, value_type = self._parse_value(value.strip())
            
            # Create option
            option = ConfigOption(
                name=name,
                value=parsed_value,
                type=value_type,
                line_number=line_number
            )
            
            self.options[name] = option
            return
            
        # Check for #undef
        match = self.RE_UNDEF.match(line)
        if match:
            name = match.group(1)
            if name in self.options:
                del self.options[name]
            return
            
    def _parse_value(self, value: str) -> tuple:
        """
        Parse configuration value.
        
        Returns:
            Tuple of (parsed_value, ConfigType)
        """
        if not value or value == '1':
            return (True, ConfigType.BOOLEAN)
            
        # Try integer
        try:
            return (int(value, 0), ConfigType.INTEGER)  # Support hex/octal
        except ValueError:
            pass
            
        # Try string (remove quotes)
        if value.startswith('"') and value.endswith('"'):
            return (value[1:-1], ConfigType.STRING)
            
        # Default to string
        return (value, ConfigType.STRING)


class ConfigManager:
    """
    Configuration manager for build system.
    
    This class manages configuration options and provides dependency checking.
    """
    
    def __init__(self):
        self.parser = ConfigParser()
        self.options: Dict[str, ConfigOption] = {}
        self.cache: Dict[str, bool] = {}
        
    def load_from_file(self, filepath: str) -> None:
        """
        Load configuration from file.
        
        Args:
            filepath: Path to rtconfig.h
        """
        self.options = self.parser.parse_file(filepath)
        self.cache.clear()  # Clear dependency cache
        
    def get_option(self, name: str) -> Optional[ConfigOption]:
        """
        Get configuration option.
        
        Args:
            name: Option name
            
        Returns:
            ConfigOption or None
        """
        return self.options.get(name)
        
    def get_value(self, name: str, default: Any = None) -> Any:
        """
        Get configuration value.
        
        Args:
            name: Option name
            default: Default value if not found
            
        Returns:
            Configuration value
        """
        option = self.options.get(name)
        if option:
            return option.value
        return default
        
    def get_dependency(self, depend: Union[str, List[str]]) -> bool:
        """
        Check if dependency is satisfied.
        
        Args:
            depend: Single dependency or list of dependencies
            
        Returns:
            True if all dependencies are satisfied
        """
        # Handle empty dependency
        if not depend:
            return True
            
        # Convert to list
        if isinstance(depend, str):
            depend = [depend]
            
        # Check cache
        cache_key = ','.join(sorted(depend))
        if cache_key in self.cache:
            return self.cache[cache_key]
            
        # Check all dependencies (AND logic)
        result = all(self._check_single_dependency(d) for d in depend)
        
        # Cache result
        self.cache[cache_key] = result
        return result
        
    def _check_single_dependency(self, name: str) -> bool:
        """Check a single dependency."""
        option = self.options.get(name)
        if not option:
            return False
            
        # For RT-Thread, any defined macro is considered True
        # except if explicitly set to 0
        if option.type == ConfigType.INTEGER:
            return option.value != 0
        elif option.type == ConfigType.BOOLEAN:
            return option.value
        elif option.type == ConfigType.STRING:
            return bool(option.value)
            
        return True
        
    def get_all_options(self) -> Dict[str, Any]:
        """
        Get all configuration options as a simple dictionary.
        
        Returns:
            Dictionary of option names to values
        """
        return {name: opt.value for name, opt in self.options.items()}
        
    def validate(self) -> List[str]:
        """
        Validate configuration.
        
        Returns:
            List of validation errors
        """
        errors = []
        
        # Check for common issues
        if 'RT_NAME_MAX' in self.options:
            name_max = self.options['RT_NAME_MAX'].as_int()
            if name_max < 4:
                errors.append("RT_NAME_MAX should be at least 4")
                
        if 'RT_THREAD_PRIORITY_MAX' in self.options:
            prio_max = self.options['RT_THREAD_PRIORITY_MAX'].as_int()
            if prio_max not in [8, 32, 256]:
                errors.append("RT_THREAD_PRIORITY_MAX should be 8, 32, or 256")
                
        return errors
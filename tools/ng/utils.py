# -*- coding: utf-8 -*-
"""
Utility functions for RT-Thread build system.

This module provides common utility functions used throughout the build system.
"""

import os
import sys
import platform
from typing import List, Tuple, Optional


class PathService:
    """Service for path manipulation and normalization."""
    
    def __init__(self, base_path: str = None):
        self.base_path = base_path or os.getcwd()
        
    def normalize_path(self, path: str) -> str:
        """
        Normalize path for cross-platform compatibility.
        
        Args:
            path: Path to normalize
            
        Returns:
            Normalized path
        """
        # Convert to absolute path if relative
        if not os.path.isabs(path):
            path = os.path.abspath(os.path.join(self.base_path, path))
            
        # Normalize separators
        path = os.path.normpath(path)
        
        # Convert to forward slashes for consistency
        if platform.system() == 'Windows':
            path = path.replace('\\', '/')
            
        return path
        
    def make_relative(self, path: str, base: str = None) -> str:
        """
        Make path relative to base.
        
        Args:
            path: Path to make relative
            base: Base path (defaults to self.base_path)
            
        Returns:
            Relative path
        """
        if base is None:
            base = self.base_path
            
        path = self.normalize_path(path)
        base = self.normalize_path(base)
        
        try:
            rel_path = os.path.relpath(path, base)
            # Convert to forward slashes
            if platform.system() == 'Windows':
                rel_path = rel_path.replace('\\', '/')
            return rel_path
        except ValueError:
            # Different drives on Windows
            return path
            
    def split_path(self, path: str) -> List[str]:
        """
        Split path into components.
        
        Args:
            path: Path to split
            
        Returns:
            List of path components
        """
        path = self.normalize_path(path)
        parts = []
        
        while True:
            head, tail = os.path.split(path)
            if tail:
                parts.insert(0, tail)
            if head == path:  # Reached root
                if head:
                    parts.insert(0, head)
                break
            path = head
            
        return parts
        
    def common_prefix(self, paths: List[str]) -> str:
        """
        Find common prefix of multiple paths.
        
        Args:
            paths: List of paths
            
        Returns:
            Common prefix path
        """
        if not paths:
            return ""
            
        # Normalize all paths
        normalized = [self.normalize_path(p) for p in paths]
        
        # Find common prefix
        prefix = os.path.commonpath(normalized)
        
        return self.normalize_path(prefix)


class PlatformInfo:
    """Platform and system information."""
    
    @staticmethod
    def get_platform() -> str:
        """Get platform name (Windows, Linux, Darwin)."""
        return platform.system()
        
    @staticmethod
    def get_architecture() -> str:
        """Get system architecture."""
        return platform.machine()
        
    @staticmethod
    def is_windows() -> bool:
        """Check if running on Windows."""
        return platform.system() == 'Windows'
        
    @staticmethod
    def is_linux() -> bool:
        """Check if running on Linux."""
        return platform.system() == 'Linux'
        
    @staticmethod
    def is_macos() -> bool:
        """Check if running on macOS."""
        return platform.system() == 'Darwin'
        
    @staticmethod
    def get_python_version() -> Tuple[int, int, int]:
        """Get Python version tuple."""
        return sys.version_info[:3]
        
    @staticmethod
    def check_python_version(min_version: Tuple[int, int]) -> bool:
        """
        Check if Python version meets minimum requirement.
        
        Args:
            min_version: Minimum version tuple (major, minor)
            
        Returns:
            True if version is sufficient
        """
        current = sys.version_info[:2]
        return current >= min_version


class FileUtils:
    """File operation utilities."""
    
    @staticmethod
    def read_file(filepath: str, encoding: str = 'utf-8') -> str:
        """
        Read file content.
        
        Args:
            filepath: File path
            encoding: File encoding
            
        Returns:
            File content
        """
        with open(filepath, 'r', encoding=encoding) as f:
            return f.read()
            
    @staticmethod
    def write_file(filepath: str, content: str, encoding: str = 'utf-8') -> None:
        """
        Write content to file.
        
        Args:
            filepath: File path
            content: Content to write
            encoding: File encoding
        """
        # Ensure directory exists
        directory = os.path.dirname(filepath)
        if directory:
            os.makedirs(directory, exist_ok=True)
            
        with open(filepath, 'w', encoding=encoding) as f:
            f.write(content)
            
    @staticmethod
    def copy_file(src: str, dst: str) -> None:
        """
        Copy file from src to dst.
        
        Args:
            src: Source file path
            dst: Destination file path
        """
        import shutil
        
        # Ensure destination directory exists
        dst_dir = os.path.dirname(dst)
        if dst_dir:
            os.makedirs(dst_dir, exist_ok=True)
            
        shutil.copy2(src, dst)
        
    @staticmethod
    def find_files(directory: str, pattern: str, recursive: bool = True) -> List[str]:
        """
        Find files matching pattern.
        
        Args:
            directory: Directory to search
            pattern: File pattern (supports wildcards)
            recursive: Search recursively
            
        Returns:
            List of matching file paths
        """
        import fnmatch
        
        matches = []
        
        if recursive:
            for root, dirnames, filenames in os.walk(directory):
                for filename in filenames:
                    if fnmatch.fnmatch(filename, pattern):
                        matches.append(os.path.join(root, filename))
        else:
            try:
                filenames = os.listdir(directory)
                for filename in filenames:
                    if fnmatch.fnmatch(filename, pattern):
                        filepath = os.path.join(directory, filename)
                        if os.path.isfile(filepath):
                            matches.append(filepath)
            except OSError:
                pass
                
        return sorted(matches)


class VersionUtils:
    """Version comparison utilities."""
    
    @staticmethod
    def parse_version(version_str: str) -> Tuple[int, ...]:
        """
        Parse version string to tuple.
        
        Args:
            version_str: Version string (e.g., "1.2.3")
            
        Returns:
            Version tuple
        """
        try:
            parts = version_str.split('.')
            return tuple(int(p) for p in parts if p.isdigit())
        except (ValueError, AttributeError):
            return (0,)
            
    @staticmethod
    def compare_versions(v1: str, v2: str) -> int:
        """
        Compare two version strings.
        
        Args:
            v1: First version
            v2: Second version
            
        Returns:
            -1 if v1 < v2, 0 if equal, 1 if v1 > v2
        """
        t1 = VersionUtils.parse_version(v1)
        t2 = VersionUtils.parse_version(v2)
        
        # Pad shorter version with zeros
        if len(t1) < len(t2):
            t1 = t1 + (0,) * (len(t2) - len(t1))
        elif len(t2) < len(t1):
            t2 = t2 + (0,) * (len(t1) - len(t2))
            
        if t1 < t2:
            return -1
        elif t1 > t2:
            return 1
        else:
            return 0
            
    @staticmethod
    def version_satisfies(version: str, requirement: str) -> bool:
        """
        Check if version satisfies requirement.
        
        Args:
            version: Version string
            requirement: Requirement string (e.g., ">=1.2.0")
            
        Returns:
            True if satisfied
        """
        import re
        
        # Parse requirement
        match = re.match(r'([<>=]+)\s*(.+)', requirement)
        if not match:
            # Exact match required
            return version == requirement
            
        op, req_version = match.groups()
        cmp = VersionUtils.compare_versions(version, req_version)
        
        if op == '>=':
            return cmp >= 0
        elif op == '<=':
            return cmp <= 0
        elif op == '>':
            return cmp > 0
        elif op == '<':
            return cmp < 0
        elif op == '==':
            return cmp == 0
        elif op == '!=':
            return cmp != 0
        else:
            return False
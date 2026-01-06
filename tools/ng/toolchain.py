# -*- coding: utf-8 -*-
"""
Toolchain management for RT-Thread build system.

This module provides abstraction for different toolchains (GCC, Keil, IAR, etc.).
"""

import os
import shutil
import subprocess
from abc import ABC, abstractmethod
from typing import Dict, List, Optional, Tuple
from dataclasses import dataclass


@dataclass
class ToolchainInfo:
    """Toolchain information."""
    name: str
    version: str
    path: str
    prefix: str = ""
    suffix: str = ""
    
    
class Toolchain(ABC):
    """Abstract base class for toolchains."""
    
    def __init__(self):
        self.info = None
        
    @abstractmethod
    def get_name(self) -> str:
        """Get toolchain name."""
        pass
        
    @abstractmethod
    def detect(self) -> bool:
        """Detect if toolchain is available."""
        pass
        
    @abstractmethod
    def configure_environment(self, env) -> None:
        """Configure SCons environment for this toolchain."""
        pass
        
    @abstractmethod
    def get_compile_flags(self, cpu: str, fpu: str = None, float_abi: str = None) -> Dict[str, str]:
        """Get compilation flags for target CPU."""
        pass
        
    def get_version(self) -> Optional[str]:
        """Get toolchain version."""
        return self.info.version if self.info else None
        
    def _run_command(self, cmd: List[str]) -> Tuple[int, str, str]:
        """Run command and return (returncode, stdout, stderr)."""
        try:
            result = subprocess.run(cmd, capture_output=True, text=True)
            return result.returncode, result.stdout, result.stderr
        except Exception as e:
            return -1, "", str(e)


class GccToolchain(Toolchain):
    """GCC toolchain implementation."""
    
    def __init__(self, prefix: str = ""):
        super().__init__()
        self.prefix = prefix or "arm-none-eabi-"
        
    def get_name(self) -> str:
        return "gcc"
        
    def detect(self) -> bool:
        """Detect GCC toolchain."""
        gcc_path = shutil.which(self.prefix + "gcc")
        if not gcc_path:
            return False
            
        # Get version
        ret, stdout, _ = self._run_command([gcc_path, "--version"])
        if ret == 0:
            lines = stdout.split('\n')
            if lines:
                version = lines[0].split()[-1]
                self.info = ToolchainInfo(
                    name="gcc",
                    version=version,
                    path=os.path.dirname(gcc_path),
                    prefix=self.prefix
                )
                return True
                
        return False
        
    def configure_environment(self, env) -> None:
        """Configure environment for GCC."""
        env['CC'] = self.prefix + 'gcc'
        env['CXX'] = self.prefix + 'g++'
        env['AS'] = self.prefix + 'gcc'
        env['AR'] = self.prefix + 'ar'
        env['LINK'] = self.prefix + 'gcc'
        env['SIZE'] = self.prefix + 'size'
        env['OBJDUMP'] = self.prefix + 'objdump'
        env['OBJCPY'] = self.prefix + 'objcopy'
        
        # Set default flags
        env['ARFLAGS'] = '-rc'
        env['ASFLAGS'] = '-x assembler-with-cpp'
        
        # Path
        if self.info and self.info.path:
            env.PrependENVPath('PATH', self.info.path)
            
    def get_compile_flags(self, cpu: str, fpu: str = None, float_abi: str = None) -> Dict[str, str]:
        """Get GCC compilation flags."""
        flags = {
            'CFLAGS': [],
            'CXXFLAGS': [],
            'ASFLAGS': [],
            'LDFLAGS': []
        }
        
        # CPU flags
        cpu_flags = {
            'cortex-m0': '-mcpu=cortex-m0 -mthumb',
            'cortex-m0+': '-mcpu=cortex-m0plus -mthumb',
            'cortex-m3': '-mcpu=cortex-m3 -mthumb',
            'cortex-m4': '-mcpu=cortex-m4 -mthumb',
            'cortex-m7': '-mcpu=cortex-m7 -mthumb',
            'cortex-m23': '-mcpu=cortex-m23 -mthumb',
            'cortex-m33': '-mcpu=cortex-m33 -mthumb',
            'cortex-a7': '-mcpu=cortex-a7',
            'cortex-a9': '-mcpu=cortex-a9'
        }
        
        if cpu in cpu_flags:
            base_flags = cpu_flags[cpu]
            for key in ['CFLAGS', 'CXXFLAGS', 'ASFLAGS']:
                flags[key].append(base_flags)
                
        # FPU flags
        if fpu:
            fpu_flag = f'-mfpu={fpu}'
            for key in ['CFLAGS', 'CXXFLAGS']:
                flags[key].append(fpu_flag)
                
        # Float ABI
        if float_abi:
            abi_flag = f'-mfloat-abi={float_abi}'
            for key in ['CFLAGS', 'CXXFLAGS']:
                flags[key].append(abi_flag)
                
        # Common flags
        common_flags = ['-ffunction-sections', '-fdata-sections']
        flags['CFLAGS'].extend(common_flags)
        flags['CXXFLAGS'].extend(common_flags)
        
        # Linker flags
        flags['LDFLAGS'].extend(['-Wl,--gc-sections'])
        
        # Convert lists to strings
        return {k: ' '.join(v) for k, v in flags.items()}


class ArmccToolchain(Toolchain):
    """ARM Compiler (Keil) toolchain implementation."""
    
    def get_name(self) -> str:
        return "armcc"
        
    def detect(self) -> bool:
        """Detect ARM Compiler toolchain."""
        armcc_path = shutil.which("armcc")
        if not armcc_path:
            # Try common Keil installation paths
            keil_paths = [
                r"C:\Keil_v5\ARM\ARMCC\bin",
                r"C:\Keil\ARM\ARMCC\bin",
                "/opt/arm/bin"
            ]
            for path in keil_paths:
                test_path = os.path.join(path, "armcc")
                if os.path.exists(test_path):
                    armcc_path = test_path
                    break
                    
        if not armcc_path:
            return False
            
        # Get version
        ret, stdout, _ = self._run_command([armcc_path, "--version"])
        if ret == 0:
            lines = stdout.split('\n')
            for line in lines:
                if "ARM Compiler" in line:
                    version = line.split()[-1]
                    self.info = ToolchainInfo(
                        name="armcc",
                        version=version,
                        path=os.path.dirname(armcc_path)
                    )
                    return True
                    
        return False
        
    def configure_environment(self, env) -> None:
        """Configure environment for ARM Compiler."""
        env['CC'] = 'armcc'
        env['CXX'] = 'armcc'
        env['AS'] = 'armasm'
        env['AR'] = 'armar'
        env['LINK'] = 'armlink'
        
        # ARM Compiler specific settings
        env['ARCOM'] = '$AR --create $TARGET $SOURCES'
        env['LIBPREFIX'] = ''
        env['LIBSUFFIX'] = '.lib'
        env['LIBLINKPREFIX'] = ''
        env['LIBLINKSUFFIX'] = '.lib'
        env['LIBDIRPREFIX'] = '--userlibpath '
        
        # Path
        if self.info and self.info.path:
            env.PrependENVPath('PATH', self.info.path)
            
    def get_compile_flags(self, cpu: str, fpu: str = None, float_abi: str = None) -> Dict[str, str]:
        """Get ARM Compiler flags."""
        flags = {
            'CFLAGS': [],
            'CXXFLAGS': [],
            'ASFLAGS': [],
            'LDFLAGS': []
        }
        
        # CPU selection
        cpu_map = {
            'cortex-m0': '--cpu Cortex-M0',
            'cortex-m0+': '--cpu Cortex-M0+',
            'cortex-m3': '--cpu Cortex-M3',
            'cortex-m4': '--cpu Cortex-M4',
            'cortex-m7': '--cpu Cortex-M7'
        }
        
        if cpu in cpu_map:
            cpu_flag = cpu_map[cpu]
            for key in flags:
                flags[key].append(cpu_flag)
                
        # Common flags
        flags['CFLAGS'].extend(['--c99', '--gnu'])
        flags['CXXFLAGS'].extend(['--cpp', '--gnu'])
        
        return {k: ' '.join(v) for k, v in flags.items()}


class IarToolchain(Toolchain):
    """IAR toolchain implementation."""
    
    def get_name(self) -> str:
        return "iar"
        
    def detect(self) -> bool:
        """Detect IAR toolchain."""
        iccarm_path = shutil.which("iccarm")
        if not iccarm_path:
            # Try common IAR installation paths
            iar_paths = [
                r"C:\Program Files (x86)\IAR Systems\Embedded Workbench 8.0\arm\bin",
                r"C:\Program Files\IAR Systems\Embedded Workbench 8.0\arm\bin",
                "/opt/iar/bin"
            ]
            for path in iar_paths:
                test_path = os.path.join(path, "iccarm.exe" if os.name == 'nt' else "iccarm")
                if os.path.exists(test_path):
                    iccarm_path = test_path
                    break
                    
        if not iccarm_path:
            return False
            
        self.info = ToolchainInfo(
            name="iar",
            version="8.x",  # IAR version detection is complex
            path=os.path.dirname(iccarm_path)
        )
        return True
        
    def configure_environment(self, env) -> None:
        """Configure environment for IAR."""
        env['CC'] = 'iccarm'
        env['CXX'] = 'iccarm'
        env['AS'] = 'iasmarm'
        env['AR'] = 'iarchive'
        env['LINK'] = 'ilinkarm'
        
        # IAR specific settings
        env['LIBPREFIX'] = ''
        env['LIBSUFFIX'] = '.a'
        env['LIBLINKPREFIX'] = ''
        env['LIBLINKSUFFIX'] = '.a'
        
        # Path
        if self.info and self.info.path:
            env.PrependENVPath('PATH', self.info.path)
            
    def get_compile_flags(self, cpu: str, fpu: str = None, float_abi: str = None) -> Dict[str, str]:
        """Get IAR flags."""
        flags = {
            'CFLAGS': [],
            'CXXFLAGS': [],
            'ASFLAGS': [],
            'LDFLAGS': []
        }
        
        # CPU selection
        cpu_map = {
            'cortex-m0': '--cpu=Cortex-M0',
            'cortex-m0+': '--cpu=Cortex-M0+',
            'cortex-m3': '--cpu=Cortex-M3',
            'cortex-m4': '--cpu=Cortex-M4',
            'cortex-m7': '--cpu=Cortex-M7'
        }
        
        if cpu in cpu_map:
            cpu_flag = cpu_map[cpu]
            flags['CFLAGS'].append(cpu_flag)
            flags['CXXFLAGS'].append(cpu_flag)
            
        # Common flags
        flags['CFLAGS'].extend(['-e', '--dlib_config', 'DLib_Config_Normal.h'])
        
        return {k: ' '.join(v) for k, v in flags.items()}


class ToolchainManager:
    """Manager for toolchain selection and configuration."""
    
    def __init__(self):
        self.toolchains: Dict[str, Toolchain] = {}
        self.current_toolchain: Optional[Toolchain] = None
        self._register_default_toolchains()
        
    def _register_default_toolchains(self) -> None:
        """Register default toolchains."""
        # Try to detect available toolchains
        toolchain_classes = [
            (GccToolchain, ['arm-none-eabi-', 'riscv32-unknown-elf-', 'riscv64-unknown-elf-']),
            (ArmccToolchain, ['']),
            (IarToolchain, [''])
        ]
        
        for toolchain_class, prefixes in toolchain_classes:
            for prefix in prefixes:
                if toolchain_class == GccToolchain:
                    tc = toolchain_class(prefix)
                else:
                    tc = toolchain_class()
                    
                if tc.detect():
                    name = f"{tc.get_name()}-{prefix}" if prefix else tc.get_name()
                    self.register_toolchain(name, tc)
                    
    def register_toolchain(self, name: str, toolchain: Toolchain) -> None:
        """Register a toolchain."""
        self.toolchains[name] = toolchain
        
    def select_toolchain(self, name: str) -> Toolchain:
        """Select a toolchain by name."""
        if name not in self.toolchains:
            # Try to create it
            if name == 'gcc':
                tc = GccToolchain()
            elif name == 'armcc' or name == 'keil':
                tc = ArmccToolchain()
            elif name == 'iar':
                tc = IarToolchain()
            else:
                raise ValueError(f"Unknown toolchain: {name}")
                
            if tc.detect():
                self.register_toolchain(name, tc)
            else:
                raise RuntimeError(f"Toolchain '{name}' not found")
                
        self.current_toolchain = self.toolchains[name]
        return self.current_toolchain
        
    def get_current(self) -> Optional[Toolchain]:
        """Get current toolchain."""
        return self.current_toolchain
        
    def list_toolchains(self) -> List[str]:
        """List available toolchains."""
        return list(self.toolchains.keys())
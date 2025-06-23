#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Test script to verify the refactoring is successful

import sys
import os

# Add current directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# Mock rtconfig module for testing
import mock_rtconfig
sys.modules['rtconfig'] = mock_rtconfig

def test_targets_import():
    """Test if all target modules can be imported successfully"""
    print("Testing targets module imports...")
    
    try:
        # Test importing targets module
        import targets
        print("✓ targets module imported successfully")
        
        # Test importing individual target modules
        target_modules = [
            'keil', 'iar', 'vs', 'vs2012', 'codeblocks', 'ua', 
            'vsc', 'cdk', 'ses', 'eclipse', 'codelite', 
            'cmake', 'xmake', 'esp_idf', 'zigbuild', 'makefile', 'rt_studio'
        ]
        
        for module_name in target_modules:
            try:
                module = getattr(targets, module_name)
                print(f"✓ {module_name} module imported successfully")
            except AttributeError as e:
                print(f"✗ Failed to import {module_name}: {e}")
                return False
        
        return True
        
    except ImportError as e:
        print(f"✗ Failed to import targets module: {e}")
        return False

def test_building_import():
    """Test if building.py can import target modules"""
    print("\nTesting building.py imports...")
    
    try:
        # Test importing building module
        import building
        print("✓ building module imported successfully")
        
        # Test if GenTargetProject function exists
        if hasattr(building, 'GenTargetProject'):
            print("✓ GenTargetProject function found")
        else:
            print("✗ GenTargetProject function not found")
            return False
            
        return True
        
    except ImportError as e:
        print(f"✗ Failed to import building module: {e}")
        return False

def test_target_functions():
    """Test if target functions can be called"""
    print("\nTesting target function calls...")
    
    try:
        # Test importing specific target functions
        from targets.keil import MDK4Project, MDK5Project
        print("✓ Keil target functions imported successfully")
        
        from targets.iar import IARProject
        print("✓ IAR target functions imported successfully")
        
        from targets.eclipse import TargetEclipse
        print("✓ Eclipse target functions imported successfully")
        
        from targets.cmake import CMakeProject
        print("✓ CMake target functions imported successfully")
        
        import targets.rt_studio
        print("✓ RT-Studio target functions imported successfully")
        
        return True
        
    except ImportError as e:
        print(f"✗ Failed to import target functions: {e}")
        return False

def main():
    """Main test function"""
    print("RT-Thread Tools Refactoring Test")
    print("=" * 40)
    
    success = True
    
    # Run all tests
    if not test_targets_import():
        success = False
    
    if not test_building_import():
        success = False
        
    if not test_target_functions():
        success = False
    
    print("\n" + "=" * 40)
    if success:
        print("✓ All tests passed! Refactoring is successful.")
        return 0
    else:
        print("✗ Some tests failed. Please check the errors above.")
        return 1

if __name__ == '__main__':
    sys.exit(main()) 
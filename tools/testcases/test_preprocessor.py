#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# File      : test_preprocessor_patch.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2025, RT-Thread Development Team
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Change Logs:
# Date           Author       Notes
# 2025-01-05     Assistant    Test file for SCons PreProcessor patch

import sys
import os

# Add current directory to path for imports
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

def test_preprocessor_patch():
    """Test the SCons PreProcessor patch functionality"""
    try:
        from scons_preprocessor_patch import SConsPreProcessorPatch, create_preprocessor_instance
        
        print("Testing SCons PreProcessor patch...")
        
        # Test creating patch instance
        patch = SConsPreProcessorPatch()
        print("✓ SConsPreProcessorPatch instance created successfully")
        
        # Test getting patched preprocessor
        patched_class = patch.get_patched_preprocessor()
        print("✓ Patched PreProcessor class retrieved successfully")
        
        # Test creating preprocessor instance
        preprocessor = create_preprocessor_instance()
        print("✓ PreProcessor instance created successfully")
        
        # Test basic functionality
        test_content = """
        #define TEST_MACRO 1
        #ifdef TEST_MACRO
        #define ENABLED_FEATURE 1
        #else
        #define DISABLED_FEATURE 1
        #endif
        """
        
        preprocessor.process_contents(test_content)
        namespace = preprocessor.cpp_namespace
        
        print("✓ PreProcessor processed test content successfully")
        print(f"  - TEST_MACRO: {namespace.get('TEST_MACRO', 'Not found')}")
        print(f"  - ENABLED_FEATURE: {namespace.get('ENABLED_FEATURE', 'Not found')}")
        print(f"  - DISABLED_FEATURE: {namespace.get('DISABLED_FEATURE', 'Not found')}")
        
        print("\n✓ All tests passed! SCons PreProcessor patch is working correctly.")
        return True
        
    except ImportError as e:
        print(f"✗ Import error: {e}")
        print("Make sure SCons is available in the environment")
        return False
    except Exception as e:
        print(f"✗ Test failed: {e}")
        return False

def test_building_integration():
    """Test integration with building.py"""
    try:
        # Test that the function is available from the patch module
        from scons_preprocessor_patch import create_preprocessor_instance
        
        print("\nTesting scons_preprocessor_patch integration...")
        
        # Test that the function is available
        preprocessor = create_preprocessor_instance()
        print("✓ create_preprocessor_instance function works from scons_preprocessor_patch")
        
        # Test basic processing
        test_content = "#define BUILD_TEST 1"
        preprocessor.process_contents(test_content)
        namespace = preprocessor.cpp_namespace
        
        print(f"✓ Integration test passed: BUILD_TEST = {namespace.get('BUILD_TEST', 'Not found')}")
        return True
        
    except Exception as e:
        print(f"✗ Integration test failed: {e}")
        return False

if __name__ == "__main__":
    print("SCons PreProcessor Patch Test Suite")
    print("=" * 40)
    
    success1 = test_preprocessor_patch()
    success2 = test_building_integration()
    
    if success1 and success2:
        print("\n🎉 All tests passed! The refactoring was successful.")
        sys.exit(0)
    else:
        print("\n❌ Some tests failed. Please check the implementation.")
        sys.exit(1) 
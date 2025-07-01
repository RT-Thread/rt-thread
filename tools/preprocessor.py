# -*- coding: utf-8 -*-
#
# File      : preprocessor.py
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
# 2025-01-05     Assistant    Extract SCons PreProcessor patch to independent class

from SCons.Script import *

class SConsPreProcessorPatch:
    """
    SCons PreProcessor patch class
    
    This class provides methods to patch the SCons PreProcessor
    to handle conditional compilation directives properly.
    """
    
    def __init__(self):
        """Initialize the PreProcessor patch"""
        self._patched_preprocessor = None
        self._apply_patch()
    
    def _apply_patch(self):
        """
        Apply the patch to SCons PreProcessor
        
        This method patches the SCons.cpp.PreProcessor class with
        custom methods for handling includes during conditional compilation.
        """
        from SCons import cpp
        
        # Store reference to original PreProcessor
        self._patched_preprocessor = cpp.PreProcessor
        
        # Create bound methods for the patch
        def start_handling_includes(preprocessor_self, t=None):
            d = preprocessor_self.dispatch_table
            p = preprocessor_self.stack[-1] if preprocessor_self.stack else preprocessor_self.default_table
            for k in ('import', 'include', 'include_next', 'define'):
                d[k] = p[k]
        
        def stop_handling_includes(preprocessor_self, t=None):
            d = preprocessor_self.dispatch_table
            d['import'] = preprocessor_self.do_nothing
            d['include'] = preprocessor_self.do_nothing
            d['include_next'] = preprocessor_self.do_nothing
            d['define'] = preprocessor_self.do_nothing
        
        # Apply the patch methods
        self._patched_preprocessor.start_handling_includes = start_handling_includes
        self._patched_preprocessor.stop_handling_includes = stop_handling_includes
    
    def get_patched_preprocessor(self):
        return self._patched_preprocessor
    
    def create_preprocessor_instance(self):
        return self._patched_preprocessor()

# Global instance for easy access
_preprocessor_patch = None

def get_patched_preprocessor():
    global _preprocessor_patch
    if _preprocessor_patch is None:
        _preprocessor_patch = SConsPreProcessorPatch()
    return _preprocessor_patch.get_patched_preprocessor()

def create_preprocessor_instance():
    global _preprocessor_patch
    if _preprocessor_patch is None:
        _preprocessor_patch = SConsPreProcessorPatch()
    return _preprocessor_patch.create_preprocessor_instance() 
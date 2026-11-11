# -*- coding: utf-8 -*-
"""
Example of minimal changes needed in building.py to integrate the new OOP system.

This file shows the exact changes that would be made to the original building.py.
"""

# =============================================================================
# CHANGES TO ADD AT THE BEGINNING OF building.py
# =============================================================================

"""
# Add after the imports section in building.py (around line 45)

# Try to import new OOP system
try:
    from ng.adapter import (
        init_build_context,
        inject_environment_methods,
        load_rtconfig as ng_load_rtconfig,
        MergeGroups as ng_MergeGroups
    )
    NG_AVAILABLE = True
except ImportError:
    NG_AVAILABLE = False
"""

# =============================================================================
# CHANGES IN PrepareBuilding FUNCTION
# =============================================================================

"""
# Add these lines in PrepareBuilding function after setting up Env (around line 70)

    # Initialize new OOP system if available
    if NG_AVAILABLE:
        # Initialize build context
        ng_context = init_build_context(Rtt_Root)
        
        # Inject methods into environment
        inject_environment_methods(Env)
        
        # Store context reference
        Env['__NG_Context'] = ng_context
"""

# =============================================================================
# CHANGES AFTER PARSING rtconfig.h
# =============================================================================

"""
# Add after parsing rtconfig.h (around line 430)

    # Load configuration into new system
    if NG_AVAILABLE and 'rtconfig.h' in os.listdir(Bsp_Root):
        ng_load_rtconfig('rtconfig.h')
"""

# =============================================================================
# ENHANCED DefineGroup FUNCTION
# =============================================================================

"""
# Replace the original DefineGroup function (around line 565) with:

def DefineGroup(name, src, depend, **parameters):
    global Env
    if Env is None:
        return []
    
    # Try to use new implementation if available
    if NG_AVAILABLE and hasattr(Env, 'DefineGroup'):
        return Env.DefineGroup(name, src, depend, **parameters)
    
    # Original implementation continues below...
    # [Keep all the original DefineGroup code here]
"""

# =============================================================================
# ENHANCED GetDepend FUNCTION  
# =============================================================================

"""
# Replace the original GetDepend function (around line 655) with:

def GetDepend(depend):
    global Env
    
    # Try to use new implementation if available
    if NG_AVAILABLE and Env and hasattr(Env, 'GetDepend'):
        return Env.GetDepend(depend)
    
    # Original implementation continues below...
    # [Keep all the original GetDepend code here]
"""

# =============================================================================
# ENHANCED MergeGroup FUNCTION
# =============================================================================

"""
# Replace the original MergeGroup function (around line 700) with:

def MergeGroup(src_group, group):
    # Try to use new implementation if available
    if NG_AVAILABLE and Env and hasattr(Env, '__NG_Context'):
        context = Env['__NG_Context']
        if context:
            # Register groups with new system
            from ng.project import ProjectGroup
            for g in group:
                if 'name' in g:
                    pg = ProjectGroup(
                        name=g['name'],
                        sources=g.get('src', []),
                        dependencies=[],
                        environment=Env
                    )
                    context.register_project_group(pg)
    
    # Original implementation continues below...
    # [Keep all the original MergeGroup code here]
"""

# =============================================================================
# EXAMPLE USAGE IN SCONSCRIPT
# =============================================================================

def example_sconscript():
    """
    Example of how to use the new features in a SConscript file.
    """
    sconscript_content = '''
from building import *

# Get environment
env = GetEnvironment()

# Method 1: Use new environment methods (if available)
if hasattr(env, 'DefineGroup'):
    # New OOP style
    src = env.GlobFiles('*.c')
    group = env.DefineGroup('MyComponent', src, depend=['RT_USING_XXX'])
else:
    # Fallback to traditional style
    src = Glob('*.c')
    group = DefineGroup('MyComponent', src, depend=['RT_USING_XXX'])

# Method 2: Always compatible style
src = Glob('*.c')
group = DefineGroup('MyComponent', src, depend=['RT_USING_XXX'])

Return('group')
'''
    return sconscript_content

# =============================================================================
# MINIMAL CHANGES SUMMARY
# =============================================================================

"""
Summary of changes needed in building.py:

1. Add imports at the beginning (5 lines)
2. Add initialization in PrepareBuilding (6 lines)  
3. Add config loading after rtconfig.h parsing (3 lines)
4. Modify DefineGroup to check for new method (3 lines)
5. Modify GetDepend to check for new method (3 lines)
6. Enhance MergeGroup to register with new system (15 lines)

Total: ~35 lines of code added/modified in building.py

Benefits:
- Fully backward compatible
- Opt-in design (works even if ng module is not present)
- Gradual migration path
- No changes needed in existing SConscript files
"""
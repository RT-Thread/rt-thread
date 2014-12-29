import os

Import('RTT_ROOT')
from building import *

def _ft_get_src_path(fn):
    # from docs/INSTALL.ANY
    ft_base_src = set([
        # use the ftsystem ourown
        #'ftsystem.c'
        'ftinit.c',
        'ftdebug.c',

        'ftbase.c',

        'ftbbox.c',
        'ftglyph.c',

        'ftbdf.c',
        'ftbitmap.c',
        'ftcid.c',
        'ftfstype.c',
        'ftgasp.c',
        'ftgxval.c',
        'ftlcdfil.c',
        'ftmm.c',
        'ftotval.c',
        'ftpatent.c',
        'ftpfr.c',
        'ftstroke.c',
        'ftsynth.c',
        'fttype1.c',
        'ftwinfnt.c',
        'ftxf86.c',

        'ftmac.c',
        ])
    ft_s_fn = {
            'type1cid.c' : 'src/cid/',
            'winfnt.c' : 'src/winfonts/',
            'ftcache.c' : 'src/cache/',
            'ftgzip.c' : 'src/gzip/',
            'ftlzw.c' : 'src/lzw/',
            'ftbz2.c' : 'src/bz2/',
            'ftsystem.c' : 'builds/rt-thread/',
            'gb2312tounicode.c' : 'builds/rt-thread/',
            }
    # Always keep the path seperator in unix format.
    if fn in ft_base_src:
        return 'src/base/' + fn
    # Handle special files
    elif fn in ft_s_fn:
        return ft_s_fn[fn] + fn
    else:
        # str.lstrip is not technically right here, but it just work(tm).
        return 'src/' + fn.rstrip('.c') + '/' + fn

# from docs/INSTALL.ANY
ft_deps = {
      'ftcache.c'  : ['ftglyph.c'],
      'ftfstype.c' : ['fttype1.c'],
      'ftglyph.c'  : ['ftbitmap.c'],
      'ftstroke.c' : ['ftglyph.c'],
      'ftsynth.c'  : ['ftbitmap.c'],

      'cff.c'      : ['sfnt.c', 'pshinter.c', 'psnames.c'],
      'truetype.c' : ['sfnt.c', 'psnames.c'],
      'type1.c'    : ['psaux.c' 'pshinter.c', 'psnames.c'],
      'type1cid.c' : ['psaux.c', 'pshinter.c', 'psnames.c'],
      'type42.c'   : ['truetype.c'],
}

ft_modules = {
'autofit.c' : ['FT_Module_Class'   , 'autofit_module_class'         ],
'truetype.c': ['FT_Driver_ClassRec', 'tt_driver_class'              ],
'type1.c'   : ['FT_Driver_ClassRec', 't1_driver_class'              ],
'cff.c'     : ['FT_Driver_ClassRec', 'cff_driver_class'             ],
'type1cid.c': ['FT_Driver_ClassRec', 't1cid_driver_class'           ],
'pfr.c'     : ['FT_Driver_ClassRec', 'pfr_driver_class'             ],
'type42.c'  : ['FT_Driver_ClassRec', 't42_driver_class'             ],
'winfnt.c'  : ['FT_Driver_ClassRec', 'winfnt_driver_class'          ],
'pcf.c'     : ['FT_Driver_ClassRec', 'pcf_driver_class'             ],
'psaux.c'   : ['FT_Module_Class'   , 'psaux_module_class'           ],
'psnames.c' : ['FT_Module_Class'   , 'psnames_module_class'         ],
'pshinter.c': ['FT_Module_Class'   , 'pshinter_module_class'        ],
'raster.c'  : ['FT_Renderer_Class' , 'ft_raster1_renderer_class'    ],
'sfnt.c'    : ['FT_Module_Class'   , 'sfnt_module_class'            ],
'smooth.c'  : ['FT_Renderer_Class' , 'ft_smooth_renderer_class'     ],
#'smooth.c'  : ['FT_Renderer_Class' , 'ft_smooth_lcd_renderer_class' ],
#'smooth.c'  : ['FT_Renderer_Class' , 'ft_smooth_lcdv_renderer_class'],
'bdf.c'     : ['FT_Driver_ClassRec', 'bdf_driver_class'             ],
}

def _ft_build_dep_src(fnli):
    dep_added = False
    for i in fnli:
        for k in ft_deps.get(i, []):
            if k not in fnli:
                dep_added = True
                fnli.append(k)
    if not dep_added:
        return fnli
    else:
        return _ft_build_dep_src(fnli)

def _ft_add_basic_system(fnli):
    for i in ('ftbase.c',
              'ftbbox.c',
              'ftfstype.c',
              'ftglyph.c',
              'ftinit.c',
              'ftlcdfil.c',
              'ftmm.c',
              'ftpatent.c',
              'gb2312tounicode.c',
              'ftsystem.c',):
        if i not in fnli:
            fnli.append(i)
    return fnli

group = []

# Test the depend before do any thing(copy config files etc).
if not GetDepend(['RT_USING_RTGUI', 'RTGUI_USING_TTF']):
    Return('group')

###
# Configurations
###
enabled_modules = ['autofit.c', 'truetype.c', 'smooth.c']

###
#
###

enabled_modules = _ft_add_basic_system(enabled_modules)
enabled_modules = _ft_build_dep_src(enabled_modules)

proj_dir = str(Dir('#'))
config_dir = os.path.join(proj_dir, 'ftconfig')
if not os.path.exists(config_dir):
    os.mkdir(config_dir)

for d, i in (('/include/config/', 'ftconfig.h'),
             ('/builds/rt-thread/', 'ftoption.h')):
    if not os.path.exists(os.path.join(config_dir, i)):
        import shutil
        shutil.copy(GetCurrentDir() + d + i, config_dir)

if not os.path.exists(os.path.join(config_dir, 'ft2build.h')):
    with open(os.path.join(config_dir, 'ft2build.h'), 'w') as e:
        e.write('''
#ifndef __FT2BUILD_H__
#define __FT2BUILD_H__

#define FT_CONFIG_OPTIONS_H  <ftoption.h>
#define FT_CONFIG_MODULES_H  <ftmodule.h>
#define FT_CONFIG_CONFIG_H   <ftconfig.h>

#include <config/ftheader.h>

#endif /* __FT2BUILD_H__ */
''')

f = open(os.path.join(config_dir, 'ftmodule.h'), 'w')
for m in enabled_modules:
    if m in ft_modules:
        f.write('FT_USE_MODULE( ' + ', '.join(ft_modules[m]) + ')\n')

# proj_dir/ftconfig should precede include/ in freetype
cpp_path = [config_dir, os.path.join(GetCurrentDir(), 'include/')]

src_file = [_ft_get_src_path(i) for i in enabled_modules]

group = DefineGroup('FreeType',
                    src_file,
                    CPPPATH = cpp_path,
                    # Depend is tested above
                    depend = [],
                    CPPDEFINES = ['FT2_BUILD_LIBRARY']
                    )

Return('group')

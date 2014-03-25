import os
import sys
from utils import _make_path_relative

def PrefixPath(prefix, path):
    path = os.path.abspath(path)
    prefix = os.path.abspath(prefix)

    if sys.platform == 'win32':
        prefix = prefix.lower()
        path = path.lower()

    if path.startswith(prefix):
        return True
    
    return False

def PrepareUA(project, RTT_ROOT, BSP_ROOT):
    with open('rtua.py', 'w') as ua:
        # ua.write('import os\n')
        # ua.write('import sys\n')
        ua.write('\n')
        
        print RTT_ROOT
        
        CPPPATH = []
        CPPDEFINES = []

        for group in project:
            # get each include path
            if group.has_key('CPPPATH') and group['CPPPATH']:
                CPPPATH += group['CPPPATH']

            # get each group's definitions
            if group.has_key('CPPDEFINES') and group['CPPDEFINES']:
                CPPDEFINES += group['CPPDEFINES']

        if len(CPPPATH):
            # use absolute path 
            for i in range(len(CPPPATH)):
                CPPPATH[i] = os.path.abspath(CPPPATH[i])

            # remove repeat path
            paths = [i for i in set(CPPPATH)]
            CPPPATH = []
            for path in paths:
                if PrefixPath(RTT_ROOT, path):
                    CPPPATH += ['RTT_ROOT + "/%s",' % _make_path_relative(RTT_ROOT, path).replace('\\', '/')]
                
                elif PrefixPath(BSP_ROOT, path):
                    CPPPATH += ['BSP_ROOT + "/%s",' % _make_path_relative(BSP_ROOT, path).replace('\\', '/')]
                else:
                    CPPPATH += ['"%s",' % path.replace('\\', '/')]

            CPPPATH.sort()
            ua.write('def GetCPPPATH(BSP_ROOT, RTT_ROOT):\n')
            ua.write('\tCPPPATH=[\n')
            for path in CPPPATH:
                ua.write('\t\t%s\n' % path)
            ua.write('\t]\n\n')
            ua.write('\treturn CPPPATH\n\n')

        if len(CPPDEFINES):
            CPPDEFINES = [i for i in set(CPPDEFINES)]

            ua.write('def GetCPPDEFINES():\n')
            ua.write('\tCPPDEFINES=%s\n' % str(CPPDEFINES))
            ua.write('\treturn CPPDEFINES\n\n')
            
            print CPPDEFINES

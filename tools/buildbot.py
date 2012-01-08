import os
import sys

def usage():
    print '%s all     -- build all bsp' % os.path.basename(sys.argv[0])
    print '%s clean   -- clean all bsp' % os.path.basename(sys.argv[0])
    print '%s project -- update all prject files' % os.path.basename(sys.argv[0])

BSP_ROOT = '../bsp'
if len(sys.argv) != 2:
	usage()
	sys.exit(0)

# get command options
command = ''
if sys.argv[1] == 'all':
    command = ' '
elif sys.argv[1] == 'clean':
    command = ' -c'
elif sys.argv[1] == 'project':
    command = ' --target=mdk -s'
else:
    usage()
    sys.exit(0)

projects = os.listdir(BSP_ROOT)
for item in projects:
    project_dir = os.path.join(BSP_ROOT, item)
    if os.path.isfile(os.path.join(project_dir, 'SConstruct')):
        if os.system('scons --directory=' + project_dir + command) != 0:
            print 'build failed!!'
            break

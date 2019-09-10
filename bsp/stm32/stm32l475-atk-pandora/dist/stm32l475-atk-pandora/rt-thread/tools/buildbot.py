import os
import sys

def usage():
    print '%s all     -- build all bsp' % os.path.basename(sys.argv[0])
    print '%s clean   -- clean all bsp' % os.path.basename(sys.argv[0])
    print '%s project -- update all prject files' % os.path.basename(sys.argv[0])

BSP_ROOT = os.path.join("..", "bsp")

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

    projects = os.listdir(BSP_ROOT)
    for item in projects:
        project_dir = os.path.join(BSP_ROOT, item)

        if os.path.isfile(os.path.join(project_dir, 'template.Uv2')):
            print ('prepare MDK3 project file on ' + project_dir)
            command = ' --target=mdk -s'

            os.system('scons --directory=' + project_dir + command)

        if os.path.isfile(os.path.join(project_dir, 'template.uvproj')):
            print ('prepare MDK4 project file on ' + project_dir)
            command = ' --target=mdk4 -s'

            os.system('scons --directory=' + project_dir + command)

        if os.path.isfile(os.path.join(project_dir, 'template.uvprojx')):
            print ('prepare MDK5 project file on ' + project_dir)
            command = ' --target=mdk5 -s'

            os.system('scons --directory=' + project_dir + command)

        if os.path.isfile(os.path.join(project_dir, 'template.ewp')):
            print ('prepare IAR project file on ' + project_dir)
            command = ' --target=iar -s'

            os.system('scons --directory=' + project_dir + command)

    sys.exit(0)
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

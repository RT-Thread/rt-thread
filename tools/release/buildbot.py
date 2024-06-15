import os
import sys

def usage():
    print('%s all     -- build all bsp' % os.path.basename(sys.argv[0]))
    print('%s clean   -- clean all bsp' % os.path.basename(sys.argv[0]))
    print('%s update  -- update all prject files' % os.path.basename(sys.argv[0]))

BSP_ROOT = os.path.join("..", "..", "bsp")

if len(sys.argv) != 2:
    usage()
    sys.exit(0)

def update_project_file(project_dir):
    if os.path.isfile(os.path.join(project_dir, 'template.Uv2')):
        print('prepare MDK3 project file on ' + project_dir)
        command = ' --target=mdk -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

    if os.path.isfile(os.path.join(project_dir, 'template.uvproj')):
        print('prepare MDK4 project file on ' + project_dir)
        command = ' --target=mdk4 -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

    if os.path.isfile(os.path.join(project_dir, 'template.uvprojx')):
        print('prepare MDK5 project file on ' + project_dir)
        command = ' --target=mdk5 -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

    if os.path.isfile(os.path.join(project_dir, 'template.ewp')):
        print('prepare IAR project file on ' + project_dir)
        command = ' --target=iar -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')


def update_all_project_files(root_path):
    # current path is dir
    if os.path.isdir(root_path):
        projects = os.listdir(root_path)
        # is a project path?
        if "SConstruct" in projects:
            try:
                # update rtconfig.h and .config
                if "Kconfig" in projects:
                    if "win32" in sys.platform:
                        retval = os.getcwd()
                        os.chdir(root_path)
                        os.system("menuconfig --silent")
                        os.chdir(retval)
                    else:
                        os.system('scons --pyconfig-silent -C {0}'.format(root_path))
                update_project_file(root_path)
            except Exception as e:
                print("error message: {}".format(e))
                sys.exit(-1)
        else:
            for i in projects:
                new_root_path = os.path.join(root_path, i)
                update_all_project_files(new_root_path)

# get command options
command = ''
if sys.argv[1] == 'all':
    command = ' '
elif sys.argv[1] == 'clean':
    command = ' -c'
elif sys.argv[1] == 'update':
    print('begin to update all the bsp projects')

    from stm32_update import stm32_update
    stm32_update(os.path.join(BSP_ROOT, 'stm32'))

    update_all_project_files(BSP_ROOT)

    print('finished!')
    sys.exit(0)
else:
    usage()
    sys.exit(0)

projects = os.listdir(BSP_ROOT)
for item in projects:
    project_dir = os.path.join(BSP_ROOT, item)
    if os.path.isfile(os.path.join(project_dir, 'SConstruct')):
        if os.system('scons --directory=' + project_dir + command) != 0:
            print('build failed!!')
            break

import os

# make rtconfig.h from .config

def mk_rtconfig(filename):
    try:
        config = file(filename)
    except:
        print('open config:%s failed' % filename)
        return

    rtconfig = file('rtconfig.h', 'w')
    rtconfig.write('#ifndef RT_CONFIG_H__\n')
    rtconfig.write('#define RT_CONFIG_H__\n\n')

    empty_line = 1

    for line in config:
        line = line.lstrip(' ').replace('\n', '').replace('\r', '')

        if len(line) == 0: continue

        if line[0] == '#':
            if len(line) == 1:
                if empty_line:
                    continue

                rtconfig.write('\n')
                empty_line = 1
                continue

            comment_line = line[1:]
            if line.startswith('# CONFIG_'): line = ' ' + line[9:]
            else: line = line[1:]

            rtconfig.write('/*%s */\n' % line)
            empty_line = 0
        else:
            empty_line = 0
            setting = line.split('=')
            if len(setting) >= 2:
                if setting[0].startswith('CONFIG_'):
                    setting[0] = setting[0][7:]

                # remove CONFIG_PKG_XX_PATH or CONFIG_PKG_XX_VER
                if type(setting[0]) == type('a') and (setting[0].endswith('_PATH') or setting[0].endswith('_VER')):
                    continue

                if setting[1] == 'y':
                    rtconfig.write('#define %s\n' % setting[0])
                else:
                    rtconfig.write('#define %s %s\n' % (setting[0], setting[1]))

    if os.path.isfile('rtconfig_project.h'):
        rtconfig.write('#include "rtconfig_project.h"\n')

    rtconfig.write('\n')
    rtconfig.write('#endif\n')
    rtconfig.close()

def config():
    mk_rtconfig('.config')

def get_env_dir():
    if os.environ.get('ENV_ROOT'):
        return os.environ.get('ENV_ROOT')

    home_dir = os.environ['HOME']
    env_dir  = os.path.join(home_dir, '.env')

    if not os.path.exists(env_dir):
        return None

    return env_dir

def touch_env():
    home_dir = os.environ['HOME']
    env_dir  = os.path.join(home_dir, '.env')
    if not os.path.exists(env_dir):
        os.mkdir(env_dir)
        os.mkdir(os.path.join(env_dir, 'local_pkgs'))
        os.mkdir(os.path.join(env_dir, 'packages'))

        os.system('git clone https://github.com/RT-Thread/packages.git ~/.env/packages/packages')

        kconfig = file(os.path.join(env_dir, 'packages', 'Kconfig'), 'w')
        kconfig.write('source "$PKGS_DIR/packages/Kconfig"')

        os.mkdir(os.path.join(env_dir, 'tools'))
        os.system('git clone https://github.com/RT-Thread/env.git ~/.env/tools/scripts')

        env_sh = file(os.path.join(env_dir, 'env.sh'), 'w')
        env_sh.write('export PATH=~/.env/tools/scripts:$PATH')

# menuconfig for Linux
def menuconfig(RTT_ROOT):
    kconfig_dir = os.path.join(RTT_ROOT, 'tools', 'kconfig-frontends')
    os.system('scons -C ' + kconfig_dir)

    env_dir = get_env_dir()
    if not env_dir:
        touch_env()
        env_dir = get_env_dir()

    os.environ['PKGS_ROOT'] = os.path.join(env_dir, 'packages')

    fn = '.config'

    if os.path.isfile(fn):
        mtime = os.path.getmtime(fn)
    else:
        mtime = -1

    kconfig_cmd = os.path.join(RTT_ROOT, 'tools', 'kconfig-frontends', 'kconfig-mconf')
    os.system(kconfig_cmd + ' Kconfig')

    if os.path.isfile(fn):
        mtime2 = os.path.getmtime(fn)
    else:
        mtime2 = -1

    # make rtconfig.h
    if mtime != mtime2:
        mk_rtconfig(fn)


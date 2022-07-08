import os

def GetStringFromConfig(bsp_dir, string):
    try:
        config = open(bsp_dir + '/rtconfig.h', 'r')
    except IOError:
        print('no found rtconfig.h, use scons --menuconfig before compile')
    else:
        cfg_list = config.readlines()
        for cfg in cfg_list:
            if cfg.find(string) != -1:
                target = cfg[cfg.find('"'):-1]
                target = eval(target)
                config.close()
                return target
        print('no found ' + string + ' in rtconfig.h, you must define this in kconfig of board')

    return ''

def GetRTConfigOption(bsp_dir, option):
    value = False
    try:
        config = open(bsp_dir + '/rtconfig.h', 'r')
    except IOError:
        print('no found rtconfig.h, use scons --menuconfig before compile')
    else:
        cfg_list = config.readlines()
        for cfg in cfg_list:
            if cfg.find('#define ' + option) != -1:
                cfg = cfg.rstrip('\n')
                values = cfg.split(' ')

                if len(values) == 3:
                    value = values[2]
                else:
                    value = True

                config.close()
                return value

    return value

def GetImageSetting(bsp_dir):
    board = GetStringFromConfig(bsp_dir, 'RT_BOARD_NAME')
    path = 'board/{dir}/setting.ini'.format(dir = board)
    if (bsp_dir.endswith('/') == False):
        bsp_dir += '/'
    if os.path.exists(bsp_dir + path) == True:
        return path
    else:
        return 'board/common/setting.ini'

def ParsePartitionStart(bsp_dir, name):
    start = -1
    path = GetImageSetting(bsp_dir)
    configer = configparser.ConfigParser()
    configer.read(path)
    for section in configer.sections():
        if (configer.has_option(section, 'Name')):
            if configer.get(section, 'Name') == name:
                sector = int(configer.get(section, 'PartOffset'), 16)
                start = (sector + 1) * 512
    return start

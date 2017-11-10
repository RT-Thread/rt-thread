import os

# make rtconfig.h from .config

def mk_rtconfig(filename):
    try:
        config = file(filename)
    except:
        print 'open .config failed'
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

            rtconfig.write('/*%s */\n' % line[1:])
            empty_line = 0
        else:
            empty_line = 0
            setting = line.split('=', 1)
            if len(setting) >= 2:
                if setting[0].startswith('CONFIG_'):
                    setting[0] = setting[0][7:]

                if setting[1] == 'y':
                    rtconfig.write('#define %s\n' % setting[0])
                else:
                    rtconfig.write('#define %s %s\n' % (setting[0], setting[1]))

    rtconfig.write('#endif\n')
    rtconfig.close()

def config():
    mk_rtconfig('.config')


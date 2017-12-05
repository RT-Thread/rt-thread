import os
import rtconfig
def DoDownloading(Tool, target, Command, Parameter):
    BAT_SUCCESS  = 2
    if Tool == 'keil':
        print 'target file is ..'
        if os.path.exists(target) == True:
            print "...exist, now open MDK downloaded command ... ... "
            if os.system(Command + " -f " + Parameter) == BAT_SUCCESS:
                print '...complete!'
            else:
                print '...failure!'
        else:
            print '...Non-existent'
    else:
        print 'please select keil as download tool, the currect tool is: ' + rtconfig.CROSS_TOOL
DoDownloading(rtconfig.CROSS_TOOL, rtconfig.TARGET, rtconfig.DOWNLOAD_COMMAND_PATH, rtconfig.PROJECT_PATH)

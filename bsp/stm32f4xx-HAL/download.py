
import os
import rtconfig
BAT_SUCCESS           = 2
print 'target file is ..'
if os.path.exists(rtconfig.TARGET) == True:
    print "...exist, now open MDK downloaded command ... ... "
    if os.system(rtconfig.DOWNLOAD_COMMAND_PATH + " -f " + rtconfig.PARAMETER) == BAT_SUCCESS:
        print '...success!'
    else:
        print '...failure!'
else:
    print '...Non-existent'

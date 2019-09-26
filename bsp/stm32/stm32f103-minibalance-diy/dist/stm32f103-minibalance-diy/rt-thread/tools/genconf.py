import os

def genconfig() :
    from SCons.Script import SCons

    PreProcessor = SCons.cpp.PreProcessor()

    try:
        f = open('rtconfig.h', 'r')
        contents = f.read()
        f.close()
    except :
        print("Open rtconfig.h file failed.")

    PreProcessor.process_contents(contents)
    options = PreProcessor.cpp_namespace

    try:
        f = open('.config', 'w')
        for (opt, value) in options.items():
            if type(value) == type(1):
                f.write("CONFIG_%s=%d\n" % (opt, value))

            if type(value) == type('') and value == '':
                f.write("CONFIG_%s=y\n" % opt)
            elif type(value) == type('str'):
                f.write("CONFIG_%s=%s\n" % (opt, value))

        print("Generate .config done!")
        f.close()
    except:
        print("Generate .config file failed.")

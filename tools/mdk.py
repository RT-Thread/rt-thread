import os
import string
import SCons.Script

def _get_filetype(fn):
    if fn.rfind('.c') != -1 or fn.rfind('.C') != -1 or fn.rfind('.cpp') != -1:
        return 1
    
    # assimble file type
    if fn.rfind('.s') != -1 or fn.rfind('.S') != -1:
        return 2
    
    # header type 
    if fn.rfind('.h') != -1:
        return 5
    
    # other filetype 
    return 5

def splitall(loc):
    """
    Return a list of the path components in loc. (Used by relpath_).
    
    The first item in the list will be  either ``os.curdir``, ``os.pardir``, empty,
    or the root directory of loc (for example, ``/`` or ``C:\\).
    
    The other items in the list will be strings.
        
    Adapted from *path.py* by Jason Orendorff.
    """
    parts = []
    while loc != os.curdir and loc != os.pardir:
        prev = loc
        loc, child = os.path.split(prev)
        if loc == prev:
            break
        parts.append(child)
    parts.append(loc)
    parts.reverse()
    return parts

def _make_path_relative(origin, dest):
    """
    Return the relative path between origin and dest.
    
    If it's not possible return dest.
    
    
    If they are identical return ``os.curdir``
    
    Adapted from `path.py <http://www.jorendorff.com/articles/python/path/>`_ by Jason Orendorff. 
    """
    origin = os.path.abspath(origin).replace('\\', '/')
    dest = os.path.abspath(dest).replace('\\', '/')
    #
    orig_list = splitall(os.path.normcase(origin))
    # Don't normcase dest!  We want to preserve the case.
    dest_list = splitall(dest)
    #
    if orig_list[0] != os.path.normcase(dest_list[0]):
        # Can't get here from there.
        return dest
    #
    # Find the location where the two paths start to differ.
    i = 0
    for start_seg, dest_seg in zip(orig_list, dest_list):
        if start_seg != os.path.normcase(dest_seg):
            break
        i += 1
    #
    # Now i is the point where the two paths diverge.
    # Need a certain number of "os.pardir"s to work up
    # from the origin to the point of divergence.
    segments = [os.pardir] * (len(orig_list) - i)
    # Need to add the diverging part of dest_list.
    segments += dest_list[i:]
    if len(segments) == 0:
        # If they happen to be identical, use os.curdir.
        return os.curdir
    else:
        # return os.path.join(*segments).replace('\\', '/')
        return os.path.join(*segments)

def MDKProject(target, script):
    template = file('template.uV2', "rb")
    lines = template.readlines()

    project = file(target, "wb")
    project_path = os.path.dirname(os.path.abspath(target))

    line_index = 5
    # write group 
    for group in script:
        lines.insert(line_index, 'Group (%s)\r\n' % group['name'])
        line_index += 1
    
    lines.insert(line_index, '\r\n')
    line_index += 1
    
    # write file
    
    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''

    # number of groups 
    group_index = 1
    for group in script:
        # print group['name']

        # get each include path
        if group.has_key('CPPPATH') and group['CPPPATH']:
            if CPPPATH:
                CPPPATH += group['CPPPATH']
            else:
                CPPPATH += group['CPPPATH']

        # get each group's definitions
        if group.has_key('CPPDEFINES') and group['CPPDEFINES']:
            if CPPDEFINES:
                CPPDEFINES += ';' + group['CPPDEFINES']
            else:
                CPPDEFINES += group['CPPDEFINES']

        # get each group's link flags 
        if group.has_key('LINKFLAGS') and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']

        # generate file items
        for node in group['src']:
            fn = node.rfile()
            name = fn.name
            path = os.path.dirname(fn.abspath)
            path = _make_path_relative(project_path, path)
            path = os.path.join(path, name)
            lines.insert(line_index, 'File %d,%d,<%s><%s>\r\n' 
                % (group_index, _get_filetype(name), path, name))
            line_index += 1

        group_index = group_index + 1

    lines.insert(line_index, '\r\n')
    line_index += 1

    # remove repeat path
    paths = set()
    for path in CPPPATH:
        inc = _make_path_relative(project_path, os.path.normpath(path))
        paths.add(inc) #.replace('\\', '/')

    paths = [i for i in paths]
    CPPPATH = string.join(paths, ';')
    
    definitions = [i for i in set(CPPDEFINES)]
    CPPDEFINES = string.join(definitions, ', ')

    while line_index < len(lines):
        if lines[line_index].startswith(' ADSCINCD '):
            lines[line_index] = ' ADSCINCD (' + CPPPATH + ')\r\n'
        
        if lines[line_index].startswith(' ADSLDMC ('):
            lines[line_index] = ' ADSLDMC (' + LINKFLAGS + ')\r\n'
        
        if lines[line_index].startswith(' ADSCDEFN ('):
            lines[line_index] = ' ADSCDEFN (' + CPPDEFINES + ')\r\n'
            
        line_index += 1

    # write project
    for line in lines:
        project.write(line)

    project.close()

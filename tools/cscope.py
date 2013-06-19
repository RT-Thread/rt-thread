import os

def _get_src(project):
    li = []
    for group in project:
        for f in group['src']:
            li.append(os.path.normpath(f.rfile().abspath))
    return li

def _get_header_dir(dirp):
    li = []
    for root, dirs, files in os.walk(dirp):
        for d in dirs:
            fpath = os.path.join(root, d)
            li.extend(_get_header_dir(fpath))

        for f in files:
            if f[-2:] == '.h':
                fpath = os.path.join(root, f)
                li.append(os.path.normpath(fpath))
    return li

def _get_header(project):
    li = []
    for g in project:
        for d in g.get('CPPPATH', []):
            li.extend(_get_header_dir(d))
    return li

def CscopeDatabase(project):
    files = set(_get_src(project) + _get_header(project))
    with open('cscope.files', 'w') as db:
        db.write('-k\n-q\n')
        db.write('\n'.join(files))
        db.flush() # let cscope see the full content
        os.system('cscope -b')


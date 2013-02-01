#encoding: utf-8
from perfect_hash import perfect_hash

import re, string, os, random

cur_dir = os.path.abspath(os.path.dirname(__file__))

unicode_chinese_re = u'[\u2E80-\u2EFF\u2F00-\u2FDF\u3000-\u303F\u31C0-\u31EF\u3200-\u32FF\u3300-\u33FF\u3400-\u4DBF\u4DC0-\u4DFF\u4E00-\u9FBF\uF900-\uFAFF\uFE30-\uFE4F\uFF00-\uFFEF]'
match_re = re.compile(unicode_chinese_re)

def _get_font_lib(f):
    reading_data = False
    data = []
    for i in f.readlines():
        if i.strip() == 'FONT_BMP_DATA_BEGIN':
            reading_data = True
            continue
        if i.strip() == 'FONT_BMP_DATA_END':
            break
        if reading_data:
            line = [k for k in i.strip().split(',') if k]
            data.extend([int(k, 16) for k in line])
    return data

class font_lib(object):
    def __init__(self, f, width, height, encoding):
        self.width = width
        self.height = height
        self._lib = _get_font_lib(f)
        # byte per charactor
        self._bpc = (width+7)//8*height
        self.encoding = encoding
        self._finished_push = False

        self.char_dict = {}

    def get_char_data(self, char):
        #char_gb = char.encode(self.encoding)

        # copied from font_hz_bmp.c
        sec, idx = [ord(i) - 0xA0 for i in char]
        #print 'sec %d, idx %d for' % (sec, idx), char
        start = (94 * (sec-1) + (idx-1)) * self._bpc
        return self._lib[start:start+self._bpc]

    def push_char(self, c):
        self.char_dict[c] = self.char_dict.get(c, 0) + 1

    def push_file(self, f):
        try:
            for i in f:
                t = re.findall(match_re, unicode(i.decode(self.encoding)))
                if t:
                    for c in t:
                        self.push_char(c.encode(self.encoding))
        except UnicodeDecodeError as e:
            try:
                print 'error in decoding %s' % f.name
            except:
                print 'error in decoding string %s' % f
            # re-raise the exception and terminate the building process
            raise

    def _finish_push(self):
        if self._finished_push:
            return

        self._char_li = zip(self.char_dict.keys(), self.char_dict.values())
        self._char_li.sort(key=lambda x:x[1], reverse=True)
        self._finished_push = True

        #for i in self._char_li:
            #print i[0], i[1]

    def get_hash_map(self):
        self._finish_push()
        li = []
        for  i, k in enumerate(self._char_li):
            li.append((k[0], i))
        return li

    def get_new_font_lib(self):
        self._finish_push()
        dat = []
        for c, f in self._char_li:
            dat.extend(self.get_char_data(c))
        return dat

    def finish(self):
        return self.get_hash_map(), self.get_new_font_lib()

class mph_options(object):
    'mock object for options'
    def __init__(self, verbose=4, delimiter=', ', indent=4, width=80):
        self.verbose = verbose
        self.delimiter = delimiter
        self.indent = indent
        self.width = width

def gen_char_mph(font_lib):
    template = open(os.path.join(cur_dir, '..', 'common', 'font_mph-tmpl.c'), 'r').read()
    opt = mph_options()
    hmap, flib = font_lib.finish()
    #print 'compact font lib: %d chars included.' % len(hmap)
    #for i in hmap:
        #print i[0], repr(i[0]), i[1]
    code = perfect_hash.generate_code(hmap, template, perfect_hash.Hash2, opt,
            extra_subs={
                'width':str(font_lib.width),
                'height':str(font_lib.height),
                'font_data':', '.join([hex(i) for i in flib])})

    return code

# {name:[file_name, height, width, encoding, instance]}
_font_map = {'hz16':{'fname':'common/hz16font.c',
                     'height':16,
                     'width':16,
                     'encoding':'GB2312',
                     'flib':None},
             'hz12':{'fname':'common/hz12font.c',
                     'height':12,
                     'width':12,
                     'encoding':'GB2312',
                     'flib':None}
            }

def get_font_lib(name):
    if name not in _font_map.keys():
        return None

    if _font_map[name]['flib'] is None:
        _font_map[name]['flib'] = font_lib(open(
                                       os.path.join(cur_dir, '..', _font_map[name]['fname']), 'r'),
                                       _font_map[name]['height'],
                                       _font_map[name]['width'],
                                       _font_map[name]['encoding'])
    return _font_map[name]['flib']

def gen_cmp_font_file():
    for i in _font_map:
        fl = _font_map[i]['flib']
        if fl is not None:
            code = gen_char_mph(fl)
            with open(os.path.join(cur_dir, '..', 'common', 'font_cmp_%s.c' % i), 'w') as f:
                f.write(code)

if __name__ == '__main__':
    import sys

    lib = get_font_lib('hz16')
    libn = get_font_lib('hz16')
    assert(lib is libn)

    lib.push_file(open(sys.argv[1], 'rb'))

    hmap, flib = lib.finish()
    for i in hmap:
        print i[0], i[1]

    assert(len(flib) == 32 * len(hmap))

    print gen_char_mph(lib)

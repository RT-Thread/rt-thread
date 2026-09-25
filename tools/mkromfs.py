#!/usr/bin/env python

import sys
import os

import struct
from collections import namedtuple
import io


def _make_c_identifier(name):
    encoded = os.fsencode(name)
    chars = []
    for byte in encoded:
        is_digit = ord('0') <= byte <= ord('9')
        is_upper = ord('A') <= byte <= ord('Z')
        is_lower = ord('a') <= byte <= ord('z')
        if is_digit or is_upper or is_lower or byte == ord('_'):
            chars.append(chr(byte))
        else:
            chars.append('_%02x' % byte)

    if not chars:
        chars.append('empty')
    if chars[0].isdigit():
        chars.insert(0, '_')
    return '_' + ''.join(chars)


def _unique_c_identifier(name, used):
    base = _make_c_identifier(name)
    candidate = base
    index = 1
    while candidate in used:
        candidate = '%s_%d' % (base, index)
        index += 1
    used.add(candidate)
    return candidate


def _c_string_literal(value):
    escaped = []
    for byte in os.fsencode(value):
        if byte == ord('\\'):
            escaped.append('\\\\')
        elif byte == ord('"'):
            escaped.append('\\\"')
        elif byte == ord('\n'):
            escaped.append('\\n')
        elif byte == ord('\r'):
            escaped.append('\\r')
        elif byte == ord('\t'):
            escaped.append('\\t')
        elif 0x20 <= byte <= 0x7e:
            escaped.append(chr(byte))
        else:
            escaped.append('\\%03o' % byte)
    return '"' + ''.join(escaped) + '"'

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('rootdir', type=str, help='the path to rootfs')
parser.add_argument('output', type=argparse.FileType('wb'), nargs='?', help='output file name')
parser.add_argument('--dump', action='store_true', help='dump the fs hierarchy')
parser.add_argument('--binary', action='store_true', help='output binary file')
parser.add_argument('--addr', default='0', help='set the base address of the binary file, default to 0.')

class File(object):
    def __init__(self, name, path=None):
        self._name = name
        self._path = path if path is not None else name
        self._data = open(self._path, 'rb').read()
        self._c_name = None

    @property
    def name(self):
        return self._name

    @property
    def c_name(self):
        if self._c_name is not None:
            return self._c_name
        return _make_c_identifier(self._name)

    def set_c_name(self, c_name):
        self._c_name = c_name

    @property
    def bin_name(self):
        # Pad to 4 bytes boundary with \0
        pad_len = 4
        bn = self._name + '\0' * (pad_len - len(self._name) % pad_len)
        return bn

    def c_data(self, prefix=''):
        '''Get the C code represent of the file content.'''
        head = 'static const rt_uint8_t %s[] = {\n' % \
                (prefix + self.c_name)
        tail = '\n};'

        if self.entry_size == 0:
            return ''
        if len(self._data) > 0 and type(self._data[0]) == int:
            return head + ','.join(('0x%02x' % i for i in self._data)) + tail
        else:
            return head + ','.join(('0x%02x' % ord(i) for i in self._data)) + tail

    @property
    def entry_size(self):
        return len(self._data)

    def bin_data(self, base_addr=0x0):
        return bytes(self._data)

    def dump(self, indent=0):
        print('%s%s' % (' ' * indent, self._name))

class Folder(object):
    bin_fmt = struct.Struct('IIII')
    bin_item = namedtuple('dirent', 'type, name, data, size')

    def __init__(self, name, path=None):
        self._name = name
        self._path = path
        self._children = []
        self._c_name = None

    @property
    def name(self):
        return self._name

    @property
    def c_name(self):
        if self._c_name is not None:
            return self._c_name
        return _make_c_identifier(self._name)

    def set_c_name(self, c_name):
        self._c_name = c_name

    @property
    def bin_name(self):
        # Pad to 4 bytes boundary with \0
        pad_len = 4
        bn = self._name + '\0' * (pad_len - len(self._name) % pad_len)
        return bn

    def walk(self):
        root = self._path if self._path is not None else u'.'
        for ent in os.listdir(root):
            path = os.path.join(root, ent)
            if os.path.isdir(path):
                d = Folder(ent, path)
                d.walk()
                self._children.append(d)
            else:
                self._children.append(File(ent, path))

    def sort(self):
        def _sort(x, y):
            if x.name == y.name:
                return 0
            elif x.name > y.name:
                return 1
            else:
                return -1
        from functools import cmp_to_key
        self._children.sort(key=cmp_to_key(_sort))

        # sort recursively
        for c in self._children:
            if isinstance(c, Folder):
                c.sort()

    def assign_c_names(self):
        if self._c_name is None:
            self._c_name = _make_c_identifier(self._name)

        used = set()
        for c in self._children:
            c.set_c_name(_unique_c_identifier(c.name, used))

        for c in self._children:
            if isinstance(c, Folder):
                c.assign_c_names()

    def dump(self, indent=0):
        print('%s%s' % (' ' * indent, self._name))
        for c in self._children:
            c.dump(indent + 1)

    def c_data(self, prefix=''):
        '''get the C code represent of the folder.

           It is recursive.'''
        # make the current dirent
        # static is good. Only root dirent is global visible.
        if self.entry_size == 0:
            return ''

        dhead = 'static const struct romfs_dirent %s[] = {\n' % (prefix + self.c_name)
        dtail = '\n};'
        body_fmt = '    {{{type}, {name}, (rt_uint8_t *){data}, sizeof({data})/sizeof({data}[0])}}'
        body_fmt0= '    {{{type}, {name}, RT_NULL, 0}}'
        # prefix of children
        cpf = prefix+self.c_name
        body_li = []
        payload_li = []
        for c in self._children:
            entry_size = c.entry_size
            if isinstance(c, File):
                tp = 'ROMFS_DIRENT_FILE'
            elif isinstance(c, Folder):
                tp = 'ROMFS_DIRENT_DIR'
            else:
                assert False, 'Unkown instance:%s' % str(c)
            if entry_size == 0:
                body_li.append(body_fmt0.format(type=tp,
                                                name=_c_string_literal(c.name)))
            else:
                body_li.append(body_fmt.format(type=tp,
                                            name=_c_string_literal(c.name),
                                            data=cpf+c.c_name))
            payload_li.append(c.c_data(prefix=cpf))

        # All the data we need is defined in payload so we should append the
        # dirent to it. It also meet the depth-first policy in this code.
        payload_li.append(dhead + ',\n'.join(body_li) + dtail)

        return '\n\n'.join(payload_li)

    @property
    def entry_size(self):
        return len(self._children)

    def bin_data(self, base_addr=0x0):
        '''Return StringIO object'''
        # The binary layout is different from the C code layout. We put the
        # dirent before the payload in this mode. But the idea is still simple:
        #                           Depth-First.

        #{
        #  rt_uint32_t type;
        #  const char *name;
        #  const rt_uint8_t *data;
        #  rt_size_t size;
        #}
        d_li = []
        # payload base
        p_base = base_addr + self.bin_fmt.size * self.entry_size
        # the length to record how many data is in
        v_len = p_base
        # payload
        p_li = []
        for c in self._children:
            if isinstance(c, File):
                # ROMFS_DIRENT_FILE
                tp = 0
            elif isinstance(c, Folder):
                # ROMFS_DIRENT_DIR
                tp = 1
            else:
                assert False, 'Unkown instance:%s' % str(c)

            name = bytes(c.bin_name.encode('utf-8'))
            name_addr = v_len
            v_len += len(name)

            data = c.bin_data(base_addr=v_len)
            data_addr = v_len
            # pad the data to 4 bytes boundary
            pad_len = 4
            if len(data) % pad_len != 0:
                data += ('\0' * (pad_len - len(data) % pad_len)).encode('utf-8')
            v_len += len(data)

            d_li.append(self.bin_fmt.pack(*self.bin_item(
                                               type=tp,
                                               name=name_addr,
                                               data=data_addr,
                                               size=c.entry_size)))

            p_li.extend((name, data))

        return bytes().join(d_li) + bytes().join(p_li)

def get_c_data(tree):
    # Handle the root dirent specially.
    root_dirent_fmt = '''/* Generated by mkromfs. Edit with caution. */
#include <rtthread.h>
#include <dfs_romfs.h>

{data}

const struct romfs_dirent {name} = {{
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *){rootdirent}, sizeof({rootdirent})/sizeof({rootdirent}[0])
}};
'''

    return root_dirent_fmt.format(name='romfs_root',
                                  rootdirent=tree.c_name,
                                  data=tree.c_data())

def get_bin_data(tree, base_addr):
    v_len = base_addr + Folder.bin_fmt.size
    name = bytes('/\0\0\0'.encode("utf-8"))
    name_addr = v_len
    v_len += len(name)
    data_addr = v_len
    # root entry
    data = Folder.bin_fmt.pack(*Folder.bin_item(type=1,
                                                name=name_addr,
                                                data=data_addr,
                                                size=tree.entry_size))
    return data + name + tree.bin_data(v_len)

if __name__ == '__main__':
    args = parser.parse_args()

    tree = Folder('romfs_root', args.rootdir)
    tree.walk()
    tree.sort()
    tree.assign_c_names()

    if args.dump:
        tree.dump()

    if args.binary:
        data = get_bin_data(tree, int(args.addr, 16))
    else:
        data = get_c_data(tree).encode()

    output = args.output
    if output:
        output.write(data)
    elif args.binary:
        sys.stdout.buffer.write(data)
    else:
        sys.stdout.write(data.decode())

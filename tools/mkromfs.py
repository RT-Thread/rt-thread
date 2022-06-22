#!/usr/bin/env python

import sys
import os

import struct
from collections import namedtuple
import io

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('rootdir', type=str, help='the path to rootfs')
parser.add_argument('output', type=argparse.FileType('wb'), nargs='?', help='output file name')
parser.add_argument('--dump', action='store_true', help='dump the fs hierarchy')
parser.add_argument('--binary', action='store_true', help='output binary file')
parser.add_argument('--addr', default='0', help='set the base address of the binary file, default to 0.')

class File(object):
    def __init__(self, name):
        self._name = name
        self._data = open(name, 'rb').read()

    @property
    def name(self):
        return self._name

    @property
    def c_name(self):
        return '_' + self._name.replace('.', '_')

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

    def __init__(self, name):
        self._name = name
        self._children = []

    @property
    def name(self):
        return self._name

    @property
    def c_name(self):
        # add _ to avoid conflict with C key words.
        return '_' + self._name

    @property
    def bin_name(self):
        # Pad to 4 bytes boundary with \0
        pad_len = 4
        bn = self._name + '\0' * (pad_len - len(self._name) % pad_len)
        return bn

    def walk(self):
        # os.listdir will return unicode list if the argument is unicode.
        # TODO: take care of the unicode names
        for ent in os.listdir(u'.'):
            if os.path.isdir(ent):
                cwd = os.getcwd()
                d = Folder(ent)
                # depth-first
                os.chdir(os.path.join(cwd, ent))
                d.walk()
                # restore the cwd
                os.chdir(cwd)
                self._children.append(d)
            else:
                self._children.append(File(ent))

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
        body_fmt = '    {{{type}, "{name}", (rt_uint8_t *){data}, sizeof({data})/sizeof({data}[0])}}'
        body_fmt0= '    {{{type}, "{name}", RT_NULL, 0}}'
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
                body_li.append(body_fmt0.format(type=tp, name = c.name))
            else:
                body_li.append(body_fmt.format(type=tp,
                                            name=c.name,
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

    os.chdir(args.rootdir)

    tree = Folder('romfs_root')
    tree.walk()
    tree.sort()

    if args.dump:
        tree.dump()

    if args.binary:
        data = get_bin_data(tree, int(args.addr, 16))
    else:
        data = get_c_data(tree).encode()

    output = args.output
    if not output:
        output = sys.stdout

    output.write(data)

## The little filesystem technical specification

This is the technical specification of the little filesystem. This document
covers the technical details of how the littlefs is stored on disk for
introspection and tooling development. This document assumes you are
familiar with the design of the littlefs, for more info on how littlefs
works check out [DESIGN.md](DESIGN.md).

```
   | | |     .---._____
  .-----.   |          |
--|o    |---| littlefs |
--|     |---|          |
  '-----'   '----------'
   | | |
```

## Some important details

- The littlefs is a block-based filesystem. This is, the disk is divided into
  an array of evenly sized blocks that are used as the logical unit of storage
  in littlefs. Block pointers are stored in 32 bits.

- There is no explicit free-list stored on disk, the littlefs only knows what
  is in use in the filesystem.

- The littlefs uses the value of 0xffffffff to represent a null block-pointer.

- All values in littlefs are stored in little-endian byte order.

## Directories / Metadata pairs

Metadata pairs form the backbone of the littlefs and provide a system for
atomic updates. Even the superblock is stored in a metadata pair.

As their name suggests, a metadata pair is stored in two blocks, with one block
acting as a redundant backup in case the other is corrupted. These two blocks
could be anywhere in the disk and may not be next to each other, so any
pointers to directory pairs need to be stored as two block pointers.

Here's the layout of metadata blocks on disk:

| offset | size          | description    |
|--------|---------------|----------------|
| 0x00   | 32 bits       | revision count |
| 0x04   | 32 bits       | dir size       |
| 0x08   | 64 bits       | tail pointer   |
| 0x10   | size-16 bytes | dir entries    |
| 0x00+s | 32 bits       | CRC            |

**Revision count** - Incremented every update, only the uncorrupted
metadata-block with the most recent revision count contains the valid metadata.
Comparison between revision counts must use sequence comparison since the
revision counts may overflow.

**Dir size** - Size in bytes of the contents in the current metadata block,
including the metadata-pair metadata. Additionally, the highest bit of the
dir size may be set to indicate that the directory's contents continue on the
next metadata-pair pointed to by the tail pointer.

**Tail pointer** - Pointer to the next metadata-pair in the filesystem.
A null pair-pointer (0xffffffff, 0xffffffff) indicates the end of the list.
If the highest bit in the dir size is set, this points to the next
metadata-pair in the current directory, otherwise it points to an arbitrary
metadata-pair. Starting with the superblock, the tail-pointers form a
linked-list containing all metadata-pairs in the filesystem.

**CRC** - 32 bit CRC used to detect corruption from power-lost, from block
end-of-life, or just from noise on the storage bus. The CRC is appended to
the end of each metadata-block. The littlefs uses the standard CRC-32, which
uses a polynomial of 0x04c11db7, initialized with 0xffffffff.

Here's an example of a simple directory stored on disk:
```
(32 bits) revision count = 10                    (0x0000000a)
(32 bits) dir size       = 154 bytes, end of dir (0x0000009a)
(64 bits) tail pointer   = 37, 36                (0x00000025, 0x00000024)
(32 bits) CRC            = 0xc86e3106

00000000: 0a 00 00 00 9a 00 00 00 25 00 00 00 24 00 00 00  ........%...$...
00000010: 22 08 00 03 05 00 00 00 04 00 00 00 74 65 61 22  "...........tea"
00000020: 08 00 06 07 00 00 00 06 00 00 00 63 6f 66 66 65  ...........coffe
00000030: 65 22 08 00 04 09 00 00 00 08 00 00 00 73 6f 64  e"...........sod
00000040: 61 22 08 00 05 1d 00 00 00 1c 00 00 00 6d 69 6c  a"...........mil
00000050: 6b 31 22 08 00 05 1f 00 00 00 1e 00 00 00 6d 69  k1"...........mi
00000060: 6c 6b 32 22 08 00 05 21 00 00 00 20 00 00 00 6d  lk2"...!... ...m
00000070: 69 6c 6b 33 22 08 00 05 23 00 00 00 22 00 00 00  ilk3"...#..."...
00000080: 6d 69 6c 6b 34 22 08 00 05 25 00 00 00 24 00 00  milk4"...%...$..
00000090: 00 6d 69 6c 6b 35 06 31 6e c8                    .milk5.1n.
```

A note about the tail pointer linked-list: Normally, this linked-list is
threaded through the entire filesystem. However, after power-loss this
linked-list may become out of sync with the rest of the filesystem.
- The linked-list may contain a directory that has actually been removed
- The linked-list may contain a metadata pair that has not been updated after
  a block in the pair has gone bad.

The threaded linked-list must be checked for these errors before it can be
used reliably. Fortunately, the threaded linked-list can simply be ignored
if littlefs is mounted read-only.

## Entries

Each metadata block contains a series of entries that follow a standard
layout. An entry contains the type of the entry, along with a section for
entry-specific data, attributes, and a name.

Here's the layout of entries on disk:

| offset  | size                   | description                |
|---------|------------------------|----------------------------|
| 0x0     | 8 bits                 | entry type                 |
| 0x1     | 8 bits                 | entry length               |
| 0x2     | 8 bits                 | attribute length           |
| 0x3     | 8 bits                 | name length                |
| 0x4     | entry length bytes     | entry-specific data        |
| 0x4+e   | attribute length bytes | system-specific attributes |
| 0x4+e+a | name length bytes      | entry name                 |

**Entry type** - Type of the entry, currently this is limited to the following:
- 0x11 - file entry
- 0x22 - directory entry
- 0x2e - superblock entry

Additionally, the type is broken into two 4 bit nibbles, with the upper nibble
specifying the type's data structure used when scanning the filesystem. The
lower nibble clarifies the type further when multiple entries share the same
data structure.

The highest bit is reserved for marking the entry as "moved". If an entry
is marked as "moved", the entry may also exist somewhere else in the
filesystem. If the entry exists elsewhere, this entry must be treated as
though it does not exist.

**Entry length** - Length in bytes of the entry-specific data. This does
not include the entry type size, attributes, or name. The full size in bytes
of the entry is 4 + entry length + attribute length + name length.

**Attribute length** - Length of system-specific attributes in bytes. Since
attributes are system specific, there is not much guarantee on the values in
this section, and systems are expected to work even when it is empty. See the
[attributes](#entry-attributes) section for more details.

**Name length** - Length of the entry name. Entry names are stored as UTF8,
although most systems will probably only support ASCII. Entry names can not
contain '/' and can not be '.' or '..' as these are a part of the syntax of
filesystem paths.

Here's an example of a simple entry stored on disk:
```
(8 bits)   entry type       = file     (0x11)
(8 bits)   entry length     = 8 bytes  (0x08)
(8 bits)   attribute length = 0 bytes  (0x00)
(8 bits)   name length      = 12 bytes (0x0c)
(8 bytes)  entry data       = 05 00 00 00 20 00 00 00
(12 bytes) entry name       = smallavacado

00000000: 11 08 00 0c 05 00 00 00 20 00 00 00 73 6d 61 6c  ........ ...smal
00000010: 6c 61 76 61 63 61 64 6f                          lavacado
```

## Superblock

The superblock is the anchor for the littlefs. The superblock is stored as
a metadata pair containing a single superblock entry. It is through the
superblock that littlefs can access the rest of the filesystem.

The superblock can always be found in blocks 0 and 1, however fetching the
superblock requires knowing the block size. The block size can be guessed by
searching the beginning of disk for the string "littlefs", although currently
the filesystems relies on the user providing the correct block size.

The superblock is the most valuable block in the filesystem. It is updated
very rarely, only during format or when the root directory must be moved. It
is encouraged to always write out both superblock pairs even though it is not
required.

Here's the layout of the superblock entry:

| offset | size                   | description                            |
|--------|------------------------|----------------------------------------|
| 0x00   | 8 bits                 | entry type (0x2e for superblock entry) |
| 0x01   | 8 bits                 | entry length (20 bytes)                |
| 0x02   | 8 bits                 | attribute length                       |
| 0x03   | 8 bits                 | name length (8 bytes)                  |
| 0x04   | 64 bits                | root directory                         |
| 0x0c   | 32 bits                | block size                             |
| 0x10   | 32 bits                | block count                            |
| 0x14   | 32 bits                | version                                |
| 0x18   | attribute length bytes | system-specific attributes             |
| 0x18+a | 8 bytes                | magic string ("littlefs")              |

**Root directory** - Pointer to the root directory's metadata pair.

**Block size** - Size of the logical block size used by the filesystem.

**Block count** - Number of blocks in the filesystem.

**Version** - The littlefs version encoded as a 32 bit value. The upper 16 bits
encodes the major version, which is incremented when a breaking-change is
introduced in the filesystem specification. The lower 16 bits encodes the
minor version, which is incremented when a backwards-compatible change is
introduced. Non-standard Attribute changes do not change the version. This
specification describes version 1.1 (0x00010001), which is the first version
of littlefs.

**Magic string** - The magic string "littlefs" takes the place of an entry
name.

Here's an example of a complete superblock:
```
(32 bits) revision count   = 3                    (0x00000003)
(32 bits) dir size         = 52 bytes, end of dir (0x00000034)
(64 bits) tail pointer     = 3, 2                 (0x00000003, 0x00000002)
(8 bits)  entry type       = superblock           (0x2e)
(8 bits)  entry length     = 20 bytes             (0x14)
(8 bits)  attribute length = 0 bytes              (0x00)
(8 bits)  name length      = 8 bytes              (0x08)
(64 bits) root directory   = 3, 2                 (0x00000003, 0x00000002)
(32 bits) block size       = 512 bytes            (0x00000200)
(32 bits) block count      = 1024 blocks          (0x00000400)
(32 bits) version          = 1.1                  (0x00010001)
(8 bytes) magic string     = littlefs
(32 bits) CRC              = 0xc50b74fa

00000000: 03 00 00 00 34 00 00 00 03 00 00 00 02 00 00 00  ....4...........
00000010: 2e 14 00 08 03 00 00 00 02 00 00 00 00 02 00 00  ................
00000020: 00 04 00 00 01 00 01 00 6c 69 74 74 6c 65 66 73  ........littlefs
00000030: fa 74 0b c5                                      .t..
```

## Directory entries

Directories are stored in entries with a pointer to the first metadata pair
in the directory. Keep in mind that a directory may be composed of multiple
metadata pairs connected by the tail pointer when the highest bit in the dir
size is set.

Here's the layout of a directory entry:

| offset | size                   | description                             |
|--------|------------------------|-----------------------------------------|
| 0x0    | 8 bits                 | entry type (0x22 for directory entries) |
| 0x1    | 8 bits                 | entry length (8 bytes)                  |
| 0x2    | 8 bits                 | attribute length                        |
| 0x3    | 8 bits                 | name length                             |
| 0x4    | 64 bits                | directory pointer                       |
| 0xc    | attribute length bytes | system-specific attributes              |
| 0xc+a  | name length bytes      | directory name                          |

**Directory pointer** - Pointer to the first metadata pair in the directory.

Here's an example of a directory entry:
```
(8 bits)  entry type        = directory (0x22)
(8 bits)  entry length      = 8 bytes   (0x08)
(8 bits)  attribute length  = 0 bytes   (0x00)
(8 bits)  name length       = 3 bytes   (0x03)
(64 bits) directory pointer = 5, 4      (0x00000005, 0x00000004)
(3 bytes) name              = tea

00000000: 22 08 00 03 05 00 00 00 04 00 00 00 74 65 61     "...........tea
```

## File entries

Files are stored in entries with a pointer to the head of the file and the
size of the file. This is enough information to determine the state of the
CTZ skip-list that is being referenced.

How files are actually stored on disk is a bit complicated. The full
explanation of CTZ skip-lists can be found in [DESIGN.md](DESIGN.md#ctz-skip-lists).

A terribly quick summary: For every nth block where n is divisible by 2^x,
the block contains a pointer to block n-2^x. These pointers are stored in
increasing order of x in each block of the file preceding the data in the
block.

The maximum number of pointers in a block is bounded by the maximum file size
divided by the block size. With 32 bits for file size, this results in a
minimum block size of 104 bytes.

Here's the layout of a file entry:

| offset | size                   | description                        |
|--------|------------------------|------------------------------------|
| 0x0    | 8 bits                 | entry type (0x11 for file entries) |
| 0x1    | 8 bits                 | entry length (8 bytes)             |
| 0x2    | 8 bits                 | attribute length                   |
| 0x3    | 8 bits                 | name length                        |
| 0x4    | 32 bits                | file head                          |
| 0x8    | 32 bits                | file size                          |
| 0xc    | attribute length bytes | system-specific attributes         |
| 0xc+a  | name length bytes      | directory name                     |

**File head** - Pointer to the block that is the head of the file's CTZ
skip-list.

**File size** - Size of file in bytes.

Here's an example of a file entry:
```
(8 bits)   entry type       = file     (0x11)
(8 bits)   entry length     = 8 bytes  (0x08)
(8 bits)   attribute length = 0 bytes  (0x00)
(8 bits)   name length      = 12 bytes (0x03)
(32 bits)  file head        = 543      (0x0000021f)
(32 bits)  file size        = 256 KB   (0x00040000)
(12 bytes) name             = largeavacado

00000000: 11 08 00 0c 1f 02 00 00 00 00 04 00 6c 61 72 67  ............larg
00000010: 65 61 76 61 63 61 64 6f                          eavacado
```

## Entry attributes

Each dir entry can have up to 256 bytes of system-specific attributes. Since
these attributes are system-specific, they may not be portable between
different systems. For this reason, all attributes must be optional. A minimal
littlefs driver must be able to get away with supporting no attributes at all.

For some level of portability, littlefs has a simple scheme for attributes.
Each attribute is prefixes with an 8-bit type that indicates what the attribute
is. The length of attributes may also be determined from this type. Attributes
in an entry should be sorted based on portability, since attribute parsing
will end when it hits the first attribute it does not understand.

Each system should choose a 4-bit value to prefix all attribute types with to
avoid conflicts with other systems. Additionally, littlefs drivers that support
attributes should provide a "ignore attributes" flag to users in case attribute
conflicts do occur.

Attribute types prefixes with 0x0 and 0xf are currently reserved for future
standard attributes. Standard attributes will be added to this document in
that case.

Here's an example of non-standard time attribute:
```
(8 bits)  attribute type  = time       (0xc1)
(72 bits) time in seconds = 1506286115 (0x0059c81a23)

00000000: c1 23 1a c8 59 00                                .#..Y.
```

Here's an example of non-standard permissions attribute:
```
(8 bits)  attribute type  = permissions (0xc2)
(16 bits) permission bits = rw-rw-r--   (0x01b4)

00000000: c2 b4 01                                         ...
```

Here's what a dir entry may look like with these attributes:
```
(8 bits)   entry type       = file         (0x11)
(8 bits)   entry length     = 8 bytes      (0x08)
(8 bits)   attribute length = 9 bytes      (0x09)
(8 bits)   name length      = 12 bytes     (0x0c)
(8 bytes)  entry data       = 05 00 00 00 20 00 00 00
(8 bits)   attribute type   = time         (0xc1)
(72 bits)  time in seconds  = 1506286115   (0x0059c81a23)
(8 bits)   attribute type   = permissions  (0xc2)
(16 bits)  permission bits  = rw-rw-r--    (0x01b4)
(12 bytes) entry name       = smallavacado

00000000: 11 08 09 0c 05 00 00 00 20 00 00 00 c1 23 1a c8  ........ ....#..
00000010: 59 00 c2 b4 01 73 6d 61 6c 6c 61 76 61 63 61 64  Y....smallavacad
00000020: 6f                                               o
```

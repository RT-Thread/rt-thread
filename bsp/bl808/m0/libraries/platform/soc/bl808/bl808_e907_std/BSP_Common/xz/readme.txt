when use linux xz command to create .xz file for embedded device to decompress, memory must be taken into
consideration.
to control memory used, following opt should be considerated:
(https://www.freebsd.org/cgi/man.cgi?query=xz&sektion=1)

--memlimit-compress=limit

--memlimit-decompress=limit

--lzma2[=options]
          Add  LZMA1  or  LZMA2 filter to the filter chain.     These filters
          can be used only as the last filter in the chain.

          LZMA1 is a legacy    filter,    which is supported almost  solely  due
          to  the  legacy  .lzma  file  format, which supports only    LZMA1.
          LZMA2 is an updated version  of  LZMA1  to  fix  some  practical
          issues  of LZMA1.     The .xz format    uses LZMA2 and doesn't support
          LZMA1 at all.  Compression speed and ratios of LZMA1  and     LZMA2
          are practically the same.

          LZMA1 and    LZMA2 share the    same set of options:

          preset=preset
             Reset  all    LZMA1 or LZMA2 options to preset.  Preset con-
             sist of an    integer, which may be followed by  single-let-
             ter  preset  modifiers.   The integer can be from 0 to 9,
             matching the command line options -0 ...  -9.   The  only
             supported     modifier   is     currently  e,    which  matches
             --extreme.     If no preset is specified, the    default    values
             of    LZMA1 or LZMA2 options are taken from the preset 6.

          dict=size

--info-memory
        Display,    in  human-readable  format,  how  much physical	memory
        (RAM) xz thinks the system has and the memory usage  limits  for
        compression and decompression, and exit successfully.
        
xz --keep --check=crc32 --memlimit-decompress=32KiB   --lzma2=dict=32KiB toxz.bin
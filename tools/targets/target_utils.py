"""
Common serialization helpers for the tools/targets project generators.

The project generators (CMake / Makefile / xmake / Zig / SES / Eclipse / VS /
Keil / IAR) each take the same SCons build data (CPPDEFINES, CPPPATH, source
files, LIBS, LIBPATH, C/ASM/link flags) and serialize it into a different
project-file syntax. Historically every generator re-implemented that
serialization inline, which produced a family of related bugs:

  * tuple/list CPPDEFINES such as ('FOO', '1') rendered as two macros
    ("FOO;1") or crashed on ``str.join`` / ``set()``;
  * ``set(...)`` was used for ordering, giving non-deterministic output;
  * include/source paths containing spaces, ';' or quotes broke the target
    file's list syntax;
  * linker-script flags (``-T link.lds``) were parsed with ``str.split`` and
    fell apart on quoted paths or the ``-Wl,-T,x`` form.

These helpers centralize that logic so every generator normalizes and escapes
its output the same, correct way.
"""

import os
import shlex
import xml.sax.saxutils as saxutils


# ---------------------------------------------------------------------------
# ordering / de-duplication
# ---------------------------------------------------------------------------

def ordered_unique(items):
    """Return items with duplicates removed, preserving first-seen order.

    Generators must never use ``set()`` for this: it reorders the output and
    makes generated project files churn between runs.
    """
    result = []
    seen = set()
    for item in items or []:
        try:
            key = item
            hash(key)
        except TypeError:
            key = repr(item)
        if key in seen:
            continue
        seen.add(key)
        result.append(item)
    return result


# ---------------------------------------------------------------------------
# preprocessor defines
# ---------------------------------------------------------------------------

def normalize_define(item):
    """Normalize a single SCons CPPDEFINES entry to a ``NAME`` / ``NAME=value`` string.

      "FOO"              -> "FOO"
      ("FOO", "1")       -> "FOO=1"
      ["FOO", "1"]       -> "FOO=1"
      ("FOO", None)      -> "FOO"
      "FOO=bar"          -> "FOO=bar"
      'FOO="a b"'        -> 'FOO="a b"'

    Returns None for entries that carry no macro name (so callers can filter).
    """
    if item is None:
        return None

    if isinstance(item, (tuple, list)):
        parts = list(item)
        if len(parts) == 0:
            return None
        name = parts[0]
        if name is None:
            return None
        if len(parts) == 1 or parts[1] is None:
            return str(name)
        return "{}={}".format(name, parts[1])

    return str(item)


def normalize_defines(defines):
    """Normalize a list of CPPDEFINES entries, filtering empties and de-duplicating.

    Order is preserved (see :func:`ordered_unique`); the tuple form is folded
    into ``NAME=value`` so no generator ever emits ``FOO`` and ``1`` as two
    separate macros.
    """
    normalized = []
    for item in defines or []:
        value = normalize_define(item)
        if value is None or value == "":
            continue
        normalized.append(value)
    return ordered_unique(normalized)


# ---------------------------------------------------------------------------
# paths
# ---------------------------------------------------------------------------

def normalize_path(path, force_posix=True):
    """Normalize a filesystem path for inclusion in a project file.

    Applies ``os.path.normpath`` and, by default, converts backslashes to
    forward slashes so generated files are stable across platforms.
    """
    text = os.path.normpath(str(path))
    if force_posix:
        text = text.replace('\\', '/')
    return text


def normalize_paths(paths, force_posix=True):
    """Normalize and de-duplicate a list of paths, preserving order."""
    return ordered_unique([normalize_path(p, force_posix) for p in paths or []])


# ---------------------------------------------------------------------------
# CMake
# ---------------------------------------------------------------------------

def cmake_quote(value):
    """Escape a value for a CMake double-quoted string / list element.

    Handles backslash, double quote and the semicolon that CMake would
    otherwise treat as a list separator.
    """
    text = str(value)
    text = text.replace('\\', '\\\\')
    text = text.replace('"', '\\"')
    text = text.replace(';', '\\;')
    return text


def cmake_list(values, indent='\t'):
    """Format values as one indented, quote-safe CMake list element per line."""
    return "\n".join("{}{}".format(indent, cmake_quote(v)) for v in values)


# ---------------------------------------------------------------------------
# Makefile
# ---------------------------------------------------------------------------

def make_quote(value):
    """Escape a value for use in a Makefile assignment.

    Escapes the characters that carry meaning to make/the shell (space, ``#``
    comment, backslash) while deliberately preserving ``$(VAR)`` / ``${VAR}``
    make-variable references, which the generators intentionally embed in
    paths. A bare ``$`` that is not part of a make variable is escaped to
    ``$$`` so it survives expansion.
    """
    text = str(value)
    text = text.replace('#', '\\#')

    out = []
    i = 0
    length = len(text)
    while i < length:
        ch = text[i]
        if ch == '$':
            nxt = text[i + 1] if i + 1 < length else ''
            if nxt in ('(', '{'):
                # keep a make variable reference such as $(BSP_ROOT) intact
                out.append(ch)
            else:
                out.append('$$')
        elif ch == ' ':
            out.append('\\ ')
        else:
            out.append(ch)
        i += 1
    return ''.join(out)


def make_join(values, sep=' '):
    """Quote each value for make and join them with sep."""
    return sep.join(make_quote(v) for v in values)


# ---------------------------------------------------------------------------
# Lua (xmake)
# ---------------------------------------------------------------------------

def lua_quote(value):
    """Return a Lua double-quoted string literal for value."""
    text = str(value)
    text = text.replace('\\', '\\\\')
    text = text.replace('"', '\\"')
    text = text.replace('\n', '\\n')
    return '"{}"'.format(text)


def lua_list(values, indent='\t'):
    """Format values as a comma-separated list of Lua string literals.

    One quoted item per line, no trailing comma (matches the xmake.lua
    template's ``add_xxx( ... )`` block layout).
    """
    return ",\n".join("{}{}".format(indent, lua_quote(v)) for v in values)


# ---------------------------------------------------------------------------
# Zig
# ---------------------------------------------------------------------------

def zig_quote(value):
    """Return a Zig double-quoted string literal for value."""
    text = str(value)
    text = text.replace('\\', '\\\\')
    text = text.replace('"', '\\"')
    text = text.replace('\n', '\\n')
    return '"{}"'.format(text)


def zig_list(values, indent='\t'):
    """Format values as Zig array elements, one quoted item per line.

    A trailing comma is emitted on every line, which Zig array literals allow.
    """
    return "".join("{}{},\n".format(indent, zig_quote(v)) for v in values)


# ---------------------------------------------------------------------------
# XML (VS / Keil / IAR / Eclipse / SES)
# ---------------------------------------------------------------------------

def xml_attr(value):
    """Escape a value for safe inclusion as an XML attribute value.

    Escapes ``&``, ``<``, ``>`` plus the ``"`` and ``'`` quote characters, so
    the result is safe both as attribute content and as element text. Use this
    only when building XML text by hand (e.g. string templates); when assigning
    through ElementTree's ``set()``/``.text`` the library escapes for you.
    """
    return saxutils.escape(str(value), {'"': '&quot;', "'": '&apos;'})


def xml_path_attr(path, sep='/'):
    """Normalize a path's separators, then escape it for an XML attribute.

    Combines :func:`normalize_path` (stable, single separator style) with
    :func:`xml_attr` so a path holding ``&``/``<``/quotes cannot break the
    generated XML when written into a hand-built attribute string.
    """
    return xml_attr(normalize_path(path, force_posix=(sep == '/')))


def normalize_group_file_path(project_path, file_path, filename=None, sep='/'):
    """Build a stable, relative file path for a file-group emitter.

    Keil / IAR / VS / VS2012 all turn a source file into a project-relative
    path that becomes an XML attribute. Historically they called
    ``_make_path_relative`` (which returns '/') and then ``os.path.join`` the
    file name (which re-introduces '\\' on Windows), yielding mixed, OS-dependent
    separators in the serialized file. This centralizes that: make the path
    relative to ``project_path``, optionally append ``filename``, and normalize
    to a single separator so the output is deterministic. ``sep`` selects '/'
    (VS / Keil) or '\\' (IAR's ``$PROJ_DIR$\\`` convention).

    Note: the returned value is the raw path -- callers that hand it to
    ElementTree let the library escape it; callers building XML by hand should
    wrap it with :func:`xml_attr`.
    """
    from utils import _make_path_relative

    rel = _make_path_relative(project_path, file_path)
    if filename is not None:
        rel = os.path.join(rel, filename)
    rel = os.path.normpath(rel)
    if sep == '/':
        rel = rel.replace('\\', '/')
    else:
        rel = rel.replace('/', '\\')
    return rel


def xml_list_value(values, sep=';'):
    """Join values into a single delimited string for an XML node.

    The result is meant to be handed to ElementTree (``.set()`` / ``.text``),
    which performs XML escaping itself, so this only concatenates -- it does
    not pre-escape (that would double-escape ``&`` into ``&amp;amp;``). Order
    is preserved and duplicate values removed.
    """
    return sep.join(str(v) for v in ordered_unique(list(values)))


def semicolon_list(values):
    """Join values with ';', order-preserving de-dup -- for IDE list fields."""
    return xml_list_value(values, ';')


# ---------------------------------------------------------------------------
# compiler command / flag parsing
# ---------------------------------------------------------------------------

def shlex_split_flags(text):
    """Split a flag/command string into tokens, robust on Windows paths.

    Tuned so backslash path separators are kept verbatim and quotes around
    ``"dir with space"`` are honored and stripped.
    """
    if text is None:
        return []
    lex = shlex.shlex(str(text), posix=True)
    lex.whitespace_split = True
    lex.escape = ''
    lex.commenters = ''
    return list(lex)


def split_command(command):
    """Split a compile_commands.json ``command`` into argv tokens.

    ``arguments`` lists are already tokenized and returned as-is; string
    commands are tokenized with :func:`shlex_split_flags`.
    """
    if command is None:
        return []
    if isinstance(command, (list, tuple)):
        return list(command)
    return shlex_split_flags(command)


def extract_include_args(parts):
    """Extract include directories from tokenized compiler arguments.

    Supports ``-Ifoo``, ``-I foo``, ``/Ifoo`` and ``/I foo`` without running
    past the end of the token list.
    """
    includes = []
    i = 0
    length = len(parts)
    while i < length:
        part = parts[i]
        if part in ('-I', '/I'):
            if i + 1 < length:
                includes.append(parts[i + 1])
                i += 2
                continue
        elif part.startswith('-I') or part.startswith('/I'):
            includes.append(part[2:])
        i += 1
    return includes


def escape_quoted_flags(flags):
    """Normalize a raw flags string for embedding inside a ``"..."`` literal.

    CMake, Lua (xmake) and Zig all write compiler flags as a single
    double-quoted string (e.g. ``SET(CMAKE_C_FLAGS "<flags>")``). Two things
    can break that literal: a backslash path separator and an embedded double
    quote. This converts backslashes to ``/`` (accepted by every compiler we
    target) and escapes embedded quotes, so the flags cannot terminate the
    string early. Centralizes a pattern that was duplicated across the
    generators.
    """
    text = str(flags)
    text = text.replace('\\', '/')
    text = text.replace('"', '\\"')
    return text


def normalize_flags(flags):
    """Return a stable, de-duplicated token list from a flags string or list.

    Accepts either a raw flags string or an already-split sequence; splitting
    honors quoted paths. Order is preserved and duplicate tokens removed.
    """
    if flags is None:
        return []
    if isinstance(flags, (list, tuple)):
        tokens = []
        for item in flags:
            tokens.extend(shlex_split_flags(item))
    else:
        tokens = shlex_split_flags(flags)
    return ordered_unique(tokens)


def normalize_link_script_flags(flags):
    """Extract linker-script paths from link flags.

    Handles the real forms seen in ``LINKFLAGS``:
      ``-Tlink.lds``            (attached)
      ``-T link.lds``           (separate token)
      ``-T "dir with space/x"`` (quoted path, kept whole by the tokenizer)
      ``-Wl,-T,link.lds``       (passed through the compiler to the linker)
      ``-Wl,-T link.lds``       (compiler ``-Wl,-T`` then the path token)

    Returns the script paths in first-seen order.
    """
    tokens = flags if isinstance(flags, (list, tuple)) else shlex_split_flags(flags)
    tokens = list(tokens)

    scripts = []
    i = 0
    length = len(tokens)
    while i < length:
        tok = tokens[i]
        if tok == '-T':
            if i + 1 < length:
                scripts.append(tokens[i + 1])
                i += 2
                continue
        elif tok.startswith('-T') and tok != '-T':
            scripts.append(tok[2:])
        elif tok.startswith('-Wl,'):
            # e.g. -Wl,-T,link.lds  or  -Wl,-T
            wl_parts = tok.split(',')[1:]
            j = 0
            while j < len(wl_parts):
                p = wl_parts[j]
                if p == '-T':
                    if j + 1 < len(wl_parts):
                        scripts.append(wl_parts[j + 1])
                        j += 2
                        continue
                    # path is the following top-level token
                    elif i + 1 < length:
                        scripts.append(tokens[i + 1])
                        i += 1
                elif p.startswith('-T') and p != '-T':
                    scripts.append(p[2:])
                j += 1
        i += 1
    return ordered_unique([s for s in scripts if s])

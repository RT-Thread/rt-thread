import io
import os

import setuptools


setuptools.setup(
    name="kconfiglib",
    # MAJOR.MINOR.PATCH, per http://semver.org
    version="14.1.0",
    description="A flexible Python Kconfig implementation",

    # Make sure that README.rst decodes on Python 3 in environments that use
    # the C locale (which implies ASCII), by explicitly giving the encoding.
    #
    # io.open() has the 'encoding' parameter on both Python 2 and 3. open()
    # doesn't have it on Python 2. This lets us use the same code for both.
    long_description=io.open(
        os.path.join(os.path.dirname(__file__), "README.rst"),
        encoding="utf-8"
    ).read(),

    url="https://github.com/ulfalizer/Kconfiglib",
    author='Ulf "Ulfalizer" Magnusson',
    author_email="ulfalizer@gmail.com",
    keywords="kconfig, kbuild, menuconfig, configuration-management",
    license="ISC",

    py_modules=(
        "kconfiglib",
        "menuconfig",
        "guiconfig",
        "genconfig",
        "oldconfig",
        "olddefconfig",
        "savedefconfig",
        "defconfig",
        "alldefconfig",
        "allnoconfig",
        "allmodconfig",
        "allyesconfig",
        "listnewconfig",
        "setconfig",
    ),

    entry_points={
        "console_scripts": (
            "menuconfig = menuconfig:_main",
            "guiconfig = guiconfig:_main",
            "genconfig = genconfig:main",
            "oldconfig = oldconfig:_main",
            "olddefconfig = olddefconfig:main",
            "savedefconfig = savedefconfig:main",
            "defconfig = defconfig:main",
            "alldefconfig = alldefconfig:main",
            "allnoconfig = allnoconfig:main",
            "allmodconfig = allmodconfig:main",
            "allyesconfig = allyesconfig:main",
            "listnewconfig = listnewconfig:main",
            "setconfig = setconfig:main",
        )
    },

    # Note: windows-curses is not automatically installed on Windows anymore,
    # because it made Kconfiglib impossible to install on MSYS2 with pip

    # Needs support for unnumbered {} in format() and argparse
    python_requires=">=2.7,!=3.0.*,!=3.1.*",

    project_urls={
        "GitHub repository": "https://github.com/ulfalizer/Kconfiglib",
        "Examples": "https://github.com/ulfalizer/Kconfiglib/tree/master/examples",
    },

    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "Topic :: Software Development :: Build Tools",
        "Topic :: System :: Operating System Kernels :: Linux",
        "License :: OSI Approved :: ISC License (ISCL)",
        "Operating System :: POSIX",
        "Operating System :: Microsoft :: Windows",
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.2",
        "Programming Language :: Python :: 3.3",
        "Programming Language :: Python :: 3.4",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: Implementation :: CPython",
        "Programming Language :: Python :: Implementation :: PyPy",
    ]
)

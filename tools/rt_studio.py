import os
import re
from string import Template

import rtconfig
import shutil
import time

# version
MODULE_VER_NUM = 1

cproject_temp = """<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<?fileVersion 4.0.0?><cproject storage_type_id="org.eclipse.cdt.core.XmlProjectDescriptionStorage">
    <storageModule moduleId="org.eclipse.cdt.core.settings">
        <cconfiguration id="ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.553091094">
            <storageModule buildSystemId="org.eclipse.cdt.managedbuilder.core.configurationDataProvider" id="ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.553091094" moduleId="org.eclipse.cdt.core.settings" name="Debug">
                <externalSettings/>
                <extensions>
                    <extension id="org.eclipse.cdt.core.ELF" point="org.eclipse.cdt.core.BinaryParser"/>
                    <extension id="org.eclipse.cdt.core.GASErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
                    <extension id="org.eclipse.cdt.core.GmakeErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
                    <extension id="org.eclipse.cdt.core.GLDErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
                    <extension id="org.eclipse.cdt.core.CWDLocator" point="org.eclipse.cdt.core.ErrorParser"/>
                    <extension id="org.eclipse.cdt.core.GCCErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
                </extensions>
            </storageModule>
            <storageModule moduleId="cdtBuildSystem" version="4.0.0">
                <configuration artifactName="rtthread" buildArtefactType="org.eclipse.cdt.build.core.buildArtefactType.exe" buildProperties="org.eclipse.cdt.build.core.buildArtefactType=org.eclipse.cdt.build.core.buildArtefactType.exe,org.eclipse.cdt.build.core.buildType=org.eclipse.cdt.build.core.buildType.debug" cleanCommand="${cross_rm} -rf" description="" id="ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.553091094" name="Debug" parent="ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug">
                    <folderInfo id="ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.553091094." name="/" resourcePath="">
                        <toolChain id="ilg.gnuarmeclipse.managedbuild.cross.toolchain.elf.debug.1201710416" name="ARM Cross GCC" superClass="ilg.gnuarmeclipse.managedbuild.cross.toolchain.elf.debug">
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.addtools.createflash.251260409" name="Create flash image" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.addtools.createflash" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.addtools.createlisting.1365878149" name="Create extended listing" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.addtools.createlisting" useByScannerDiscovery="false"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.addtools.printsize.709136944" name="Print size" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.addtools.printsize" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.level.1986446770" name="Optimization Level" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.level" useByScannerDiscovery="true" value="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.level.none" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.messagelength.1312975261" name="Message length (-fmessage-length=0)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.messagelength" useByScannerDiscovery="true" value="false" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.signedchar.1538128212" name="'char' is signed (-fsigned-char)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.signedchar" useByScannerDiscovery="true" value="false" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.functionsections.2136804218" name="Function sections (-ffunction-sections)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.functionsections" useByScannerDiscovery="true" value="true" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.datasections.244767666" name="Data sections (-fdata-sections)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.optimization.datasections" useByScannerDiscovery="true" value="true" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.debugging.level.1055848773" name="Debug level" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.debugging.level" useByScannerDiscovery="true" value="ilg.gnuarmeclipse.managedbuild.cross.option.debugging.level.default" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.debugging.format.501941135" name="Debug format" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.debugging.format" useByScannerDiscovery="true" value="ilg.gnuarmeclipse.managedbuild.cross.option.debugging.format.dwarf2" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.toolchain.name.1696308067" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.toolchain.name" useByScannerDiscovery="false" value="GNU Tools for ARM Embedded Processors" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.architecture.1558403188" name="Architecture" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.architecture" useByScannerDiscovery="false" value="ilg.gnuarmeclipse.managedbuild.cross.option.architecture.arm" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.family.749415257" name="ARM family" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.family" useByScannerDiscovery="false" value="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.mcpu.cortex-m4" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.instructionset.2114153533" name="Instruction set" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.instructionset" useByScannerDiscovery="false" value="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.instructionset.thumb" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.prefix.1600865811" name="Prefix" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.prefix" useByScannerDiscovery="false" value="arm-none-eabi-" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.c.1109963929" name="C compiler" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.c" useByScannerDiscovery="false" value="gcc" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.cpp.1040883831" name="C++ compiler" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.cpp" useByScannerDiscovery="false" value="g++" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.ar.1678200391" name="Archiver" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.ar" useByScannerDiscovery="false" value="ar" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.objcopy.1171840296" name="Hex/Bin converter" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.objcopy" useByScannerDiscovery="false" value="objcopy" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.objdump.342604837" name="Listing generator" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.objdump" useByScannerDiscovery="false" value="objdump" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.size.898269225" name="Size command" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.size" useByScannerDiscovery="false" value="size" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.make.2016398076" name="Build command" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.make" useByScannerDiscovery="false" value="make" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.command.rm.1606171496" name="Remove command" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.command.rm" useByScannerDiscovery="false" value="rm" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.toolchain.id.540792084" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.toolchain.id" useByScannerDiscovery="false" value="1287942917" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.architecture.430121817" name="Architecture" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.architecture" useByScannerDiscovery="false" value="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.arch.none" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.fpu.abi.966735324" name="Float ABI" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.fpu.abi" useByScannerDiscovery="true" value="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.fpu.abi.hard" valueType="enumerated"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.warnings.allwarn.1381561249" name="Enable all common warnings (-Wall)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.warnings.allwarn" useByScannerDiscovery="true" value="true" valueType="boolean"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.target.other.2041717463" name="Other target flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.target.other" useByScannerDiscovery="true" value="" valueType="string"/>
                            <option id="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.fpu.unit.1463655269" name="FPU Type" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.fpu.unit" useByScannerDiscovery="true" value="ilg.gnuarmeclipse.managedbuild.cross.option.arm.target.fpu.unit.fpv4spd16" valueType="enumerated"/>
                            <targetPlatform archList="all" binaryParser="org.eclipse.cdt.core.ELF" id="ilg.gnuarmeclipse.managedbuild.cross.targetPlatform.1798638225" isAbstract="false" osList="all" superClass="ilg.gnuarmeclipse.managedbuild.cross.targetPlatform"/>
                            <builder buildPath="${workspace_loc:/${ProjName}/Debug" cleanBuildTarget="clean2" id="ilg.gnuarmeclipse.managedbuild.cross.builder.1736709688" keepEnvironmentInBuildfile="false" managedBuildOn="true" name="Gnu Make Builder" parallelBuildOn="true" parallelizationNumber="optimal" superClass="ilg.gnuarmeclipse.managedbuild.cross.builder"/>
                            <tool commandLinePattern="${COMMAND} ${cross_toolchain_flags} ${FLAGS} -c ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}" id="ilg.gnuarmeclipse.managedbuild.cross.tool.assembler.1810966071" name="GNU ARM Cross Assembler" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.assembler">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.usepreprocessor.1072524326" name="Use preprocessor" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.usepreprocessor" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.include.paths.161242639" name="Include paths (-I)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.include.paths" useByScannerDiscovery="true"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.defs.1521934876" name="Defined symbols (-D)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.defs" useByScannerDiscovery="true"/>
                                <option IS_BUILTIN_EMPTY="false" IS_VALUE_EMPTY="false" id="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.flags.1325367962" name="Assembler flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.flags" useByScannerDiscovery="false" valueType="stringList">
                                    <listOptionValue builtIn="false" value="-mimplicit-it=thumb"/>
                                </option>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.other.647856572" name="Other assembler flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.assembler.other" useByScannerDiscovery="false" value="a_misc_flag" valueType="string"/>
                                <inputType id="ilg.gnuarmeclipse.managedbuild.cross.tool.assembler.input.1843333483" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.assembler.input"/>
                            </tool>
                            <tool commandLinePattern="${COMMAND} ${cross_toolchain_flags} ${FLAGS} -c ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}" id="ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.1570350559" name="GNU ARM Cross C Compiler" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.include.paths.634882052" name="Include paths (-I)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.include.paths" useByScannerDiscovery="true"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.defs.100549972" name="Defined symbols (-D)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.defs" useByScannerDiscovery="true"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.other.2133065240" name="Other compiler flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.other" useByScannerDiscovery="true" value="c_misc_flag" valueType="string"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.include.files.714348818" name="Include files (-include)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.include.files" useByScannerDiscovery="true"/>
                                <inputType id="ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.input.992053063" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.input"/>
                            </tool>
                            <tool commandLinePattern="${COMMAND} ${cross_toolchain_flags} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}" id="ilg.gnuarmeclipse.managedbuild.cross.tool.c.linker.869072473" name="Cross ARM C Linker" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.c.linker">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.gcsections.1167322178" name="Remove unused sections (-Xlinker --gc-sections)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.gcsections" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.nostart.351692886" name="Do not use standard start files (-nostartfiles)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.nostart" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.nostdlibs.1009243715" name="No startup or default libs (-nostdlib)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.nostdlibs" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.nodeflibs.2016026082" name="Do not use default libraries (-nodefaultlibs)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.nodeflibs" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.usenewlibnano.923990336" name="Use newlib-nano (--specs=nano.specs)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.usenewlibnano" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option defaultValue="true" id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.shared.548869459" name="Shared (-shared)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.shared" useByScannerDiscovery="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.scriptfile.1818777301" name="Script files (-T)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.scriptfile" useByScannerDiscovery="false"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.libs.1135656995" name="Libraries (-l)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.libs" useByScannerDiscovery="false"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.paths.36884122" name="Library search path (-L)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.paths" useByScannerDiscovery="false"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.other.396049466" name="Other linker flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.other" useByScannerDiscovery="false" value="c_link_misc_flag" valueType="string"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.cref.1645737861" name="Cross reference (-Xlinker --cref)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.c.linker.cref" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                                <inputType id="ilg.gnuarmeclipse.managedbuild.cross.tool.c.linker.input.334732222" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.c.linker.input">
                                    <additionalInput kind="additionalinputdependency" paths="$(USER_OBJS)"/>
                                    <additionalInput kind="additionalinput" paths="$(LIBS)"/>
                                </inputType>
                            </tool>
                            <tool commandLinePattern="${COMMAND} ${cross_toolchain_flags} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}" id="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.linker.1601059928" name="GNU ARM Cross C++ Linker" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.linker">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.gcsections.437759352" name="Remove unused sections (-Xlinker --gc-sections)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.gcsections" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.scriptfile.1101974459" name="Script files (-T)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.scriptfile" useByScannerDiscovery="false"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.cref.2007675975" name="Cross reference (-Xlinker --cref)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.cref" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.usenewlibnano.2105838438" name="Use newlib-nano (--specs=nano.specs)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.usenewlibnano" useByScannerDiscovery="false" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.libs.934137837" name="Libraries (-l)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.libs" useByScannerDiscovery="false"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.nostart.2118356996" name="Do not use standard start files (-nostartfiles)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.nostart" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.nodeflibs.1427884346" name="Do not use default libraries (-nodefaultlibs)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.nodeflibs" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.nostdlibs.1433863653" name="No startup or default libs (-nostdlib)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.nostdlibs" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.printgcsections.1387745410" name="Print removed sections (-Xlinker --print-gc-sections)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.printgcsections" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.strip.1230158061" name="Omit all symbol information (-s)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.strip" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.printmap.1307581821" name="Print link map (-Xlinker --print-map)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.printmap" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.useprintffloat.960778920" name="Use float with nano printf (-u _printf_float)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.useprintffloat" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.usescanffloat.637205035" name="Use float with nano scanf (-u _scanf_float)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.usescanffloat" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.usenewlibnosys.1948314201" name="Do not use syscalls (--specs=nosys.specs)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.usenewlibnosys" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.verbose.273162112" name="Verbose (-v)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.verbose" useByScannerDiscovery="false" value="false" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.paths.1399535143" name="Library search path (-L)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.paths" useByScannerDiscovery="false"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.other.882307902" name="Other linker flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.other" useByScannerDiscovery="false" value="cpp_link_misc_flag" valueType="string"/>
                                <inputType id="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.linker.input.262373798" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.linker.input">
                                    <additionalInput kind="additionalinputdependency" paths="$(USER_OBJS)"/>
                                    <additionalInput kind="additionalinput" paths="$(LIBS)"/>
                                </inputType>
                            </tool>
                            <tool id="ilg.gnuarmeclipse.managedbuild.cross.tool.archiver.506412204" name="GNU ARM Cross Archiver" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.archiver"/>
                            <tool id="ilg.gnuarmeclipse.managedbuild.cross.tool.createflash.1461589245" name="GNU ARM Cross Create Flash Image" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.createflash">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.createflash.choice.1937707052" name="Output file format (-O)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.createflash.choice" useByScannerDiscovery="false" value="ilg.gnuarmeclipse.managedbuild.cross.option.createflash.choice.binary" valueType="enumerated"/>
                            </tool>
                            <tool id="ilg.gnuarmeclipse.managedbuild.cross.tool.createlisting.82359725" name="GNU ARM Cross Create Listing" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.createlisting">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.source.601724476" name="Display source (--source|-S)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.source" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.allheaders.692505279" name="Display all headers (--all-headers|-x)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.allheaders" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.demangle.97345172" name="Demangle names (--demangle|-C)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.demangle" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.linenumbers.1342893377" name="Display line numbers (--line-numbers|-l)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.linenumbers" value="true" valueType="boolean"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.wide.1533725981" name="Wide lines (--wide|-w)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.createlisting.wide" value="true" valueType="boolean"/>
                            </tool>
                            <tool id="ilg.gnuarmeclipse.managedbuild.cross.tool.printsize.1073550295" name="GNU ARM Cross Print Size" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.printsize">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.printsize.format.946451386" name="Size format" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.printsize.format" useByScannerDiscovery="false"/>
                            </tool>
                            <tool commandLinePattern="${COMMAND} ${cross_toolchain_flags} ${FLAGS} -c ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}" id="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.compiler.1302177015" name="GNU ARM Cross C++ Compiler" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.compiler">
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.defs.704468062" name="Defined symbols (-D)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.defs" useByScannerDiscovery="true"/>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.include.paths.302877723" name="Include paths (-I)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.include.paths" useByScannerDiscovery="true"/>
                                <option IS_BUILTIN_EMPTY="false" IS_VALUE_EMPTY="false" id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.include.files.343249373" name="Include files (-include)" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.include.files" useByScannerDiscovery="true" valueType="includeFiles">
                                    <listOptionValue builtIn="false" value="&quot;${workspace_loc:/${ProjName}/rtconfig_preinc.h}&quot;"/>
                                </option>
                                <option id="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.other.465079095" name="Other compiler flags" superClass="ilg.gnuarmeclipse.managedbuild.cross.option.cpp.compiler.other" useByScannerDiscovery="true" value="cpp_misc_flag" valueType="string"/>
                                <inputType id="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.compiler.input.45918001" superClass="ilg.gnuarmeclipse.managedbuild.cross.tool.cpp.compiler.input"/>
                            </tool>
                        </toolChain>
                    </folderInfo>
                    <sourceEntries>
                        <entry excluding="|" flags="VALUE_WORKSPACE_PATH|RESOLVED" kind="sourcePath" name=""/>
                    </sourceEntries>
                </configuration>
            </storageModule>
            <storageModule moduleId="org.eclipse.cdt.core.externalSettings"/>
        </cconfiguration>
    </storageModule>
    <storageModule moduleId="cdtBuildSystem" version="4.0.0">
        <project id="qemu-vexpress-a9.ilg.gnuarmeclipse.managedbuild.cross.target.elf.860020518" name="Executable" projectType="ilg.gnuarmeclipse.managedbuild.cross.target.elf"/>
    </storageModule>
    <storageModule moduleId="scannerConfiguration">
        <autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
        <scannerConfigBuildInfo instanceId="ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.553091094;ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.553091094.;ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.1570350559;ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.input.992053063">
            <autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
        </scannerConfigBuildInfo>
    </storageModule>
    <storageModule moduleId="org.eclipse.cdt.core.LanguageSettingsProviders"/>
    <storageModule moduleId="refreshScope" versionNumber="2">
        <configuration configurationName="Debug">
            <resource resourceType="PROJECT" workspacePath="/f429_tmp"/>
        </configuration>
    </storageModule>
    <storageModule moduleId="org.eclipse.cdt.make.core.buildtargets"/>
    <storageModule moduleId="org.eclipse.cdt.internal.ui.text.commentOwnerProjectMappings">
        <doc-comment-owner id="org.eclipse.cdt.ui.doxygen">
            <path value=""/>
        </doc-comment-owner>
    </storageModule>
</cproject>"""

project_temp = """<?xml version="1.0" encoding="UTF-8"?>
<projectDescription>
    <name>__project_name_flag__</name>
    <comment></comment>
    <projects>
    </projects>
    <buildSpec>
        <buildCommand>
            <name>org.eclipse.cdt.managedbuilder.core.genmakebuilder</name>
            <triggers>clean,full,incremental,</triggers>
            <arguments>
            </arguments>
        </buildCommand>
        <buildCommand>
            <name>org.eclipse.cdt.managedbuilder.core.ScannerConfigBuilder</name>
            <triggers>full,incremental,</triggers>
            <arguments>
            </arguments>
        </buildCommand>
    </buildSpec>
    <natures>
        <nature>org.eclipse.cdt.core.cnature</nature>
        <nature>org.rt-thread.studio.rttnature</nature>
        <nature>org.eclipse.cdt.managedbuilder.core.managedBuildNature</nature>
        <nature>org.eclipse.cdt.managedbuilder.core.ScannerConfigNature</nature>
    </natures>
</projectDescription>"""

projcfg_ini_temp = """#RT-Thread Studio Project Configuration
# $time
cfg_version=v3.0

board_name=
bsp_version=
bsp_path=
chip_name=
project_base_rtt_bsp=true
is_use_scons_build=true
hardware_adapter=
selected_rtt_version=latest
board_base_nano_proj=false
is_base_example_project=false
example_name=
project_type=rt-thread
os_branch=master
os_version=latest
project_name=$project_name
output_project_path=$output_project_path"""

eclipse_core_runtime_temp = """content-types/enabled=true
content-types/org.eclipse.cdt.core.asmSource/file-extensions=s
eclipse.preferences.version=1"""

makefile_targets_temp = """clean2:
\t-$(RM) $(CC_DEPS)$(C++_DEPS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS)
\t-$(RM) $(OBJS) *.elf
\t-@echo ' '

*.elf: $(wildcard ../linkscripts/*/*.lds) $(wildcard ../linkscripts/*/*/*.lds)"""


def get_mcu_info(uvproj_file_path):
    if os.path.exists(uvproj_file_path):
        with open(uvproj_file_path, mode='r') as f:
            data = f.read()
            result = re.search("<Device>(.*)</Device>", data)
            if result:
                return result.group(1)
            else:
                return "unknown"
    else:
        return "unknown"


def gen_makefile_targets(output_file_path):
    try:
        w_str = makefile_targets_temp
        dir_name = os.path.dirname(output_file_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)
        with open(output_file_path, 'w') as f:
            f.write(w_str)
            return True
    except Exception as e:
        print(e)
        return False


def gen_org_eclipse_core_runtime_prefs(output_file_path):
    try:
        w_str = eclipse_core_runtime_temp
        dir_name = os.path.dirname(output_file_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)
        with open(output_file_path, 'w') as f:
            f.write(w_str)
            return True
    except Exception as e:
        print(e)
        return False


def gen_cproject_file(output_file_path):
    template_file_path = os.path.join(os.path.dirname(output_file_path), "template.cproject")
    if os.path.exists(template_file_path):
        try:
            shutil.copy(template_file_path, output_file_path)
        except Exception as e:
            print(e)
        return True
    else:
        CFLAGS = rtconfig.CFLAGS
        AFLAGS = rtconfig.AFLAGS
        LFLAGS = rtconfig.LFLAGS
        if 'CXXFLAGS' in dir(rtconfig):
            CXXFLAGS = rtconfig.CXXFLAGS
        else:
            CXXFLAGS = ""

        if "-T" in LFLAGS:
            items = str(LFLAGS).split()
            t_index = items.index("-T")
            items[t_index] = ""
            items[t_index + 1] = ""
            LFLAGS = " ".join(items)

        try:
            w_str = cproject_temp
            if "a_misc_flag" in w_str:
                w_str = w_str.replace("a_misc_flag", AFLAGS)
            if "c_misc_flag" in w_str:
                w_str = w_str.replace("c_misc_flag", CFLAGS)
            if "cpp_misc_flag" in w_str:
                w_str = w_str.replace("cpp_misc_flag", CXXFLAGS)
            if "c_link_misc_flag" in w_str:
                w_str = w_str.replace("c_link_misc_flag", LFLAGS)
            if "cpp_link_misc_flag" in w_str:
                w_str = w_str.replace("cpp_link_misc_flag", LFLAGS)

            dir_name = os.path.dirname(output_file_path)
            if not os.path.exists(dir_name):
                os.makedirs(dir_name)
            with open(output_file_path, 'w') as f:
                f.write(w_str)
                return True
        except Exception as e:
            return False


def gen_project_file(output_file_path):
    try:
        w_str = project_temp
        dir_name = os.path.dirname(output_file_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)
        with open(output_file_path, 'w') as f:
            f.write(w_str)
            return True
    except Exception as e:
        return False


def gen_projcfg_ini_file(chip_name, project_name, output_file_path):
    try:
        projcfg_file_tmp = Template(projcfg_ini_temp)
        w_str = projcfg_file_tmp.substitute(time=time.strftime("%a %b %d %H:%M:%S %Y", time.localtime()),
                                            project_name=project_name,
                                            output_project_path=os.path.abspath(""))
        dir_name = os.path.dirname(output_file_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)
        with open(output_file_path, 'w') as f:
            f.write(w_str)
            return True
    except Exception as e:
        return False

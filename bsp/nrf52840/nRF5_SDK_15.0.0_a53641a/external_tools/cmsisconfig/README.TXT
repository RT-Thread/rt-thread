CMSIS Configuration Wizard v0.0.7

http://helmpcb.com/software/cmsis-configuration-wizard
https://sourceforge.net/projects/cmsisconfig/

The CMSIS Configuration Wizard allows users to easily configure ARM source files without using the Keil uVision IDE. The wizard parses the source file and generates a GUI, allowing the various parameters to be edited.

Changelog:

v0.0.7		(2017/08/11)
- Added the ability to load a file directly from the command line. Simply pass the full file name as the first paramter to the program (e.g. java -jar CMSIS_Configuration_Wizard.jar /path/to/file).

v0.0.6		(2012/04/20)
- Fixed a bug where the program would throw an exception if a numeric option was outside of its range. The value is now automatically clamped to either the maximum or the minimum.

v0.0.5		(2012/04/20)
- Added support for assembler files.

v0.0.4		(2012/04/20)
- Modifed the filter in the file dialogs to allow both C source and header files.

v0.0.3		(2012/04/20)
- Modified the code for selection modifiers (e.g. <XX=>) so that they can accept both decimal and hexadecimal figures.

v0.0.2		(2012/04/07)
- Initial release.
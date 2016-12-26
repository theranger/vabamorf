# Vabamorf

This is a free morphological analyzer for Estonian language.
Software is created and originally published by [Filosoft](https://github.com/Filosoft/vabamorf).

The goal was to produce a generic library for Linux and OSX environments that can be linked into other projects.

This fork from original build is therefore heavily refactored:
* Modified build tree structure to conform typical Open Source standards
* Switched from classical GNU Make to Cmake
* Switched to hierarchical component-level (static library) builds
* Modified database generation scripts
* Dropped support for original LibreOffice and Java plugins
* Removed Visual Studio project files

Note that many parts of the original build tree use Estonian both in source code, comments and documentation.
This has not been changed.

Some new modules have been added:
* New JNI library, based on the requirements of the [Radagast project](https://github.com/theranger/radagast)

No versioned builds or releases are currently available.

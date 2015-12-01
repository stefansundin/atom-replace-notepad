## 0.2.1 - 2015-11-30
* Fix not being able to open some files with spaces, e.g. when right-clicking files with certain extensions and using the _Edit_ context menu option.
* I forgot to comment out some debug code in previous versions that outputted the command line arguments to a file called `bin\debug.txt`. This file might contain what files you opened using the Notepad redirection, so for privacy reasons you might want to find and delete that file. It should be located at `%USERPROFILE%\.atom\packages\replace-notepad\bin\debug.txt`.

## 0.2.0 - 2015-11-24
* Make `replace-notepad.exe` 32-bit. Fixes issue #1. Should have done this from the beginning as Atom is 32-bit only right now.

## 0.1.1 - 2015-08-02
* Don't hard-code Atom version.

## 0.1.0 - 2015-08-02
* Initial release.

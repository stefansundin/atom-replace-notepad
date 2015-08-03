# replace-notepad

Easily replace Notepad with Atom. 64-bit Windows only. Administrator privileges are required for a one-time setup.

After installing, use the menu: _Packages_ » _Replace Notepad_ » _Replace Notepad_.

Note that you have to restore notepad **before** you uninstall this package!

If there are multiple users using the machine, please be aware of the following caveats:
- This registry tweak is a global setting that will affect all users.
- Since Atom is installed on a per-user basis, each user must install Atom, but since the registry tweak is for a specific user, that user's files must be accessible to all users (this is usually the case by default).
- If the `replace-notepad` stub can't find Atom, it will offer to disable the redirect.

# Compiling

If you want to compile `replace-notepad.exe` yourself, download [Cygwin](https://cygwin.com/) and install the `mingw64-i686-gcc-core` package. Then open the Cygwin terminal, go to the `bin` directory, and run `./build.bat`.

Read these websites for more information:
- http://blogs.msdn.com/b/greggm/archive/2005/02/21/377663.aspx
- http://www.flos-freeware.ch/doc/notepad2-Replacement.html

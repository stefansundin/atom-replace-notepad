# replace-notepad

Easily replace Notepad with Atom. Administrator privileges are required for a one-time setup.

After installing, use the menu: _Packages_ » _Replace Notepad_ » _Replace Notepad_.

Note that you have to restore notepad **before** you uninstall this package!

If there are multiple users using the machine, please be aware of the following caveats:
- This registry tweak is a global setting that will affect all users.
- Since Atom is installed on a per-user basis, each user must install Atom, but since the registry tweak is for a specific user, that user's files must be accessible to all users (this is usually the case by default).
- If the `replace-notepad` stub can't find Atom, it will offer to disable the redirect.

# Restoring Notepad

If you forgot to restore Notepad and uninstalled Atom, you can easily restore it by running this command. In Windows 10, open an elevated command prompt by right-clicking on the start menu and then clicking _Command Prompt (Admin)_.

```shell
cmd /C reg delete "HKLM\Software\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\notepad.exe" /f
```

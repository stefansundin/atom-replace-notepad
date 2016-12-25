If you want to compile `replace-notepad.exe`, you have two options: to use Bash on Windows or Cygwin.

# Bash on Windows

First of all, [get bash set up](https://msdn.microsoft.com/en-us/commandline/wsl/about) and open a prompt.

Install the compiler:

```
sudo apt-get install gcc-mingw-w64
```

Then go to the `bin` directory, and run `./build.sh`.

# Cygwin

Download and install [Cygwin](https://cygwin.com/). Make sure to install the `mingw64-i686-gcc-core` package.

Then open the Cygwin terminal, go to the `bin` directory, and run `./build.bat`.

# Information about redirecting Notepad.exe

- https://blogs.msdn.microsoft.com/greggm/2005/02/21/inside-image-file-execution-options-debugging/
- http://www.flos-freeware.ch/doc/notepad2-Replacement.html

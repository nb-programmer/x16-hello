# Commander X16 Hello World!
This is a tutorial project to get started with programming for the [Commander X16](https://www.commanderx16.com/) 8-bit computer, made by [The 8-bit Guy](https://www.youtube.com/channel/UC8uT9cgJorJPWu7ITLGo9Ww). The project is made to be modular, so that you can create a multi-file project very easily, and make use of Assembly as well as C code.

The project is a simple test of output and input of text, using C and assembly simultaneously and simply making sure your toolchain is set-up correctly.

## Setup
You need to install a toolchain to compile / assemble the project, and an emulator (or a real X16 system!) to execute it. Here is how to set it up: (TODO: other systems)

### Windows
1. Download the [latest CC65 toolchain](https://sourceforge.net/projects/cc65/files/cc65-snapshot-win32.zip) ([Official website](https://cc65.github.io/))
2. Extract it to a folder you won't touch, like in `C:\Program Files\cc65`. You should have folders in it such as `asminc`, `bin`, etc. Add the full path to the `bin` folder to your `Path` environment variable.
3. Open Command Prompt, type `cc65.exe`. You should see the output `cc65.exe: No input files`. If so, you have correctly set up your toolchain. If not, make sure the Path is correctly set, and you have reopened the Command Prompt after doing so.
4. You will now need to install GNU make to build the project. I haven't found a good Windows binary hosting site for it, but right now, the best way is to install [Mingw-w64](https://www.mingw-w64.org/) and you can copy `mingw32-make.exe` to CC65's bin folder and rename it to `make.exe`. Make sure it is also working.
5. Download the [Commander X16 emulator](https://github.com/commanderx16/x16-emulator/releases), extract it and also add the folder to your Path variable. Make sure it works by opening `x16emu.exe` and it should present a BASIC prompt.

## Building
Open a Command Prompt window to this folder, and type `make`. It should compile the project and output `hello.prg` inside the `build` directory. This is the binary file that you will run.

## Running
To make things easier, I've added a recipe to run the emulator from make.

You can run `make run` to launch the emulator, load and launch the ROM on startup.

If you want to run it manually, launch the emulator as so:
```
x16emu -prg build/hello.prg -run
```
Omit the `-run` argument to just load it into memory, and not execute.

# References
- [SlithyMatt](https://github.com/SlithyMatt)'s repositories for X16 tutorials (some of my code is based on this! Thank you!)
- [The Official Commander X16 documentation](https://github.com/commanderx16/x16-docs) check this out if you're serious about learning everything about this amazing system
- [C64 Wiki page](https://www.c64-wiki.com/wiki/Commander_X16) on the Commander X16, a very comprehensive description on the system
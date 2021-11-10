# What's this?
This is a useful program to play music file just in console.

# How to use?
You can enter `conplay help` to get help message or read it below.
```
DESCRIPTION
        Play sound in console.

SYNOPSIS
        conplay help [license]
        conplay play <file> ([--volume <volume>] | -m) [--debug]

OPTIONS
        help        get help messages
        license     print license
        play        play sound
        <file>      sound file
        <volume>    set sound volume (default: 100)
        -m, --mute  mute (the same as "--volume 0")
        --debug, --dbg, -d
                    print debug message

LICENSE
        BSD-3-Clause
        For further information, please type "conplay help license".
```
# Build
1. Download source code
2. Use cmake to build  
   ```
   if you won't use clang to compile, then add the command option below:
   -DNOCMAKE=1
   ```
3. Execute `conplay` (`conplay.exe` on windows)  
   (Don't forget to put the BASS dynamic link library in the same directory.)

# Supported Compiler
* [MSVC](https://visualstudio.microsoft.com/) (tested)
* [clang](https://clang.llvm.org/) (tested)
* or other compilers which support C++20

# Operating System
* Windows (Windows 10 tested)
* Linux (untested) ~~(Maybe)~~

# Special thanks
* [clipp](https://github.com/muellan/clipp) and [its fork for c++20](https://github.com/andreasWallner/clipp/tree/c+%2B20)
* [BASS audio library](http://www.un4seen.com/)
* [colored cout](https://github.com/yurablok/colored-cout)
* [stdcpp.h by myself](https://github/com/sjc0910/conplay/blob/master/include/stdcpp.h)

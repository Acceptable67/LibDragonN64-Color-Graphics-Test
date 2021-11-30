
# LibDragonN64 ROMs
A play around of mathematical functions to draw interesting objects to the screen.

### Compile Script (Windows only)
This REQUIRES the N64DEV directory which can be [downloaded here](http://73.55.44.55/n64dev.7z). It includes MIPS built for Windows and LibDragon. 
Extract it into a folder called <b>N64DEV</b>.

In Visual Studio, go to Build Events -> Pre Build Event and add the following to the Command Line section, set project type to Utility and Rebuild the solution:

```
SET N64_INST=C:\n64dev
SET ROMNAME=$(TargetFileName)
SET CPP_FILES=Source.cpp
SET ROM_SIZE=16M

del map.txt
del *.o
del %ROMNAME%.bin
del %ROMNAME%.elf
del %ROMNAME%.v64

%N64_INST%/bin/mips64-elf-g++ -std=c++11 -march=vr4300 -mtune=vr4300 -G 0 -O2 -Wall -c -IC:/n64dev/include -I/C/n64dev/sm/include -IC:/n64dev/mips64-elf/include -IC:/n64dev/mips64-elf/mips64-elf/include -ffreestanding -fno-exceptions -nostdlib -fno-rtti *.cpp

%N64_INST%/bin/mips64-elf-ld -o %ROMNAME%.elf *.o extern_lib/libSprite.o -TC:/n64dev/ldscripts/n64.ld -Map map.txt -LC:/n64dev/lib -LC:/n64dev/mips64-elf/lib -LC:/n64dev/mips64-elf/lib/gcc/mips64-elf/4.8.1 -LC:/n64dev/mips64-elf/mips64-elf/lib -LC:/n64dev/lib/gcc/mips64-elf/4.4.0 -ldragon -lm -lstdc++ -lc -lgcc -ldragonsys

(to compile CPPLibDragonN64 add "extern_lib/libSprite.o" after "...%ROMNAME%.elf *.o")

%N64_INST%/bin/mips64-elf-objcopy %ROMNAME%.elf %ROMNAME%.bin -O binary

%N64_INST%/bin/mkdfs files.dfs ./filesystem/

%N64_INST%/bin/n64tool -b -l %ROM_SIZE% -t "%ROMNAME%" -h C:/n64dev/headers/header -o %ROMNAME%.v64 %ROMNAME%.bin -s 2M files.dfs

%N64_INST%/bin/chksum64 %ROMNAME%.v64
```
# Roms
## MODE7 & Pseudo-3D example
- Player looking over a grassy plane that has a picture of a mountain on it.
<IMG SRC="https://i.gyazo.com/a26ae20a78e24a62abda7183b85b3206.png"></img>

- Player viewing grey walls w/ depth shading, generated simply with tricks of mathematics- no objects or lines, just buffer manipulation. 

<IMG SRC="http://73.55.44.55/libn64gametest.png"></img>

## CPPLibDragonN64 
This is a C++ compatible LibDragon class engine that provides a decent framework
for a potential library.

<IMG SRC="https://i.gyazo.com/59d2ed4c79047a3a6a649c6650abd1b6.png"></IMG>
## ConsoleTestLib
A test of geometric functions and color generation.

# <img src="https://i.gyazo.com/bb6717da3316b91ca628648acb9bc296.png"></img>
## TestProjLib
Test 2D-Style game.

# <img src="https://i.gyazo.com/80f0e4cc6272547d2a7cb1766c277d2e.png"></img>

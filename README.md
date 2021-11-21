
# LibDragonN64 Color Graphics Test
A play around of mathematical functions to draw interesting objects to the screen.

### Compile Script (Windows only)
In Visual Studio, go to Build Events -> Pre Build Event and add the following to the Command Line section (This requires you have the "N64DEV" directory with MIPS+LibDragon):

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

%N64_INST%/bin/mips64-elf-g++ -std=gnu++98 -march=vr4300 -mtune=vr4300 -G 0 -O2 -Wall -c -IC:/n64dev/include -I/C/n64dev/sm/include -IC:/n64dev/mips64-elf/include -IC:/n64dev/mips64-elf/mips64-elf/include -ffreestanding -fno-exceptions -nostdlib -fno-rtti *.cpp

%N64_INST%/bin/mips64-elf-ld -o %ROMNAME%.elf *.o extern_lib/libSprite.o -TC:/n64dev/ldscripts/n64.ld -Map map.txt -LC:/n64dev/lib -LC:/n64dev/mips64-elf/lib -LC:/n64dev/mips64-elf/lib/gcc/mips64-elf/4.8.1 -LC:/n64dev/mips64-elf/mips64-elf/lib -LC:/n64dev/lib/gcc/mips64-elf/4.4.0 -ldragon -lm -lstdc++ -lc -lgcc -ldragonsys

(to compile CPPLibDragonN64 add "extern_lib/libSprite.o" after "...%ROMNAME%.elf *.o")

%N64_INST%/bin/mips64-elf-objcopy %ROMNAME%.elf %ROMNAME%.bin -O binary

%N64_INST%/bin/mkdfs files.dfs ./filesystem/

%N64_INST%/bin/n64tool -b -l %ROM_SIZE% -t "%ROMNAME%" -h C:/n64dev/headers/header -o %ROMNAME%.v64 %ROMNAME%.bin -s 2M files.dfs

%N64_INST%/bin/chksum64 %ROMNAME%.v64
```
# Roms
## CPPLibDragonN64 
This is a C++ compatible LibDragon class engine that provides a decent framework
for a potential library.

<IMG SRC="https://i.gyazo.com/e36d6c135789f76bf6f79774a4d5ca8c.png"></IMG>
## ConsoleTestLib
A test of geometric functions and color generation.

# <img src="https://i.gyazo.com/bb6717da3316b91ca628648acb9bc296.png"></img>
## TestProjLib
Test 2D-Style game.

# <img src="https://i.gyazo.com/80f0e4cc6272547d2a7cb1766c277d2e.png"></img>

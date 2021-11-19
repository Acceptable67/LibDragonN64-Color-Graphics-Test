#!/bin/sh
echo "Test"
ROMNAME=TestLibProj
ROM_SIZE = 2M

/home/n64/mips64-elf/bin/mips64-elf-g++ -std=c++0x -march=vr4300 -mtune=vr4300 -G 0 -O2 -Wall -c -I/home/n64/mips64-elf/include -I/home/n64/mips64-elf/sm/include -I/home/n64/mips64-elf/include -I/home/n64/mips64-elf/mips64-elf/include -ffreestanding -fno-exceptions -fno-rtti  *.cpp 

/home/n64/mips64-elf/bin/mips64-elf-ld -o $ROMNAME.elf *.o -T/home/n64/mips64-elf/lib/n64ld.x -Map map.txt -nostdlib -L/home/n64/mips64-elf/lib -L/home/n64/mips64-elf/mips64-elf/lib -L/home/n64/mips64-elf/lib/gcc/mips64-elf/4.4.0 -L/home/n64/mips64-elf/mips64-elf/mips64-elf/lib -L/home/n64/mips64-elf/lib/gcc/mips64-elf/4.4.0 -ldragon -lm -lstdc++ -lc -lgcc -ldragonsys -Tn64ld.x -logg

/home/n64/mips64-elf/bin/mips64-elf-objcopy $ROMNAME.elf $ROMNAME.bin -O binary

/home/n64/mips64-elf/bin/mkdfs files.dfs ./filesystem/

/home/n64/mips64-elf/bin/n64tool -b -l 2M -t "RPG TEST" -h /home/n64/mips64-elf/lib/header -o $ROMNAME.v64 $ROMNAME.bin -s 1M files.dfs

/home/n64/mips64-elf/bin/chksum64 $ROMNAME.v64

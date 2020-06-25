# Corewar

The Core War consists of players that are written in assembly, a compiler to turn them into binary, and the virtual computer to run the programs on.

The program is written using read, open, write, malloc, free and exit from stdlib.h.

This is an example of a simple player, a normal player has around 150 lines of assembly code:

    .name "zork"
    .comment "I'M ALIIIIVE"
    
    l2:          sti r1,%:live,%1
                 and r1,%0,r1
    
    live:        live %1
                 zjmp %:live

This complies to binary which is later represented in hexadecimal. The above program looks like this when it’s compiled:

    0000000 00 ea 83 f3 7a 6f 72 6b 00 00 00 00 00 00 00 00
    0000010 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    *
    0000080 00 00 00 00 00 00 00 00 00 00 00 17 49 27 4d 20
    0000090 41 4c 49 49 49 49 56 45 00 00 00 00 00 00 00 00
    00000a0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    *
    0000890 0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01
    00008a0 00 00 00 01 09 ff fb

The first part includes an identification code and the name, followed by the comment, and ending with the program which will be stored in the memory of the virtual machine.


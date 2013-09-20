Teh Boot

Teh Boot is a simple, open source bootloader that was started as a simple project
by me to help sharpen by skills as a low-level developer. Currently, all the project
does is boot in 16-bit mode and jump to some C code where it prints to the VGA buffer.
It isn't much, but its a start.

Objectives
----------
 
 - Provide other brothers in the struggle a reasonable dependable and well-documented example
   from the one who came before.
 
 - Sharpen my skills in Assembly Langauge and Kernel
 
 - Deepen my understanding of the x86 architecture and how a system boots

 - Of course, to become a billionare, because that is possible with open source
   software

Why am I doing this?
--------------------

 - The only reason I can think of right now is because I might secretly hate myself so much that I
   don't even know it.

How to Use?
-----------
  
 Glad you want to give it a shot.
 
 run the command
 
     $ make
 
 This will build, link and flash the bootloader to a virtual hard drvie called hda.img (although
 this is configurable with the IMAGE environment variable)
 
 to give it a shot, you should install qemu. Generally you can find it in the repositories. Then run either
 
    $ make run
 
 or
 
    $ qemu -hda hda.img
 
 If my bootloader fails at even the simple task it is supposed to do, you can debug it with gdb and qemu!!
 Just run:
 
     $ make debug
 
 or
 
     $ qemu -hda hda.img -S -s &
     $ gdb -ex 'target remote localhost:1234' -ex 'break *0x7c00' -ex 'break *0x1000' -ex 'c'

Good Luck and Have Fun!!

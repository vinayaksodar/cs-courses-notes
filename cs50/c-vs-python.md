# Compilation vs interpretation

C gets compiled down to machine code this means that it is direct instructutions to the processor you don't need to have an operating system even to run this. This is the reason c compiled code is used in mmicroprocessors annd bootloaders etc places where you don't have access to an os. Many standaard functions like malloc use system calls that rely on os but you can write manual implementations of these if you are running on bare metal

Python needs the python program(the interpreter) to be running which in turn reads the instructions you have written in the python file and executes them. The interpreter is a program that is written in c and contains instructions for the processer. It simply interpretes yoour commands and maps them to the appropriate instructions for the precessor.
The standard Python interpreter (e.g. CPython):

Is written in C.
Is compiled into a binary (like any other program).
Needs an OS to:
Load it from the file system.
Allocate memory.
Handle I/O (keyboard, screen, etc.).
Manage processes and threads.

the limitation is you can't add any functionality that the interpreter itself can't do you are limited by the interpreter if you use standard python.

# Exceptions

The c program doesn't end automatically if there is any unexpected behaviour it dos not throw any exceptions. You have to manually return with error code. the error code will have to be some value taht is not normally returned by the fuction that is again a limitation

the python program will throw exception and quit you have to handle try catch blocks manually.

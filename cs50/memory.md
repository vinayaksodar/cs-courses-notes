# Memory management

All memory like variables etc that are allocated by the compiler will live in the stack and these will be automatically cleaned up.  
All memory that you ask for using malloc will live in the heap and you have to have to remember to free this.  
This seems super easy but conder the below case you have exited the program when you hit some error or there is no more momory but you should free all the variable you allocated using malloc before it you can't say simply return 1.
[watch this described by david malan in cs50](https://youtu.be/aV8LlSmd1E8?t=4392)

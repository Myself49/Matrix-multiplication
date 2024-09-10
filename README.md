# Matrix-multiplication

Multi-threaded programs using Pthread API and JAVA thread to do *matrix multiplication*.

## There are 2 source files

### *1.* Main.c

This multi-threaded matrix multiplication program written in `C` that uses `pthread` library to create a thread pool and perform matrix multiplication splitting work amoung the threads.

### *2.* Matrix.java

This multi-threaded matrix multiplication program written in `JAVA` that uses `JAVA thread` library.
In this program we use 3*3 matrix only and 3 threads for multiplication.
Threads will naturally terminate after processing.

### *3.* How to run
Use this command to compile and run `C` file,

`gcc -g -pthread main.c -o main`

`./main.exe`

In cmd use `main.exe` instead of `/.main.exe`

Use this command to compile and run `JAVA` file,

`javac Matrix.java`

`java Matrix`
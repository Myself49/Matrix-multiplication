# Matrix-multiplication

Multi-threaded programs using Pthread API and JAVA thread to do *matrix multiplication*.

## There are 2 source files

### *1.* Main.c

This multi-threaded matrix multiplication program written in **C** that uses `pthread` library to create a thread pool and perform matrix multiplication splitting work amoung the threads.

### *2.* MatrixTest.java

This multi-threaded matrix multiplication program written in **JAVA** that uses `JAVA thread` library.
In this program we use 3*3 matrix only and 3 threads for multiplication.
Threads will naturally terminate after processing.

# 2017 Operating System
Porf. Li‐Pin, Chang National Chiao‐Tung University
## Programming Assignment #1
### A Simple Shell
#### Control flow of your simple shell:
- Display the prompt sign “>” and take a string from user
- Parse the string into a program name and arguments • Fork a child process
- Have the child process execute the program
- Wait until the child terminates
- Go to the first step


## Programming Assignment #2
### Multi-Process Matrix Multiplication using Shared Memory
#### Overview
-  Matrix multiplication using multiple processes
    -  Basic parallel processing
    -  Will be faster with multicore machines
-  Input: the dimension of two square matrices A & B
    -  E.g., 100 -> A, B, and C are 100x100 square matrices
-  Output: an execution time and a checksum

## Programming Assignment #3
### Parallel Quicksort using Pthread
#### Parallel Quicksort
![](https://i.imgur.com/YJWxT4B.png)

## Programming Assignment #4
### Quick Sort with a Thread Pool
#### Objective
- Multithreaded sorting using a thread pool
- #of threads in the pool determines the max. degree of parallelism
- The problem definition is the same as that in the previous assignment, except that **the binding of sorting jobs to threads is dynamic**
- A job performs one of the following
    - Partitioning a large array into two small arrays
        - Left array < pivot < right array
    - Sorting a bottom‐level array
        - Bubble sort

## Programming Assignment #5
### Page Cache Simulation: FIFO and LRU
#### Simulation
![](https://i.imgur.com/vsb8dXs.png)

## Programming Assignment #6
### A File Find Utility
#### Introduction
- Implement a subset of the “find” command
    - Finding files by name, inode #, and file size
    - **Recursively descending** into sub‐directories to find all matches
    
## Programming Assignment #7
### File Fragmentation Reproduction
#### File fragmentation
- Ideally, a file is allocated in contiguous disk space
    - File system ages after it undergoes a number of allocation and de‐allocation requests
    - Free space become fragmented
    - It is difficult for an aged file system to allocate contiguous disk space for a new file or an existing to grow
- File fragmentation increase the disk positioning overhead

# 🧵 POSIX Threads (Pthreads) Practice Tasks

This repository contains solutions to various multithreading exercises implemented in **C** using the **POSIX Threads (Pthreads)** library. The tasks focus on thread creation, synchronization, dynamic memory management, shared resources, and file processing.

## 📋 Task List

### 🔹 Task 1 – Find the Third Maximum Element

Create a thread that calls a function receiving an array and its size as arguments. The function returns the **third largest element** of the array, and the returned value is printed by the main thread.

### 🔹 Task 2 – Prime Numbers with Dynamic Memory

Create two threads:

*  The first thread dynamically allocates memory and stores all prime numbers from `2` to `N`.
*  The second thread receives the generated array, prints all prime numbers, and releases the dynamically allocated memory.

### 🔹 Task 3 – Matrix Processing with Four Threads

Generate and initialize an `N × N` matrix. Create four concurrent threads where each thread performs a different task:

*  Find and print the maximum element.
*  Find and print the minimum element.
*  Print the main and secondary diagonals.
*  Calculate and return the arithmetic mean of all matrix elements.

The matrix must remain unchanged throughout execution.

### 🔹 Task 4 – Shared Counter with Mutex

Use a global variable initialized to `0`. Each thread increments the variable by `100`. 🔒 A mutex is used to synchronize access and ensure the final value is always a multiple of `100`.

### 🔹 Task 5 – Parallel Array Summation

Split an array into multiple segments and assign each segment to a separate thread. Every thread computes the sum of its own segment and safely updates a global sum variable.

### 🔹 Task 6 – Ordered Printing with Two Threads

Create two threads that print the elements of an array in the correct order:

* The first thread prints elements with even indices.
* The second thread prints elements with odd indices.

Proper synchronization guarantees the expected output sequence.

### 🔹 Task 7 – File Encoding and Decoding Pipeline

The program accepts an input filename and creates two synchronized threads:

*  The first thread reads one line from the input file, encodes it, and writes it into `coded.txt`.
*  The second thread reads the encoded line from `coded.txt`, decodes it, and writes the result into `new_<input_filename>.txt`.

The threads execute sequentially through synchronization.

### 🔹 Task 8 – Print Even Numbers

Read an integer `n` from the user and create a thread that prints all even numbers from `0` to `n`. 

### 🔹 Task 9 – Write Even and Odd Numbers into Separate Files

Read an integer `n` and create two threads:

* 📄 One thread writes all even numbers from `0` to `n` into `even.txt`.
* 📄 The other thread writes all odd numbers from `0` to `n` into `odd.txt`.

Each thread is responsible only for its own output file.

### 🔹 Task 10 – Concurrent Counter Updates

Maintain a global counter initialized to `0`.

The user provides:

* `n1` and `count1` for the first thread.
* `n2` and `count2` for the second thread.

Each thread repeatedly increments the shared counter according to its parameters. Synchronization mechanisms should be used to prevent race conditions.

---

## 🛠️ Technologies Used

*  C Programming Language
*  POSIX Threads (Pthreads)
*  Mutexes
*  Condition Variables
*  Dynamic Memory Allocation
*  File I/O
*  Thread Synchronization

---

## 🎯 Learning Objectives

These exercises are designed to provide practical experience with:

*  Creating and managing threads
*  Synchronizing concurrent execution
*  Protecting shared resources
*  Working with dynamic memory in multithreaded applications
*  Coordinating thread communication
*  Processing files concurrently

Happy Coding! 🚀

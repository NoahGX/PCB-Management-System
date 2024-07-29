# Process Control Block Management System

## Overview
This project implements two versions of a Process Control Block (PCB) management system, each designed to manage and track processes in an operating system-like environment. The PCB is crucial for process management, allowing the operating system to store and manage information about active processes. This implementation explores two structural approaches to managing relationships between processes: linked list (in PCBv1) and sibling pointers (in PCBv2).

## Features
  - **PCBv1.c**: Uses a linked list to manage children of each process. This implementation facilitates easy traversal and management of child processes.
  - **PCBv2.c**: Utilizes a more complex structure with pointers for the first child, younger siblings, and older siblings, allowing for a potentially more efficient management in certain scenarios.
  - **Timer Integration**: Both versions include a timing mechanism to measure the execution duration of operations using microsecond precision.

## Usage
To compile and run all programs, use the provided Makefile:
  ```
  make all
  ```

## Prerequisites
  - GCC compiler or any standard C compiler
  - Basic knowledge of C programming and process management concepts

## Input
The main functions in both PCB versions do not require external user input as they are designed to perform predefined tasks that demonstrate the creation and destruction of process structures.

## Output
Both implementations output the list of child processes before and after the destruction of certain processes to showcase the functionality of each system. The output also includes the time taken for the operations to demonstrate the efficiency of each implementation.

## Notes
  - The size of the PCB table is defined as 1000, which can be modified according to needs.
  - Initially, all entries in the PCB table are considered free except for the zeroth entry which is typically reserved for the initial process.
  - The system uses `-2` to indicate a free or non-existent relation in the PCB tables and `-9999` for the initial parent in `PCBv1`.
  - Error handling is implemented for out-of-bound accesses and memory allocation failures.

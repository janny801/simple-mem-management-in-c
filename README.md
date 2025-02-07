# Simple C Memory Management

## Description
This C project is designed to manage memory for a linked list of persons, showcasing basic memory management in C. Each `Person` structure contains dynamically allocated memory for their name, age, and pointers to the next person in the list. The program allows users to enter person details continuously until they decide to stop, after which it displays all entered persons and frees the allocated memory properly.

## Features
- **Dynamic Memory Allocation**: The project demonstrates the dynamic allocation, reallocation, and deallocation of memory using `malloc` and `free`.
- **Linked List Operations**: Implements basic operations on a linked list including insertion and traversal.
- **Input Validation**: Robust handling of user input for names and ages, ensuring all entries are valid before processing.
- **Memory Leak Prevention**: Ensures all dynamically allocated memory is freed properly to prevent memory leaks.

## Getting Started

### Dependencies
- You need to have GCC installed on your machine to compile and run this project.
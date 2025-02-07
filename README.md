# Simple C Memory Management

## Description
This C project demonstrates basic memory management techniques by managing a linked list of persons. Originally designed to handle a single name, the project was expanded to include a linked list implementation allowing multiple entries. Each `Person` structure contains dynamically allocated memory for their name, age, and a pointer to the next person in the list. The program continuously accepts input from the user until 'done' is entered, displays all entered persons, and then frees all allocated memory properly.

## Features
- **Dynamic Memory Allocation**: The project illustrates dynamic memory allocation, reallocation, and deallocation using `malloc` and `free`.
- **Linked List Operations**: Implements insertion at the head of the list and traversal, showcasing typical linked list operations.
- **Input Validation**: Robust input validation ensures all entries for names and ages are valid before they are processed.
- **Memory Leak Prevention**: Ensures that all dynamically allocated memory is freed, preventing memory leaks.

## Getting Started

### Dependencies
- GCC Compiler is required to compile and execute this program.

### Installing and Running
1. **Clone the repository:**
- git clone https://github.com/janny801/simple-mem-management-in-c.git
2. **Navigate to the project directory:**
3. **Compile the program using GCC:**
4. **Run the program:**




## Usage
1. The program prompts the user to enter a name or type 'done' to finish.
2. If a valid name is entered, it then prompts for an age.
3. Upon entering a valid age, the person is added to the linked list at the head.
4. After typing 'done', the program displays all persons in the linked list and then frees the allocated memory.

## Future Enhancements
- **File Input for Names and Ages**: Implement functionality to read names and ages from a file instead of manual entry via the command line, enhancing usability for batch inputs.
- **Greater visibility of Memory Allocation and Freeing**: Add features to make the process of memory allocation and deallocation more transparent, allowing users to visually verify that each allocation matches its corresponding deallocation.

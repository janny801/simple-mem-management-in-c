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
   - Use the command below to clone the repository to your local machine:
     ```bash
     git clone https://github.com/janny801/simple-mem-management-in-c.git
     ```

2. **Navigate to the project directory:**
   - Change into the project directory with:
     ```bash
     cd simple-mem-management-in-c
     ```

3. **Compile the program using GCC:**
   - Compile the source code file `main.c` into an executable named `main` using the GCC compiler:
     ```bash
     gcc main.c -o main
     ```

4. **Run the program:**
   - Execute the compiled program by running:
     ```bash
     ./main
     ```

Follow these steps to successfully compile and run the program on your system. Ensure you have GCC installed on your machine. If not, you might need to install it first, depending on your operating system.


## Usage
1. The program prompts the user to enter a name or type 'done' to finish.
2. If a valid name is entered, it then prompts for an age.
3. Upon entering a valid age, the person is added to the linked list at the head.
4. After typing 'done', the program displays all persons in the linked list and then frees the allocated memory.

## Example Input & Output

```sh
Enter a name (or type 'done' to finish): Alice
Enter an age: 20

Allocated person struct at location: 0x12a704080
Allocated name at location: 0x12b004080
Allocated age at location: 0x12b004090
First person added to the linked list

Enter a name (or type 'done' to finish): Bob
Enter an age: 50 

Allocated person struct at location: 0x12b104080
Allocated name at location: 0x12b204080
Allocated age at location: 0x12b204090
Person added to the linked list

Enter a name (or type 'done' to finish): Done

--- List of Persons ---
Name: Alice, Age: 20
Name: Bob, Age: 50

--- Now freeing persons from memory ---
Freeing name structure at location: 0x12b004080
Freeing age structure at location: 0x12b004090
Freeing person structure at location: 0x12a704080
Freeing name structure at location: 0x12b204080
Freeing age structure at location: 0x12b204090
Freeing person structure at location: 0x12b104080
```

## Future Enhancements

- **File Input for Names and Ages**:
  - Implement functionality to read names and ages from a file instead of manual entry via the command line, enhancing usability for batch inputs.

- **Greater Visibility of Memory Allocation and Freeing**:
  - Add features to make the process of memory allocation and deallocation more transparent, allowing users to visually verify that each allocation matches its corresponding deallocation.
  - Enable the user to match corresponding memory allocations with the same address when that memory is freed, particularly for the `person` struct, which includes fields for `name` and `age`. This will help ensure that memory is properly managed and debug issues related to memory leaks or mismanagement.

- **Increased Input Validation**:
  - Strengthen error checking for user inputs to prevent invalid data from being processed.
  - Ensure that names contain only alphabetic characters by restricting numeric or special characters in name inputs.
  - Validate age inputs to ensure they are within a reasonable range and consist only of numeric values.
  - Improve handling of edge cases, such as empty input fields or excessively long strings, to enhance program robustness.

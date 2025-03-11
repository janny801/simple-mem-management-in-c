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
Enter a name (or type 'done' to finish): janred
Enter an age: 20

[ALLOC] Person 'janred' struct at 0x145704080
[ALLOC] Name  'janred' at 0x1457040a0
[ALLOC] Age   'janred' at 0x1457040b0
First person added to the linked list

Enter a name (or type 'done' to finish): lebron
Enter an age: 40

[ALLOC] Person 'lebron' struct at 0x146004080
[ALLOC] Name  'lebron' at 0x146104080
[ALLOC] Age   'lebron' at 0x146104090
Person 'lebron' added to the linked list

Enter a name (or type 'done' to finish): yo mommaa
Invalid name. Names must only contain alphabetic characters. Please enter a valid name.
Enter a name (or type 'done' to finish): yomoma
Enter an age: 200
Please enter a valid age between 0 and 120: 120

[ALLOC] Person 'yomoma' struct at 0x145605ed0
[ALLOC] Name  'yomoma' at 0x145605ef0
[ALLOC] Age   'yomoma' at 0x145605fc0
Person 'yomoma' added to the linked list

Enter a name (or type 'done' to finish): done

--- List of Persons ---
Name: janred, Age: 20
Name: lebron, Age: 40
Name: yomoma, Age: 120

--- Now freeing persons from memory ---

--- Freeing Memory (Matching Allocations) ---
-----------------------------------------------------------------------------
| Person Name     | Struct Addr        | Name Addr          | Age Addr           |
-----------------------------------------------------------------------------
| janred          | 0x145704080        | 0x1457040a0        | 0x1457040b0        |
[FREE] Name  'janred' at 0x1457040a0
[FREE] Age   'janred' at 0x1457040b0
[FREE] Person 'janred' struct at 0x145704080
| lebron          | 0x146004080        | 0x146104080        | 0x146104090        |
[FREE] Name  'lebron' at 0x146104080
[FREE] Age   'lebron' at 0x146104090
[FREE] Person 'lebron' struct at 0x146004080
| yomoma          | 0x145605ed0        | 0x145605ef0        | 0x145605fc0        |
[FREE] Name  'yomoma' at 0x145605ef0
[FREE] Age   'yomoma' at 0x145605fc0
[FREE] Person 'yomoma' struct at 0x145605ed0
-----------------------------------------------------------------------------
```

## Explanation:

1. The user enters `"Alice"` as the name and `20` as the age.
   - Memory is allocated for Alice and added to the linked list.

2. The user enters `"Bob"` as the name and `50` as the age.
   - Memory is allocated for Bob and added to the linked list.

3. The user enters `"Done"`, signaling the program to stop taking inputs.

4. The program displays all stored persons in the list.

5. The program then frees all dynamically allocated memory, ensuring no memory leaks.

## Future Enhancements

- **File Input for Names and Ages**:
  - Implement functionality to read names and ages from a file instead of manual entry via the command line, enhancing usability for batch inputs.

- **Increased Input Validation**:
  - Strengthen error checking for user inputs to prevent invalid data from being processed.
  - Ensure that names contain only alphabetic characters by restricting numeric or special characters in name inputs.
  - Validate age inputs to ensure they are within a reasonable range and consist only of numeric values.
  - Improve handling of edge cases, such as empty input fields or excessively long strings, to enhance program robustness.

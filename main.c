//simple memory management system 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <limits.h> 
#include <ctype.h>   // Needed for isalpha()



/* 




other features to implement 
- make name input dynamic to prevent buffer overflow and unused memory 
-(done)when taking in name input, normalize ‘done’ incase user accidentally adds spaces or capitalizes (for example so that we dont have someone named “Done”)

- file input for names and ages instead of typing in command line 
add easier way to view the allocation and freeing so that the user can verify that they match
- sort persons by age when displaying (after typing 'done' ) 



*** dynamic resizing for name input ***

- use getline() instead of fgets()
How it works:

Takes a NULL pointer and allocates memory dynamically.
Automatically resizes the buffer as needed.
Reads an entire line, including the newline character (\n).
Stores the actual number of bytes read.

Advantages Over fgets():
✅ No buffer overflow – Resizes as needed.
✅ Handles long input gracefully – No truncation.
✅ Includes input length (len) – Useful for processing.
❌ Must free memory manually (free(line)).

** allocate to the heap instead of the stack 
getline() dynamically allocates memory using malloc() (or realloc() internally if resizing is needed).
The pointer you pass to getline() will receive a memory block from the heap, meaning it will persist beyond the function call until you explicitly free() it.



before[using fgets()]
nameBuffer is a stack-allocated array.
When the function exits, nameBuffer is automatically freed.
No need for free(), but the buffer size is fixed (risk of truncation).




why still need freePerson() function? 
Use of free() in freePersons() for fgets()
Even though fgets() itself does not require free(), you still need freePersons() because:

fgets() stores input in nameBuffer (stack memory)

nameBuffer[100] is stack-allocated and is automatically freed when the function exits.
No need to call free(nameBuffer);
But you store nameBuffer in a dynamically allocated Person struct

When adding a new Person, you allocate heap memory for name using malloc():
This memory persists beyond the function call and must be freed manually.
freePersons() ensures memory is released

freePersons() calls free(newPerson->name); to free the heap-allocated name.
It also frees newPerson->age (if dynamically allocated) and newPerson itself.



how it should function after [using getline()]
getline() allocates memory on the heap and resizes as needed.
The pointer line stores the heap address.
You must call free(line);, or memory will leak.




_______________________

small heap allocation example to build off of
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int));  // Allocates memory for one int

    if (ptr == NULL) {  
        printf("Memory allocation failed!\n");
        return 1;
    }

    *ptr = 42;  // Assign a value
    printf("Value: %d\n", *ptr);

    free(ptr);  // Free the allocated memory
    return 0;
}


*/




typedef struct Person
{
    //dynamically allocated ptrs 
    char *name; 
    int *age; 
    struct Person *next; //pointer to next person in the LL 
}Person; 

//function prototypes (used for best prac-- defined later)
Person* addPerson(Person *head, const char *name, const int *age);
void printPersons(Person *head);
void freePersons(Person *head);



// Function to trim leading and trailing spaces from a string
void trimWhitespace(char *str) {
    int start = 0, end = strlen(str) - 1;

    // Move start index forward past any leading spaces
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    // Move end index backward past any trailing spaces
    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Shift the trimmed string to the beginning
    memmove(str, str + start, end - start + 1);

    // Null terminate the string at the correct position
    str[end - start + 1] = '\0';
}






int main()
{
    //main

    Person *head = NULL;
    char nameBuffer[100]; 
    int age, scanfResult;

    while(1)
    {
        
        printf("Enter a name (or type 'done' to finish): "); 
        char *result = fgets(nameBuffer, sizeof(nameBuffer), stdin); //use fget()
                                                                //to assign input result to namebuffer variable

    // Check if fgets returned NULL, indicating an error or EOF
        if (result == NULL) {
            printf("Error reading name. Please try again.\n");
            continue; // Skip the rest of the loop and start over
        }
        // Remove newline character from nameBuffer if present
        nameBuffer[strcspn(nameBuffer, "\n")] = 0;

        // **Trim whitespace from the name**
        trimWhitespace(nameBuffer);


        // Check if the user wants to quit (case-insensitive) directly in the if statement
        if (strcasecmp(nameBuffer, "done") == 0) {  
            break;
        }


        // Check if the input is empty or consists only of whitespace characters
        if (strlen(nameBuffer) == 0 || strspn(nameBuffer, " \t\n") == strlen(nameBuffer)) {
            // If true, the input is either completely empty or only contains spaces, tabs, or newlines
            printf("Name cannot be empty. Please enter a valid name.\n");
            continue; // Ask the user to re-enter a valid name
        }

        int isValidName = 1;
        // Validation loop to ensure name contains only alphabetic characters
        for (int i = 0; nameBuffer[i] != '\0'; i++) {
            if (!isalpha(nameBuffer[i])) { // Check if the character is not alphabetic
                isValidName = 0;
                break;
            }
        }
        
        if (!isValidName) {
            printf("Invalid name. Names must only contain alphabetic characters. Please enter a valid name.\n");
            continue;
        }



        printf("Enter an age: ");
        while (1) { 
            scanfResult = scanf("%d", &age); 

            if (scanfResult != 1) { 
                printf("Invalid input. Please enter an integer for age: ");
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }

            if (age < 0 || age > 120) { 
                printf("Please enter a valid age between 0 and 120: ");
                continue; 
            }

            while (getchar() != '\n'); // Clear input buffer after successful input
    // This is needed because scanf("%d") reads only the integer, but leaves a newline (\n) in the input buffer.
    // Without clearing the buffer, fgets() in the next loop iteration would read an empty string instead of waiting for user input.
 
            
            
            break; 




        }
                
        

        head = addPerson(head, nameBuffer, &age); 
    }


    printf("\n--- List of Persons ---\n");
    printPersons(head);

    printf("\n--- Now freeing persons from memory ---\n");
    freePersons(head);

    return 0;


}


    /*          old loop to take in singlular person 


    
    char nameBuffer[100]; //temp array to hold user input for name
    int age; //temp variable to hold user input for age 


    printf("enter a name: "); 
    scanf("%99s", nameBuffer); //read up to 99 char(prevent overflow)
    //dont need to use &nameBuffer since array naturally
    //decay to string in c


    //prompt the user to enter an age
    printf("enter an age: "); 
    scanf("%d", &age); //store age 


   //dynamically allocate memory for a person and initialize it with user input 
   Person *person = allocatePerson(nameBuffer, &age); 

   
   //print details of the allocated person 
   printPerson(person); 

   //free dynamically allocated memory to avoid memory leaks
   freePerson(person); 

   return 0; //prog ends
    

     */









/* used for allocating memory for an array 
Person* allocatePerson(const char*name, const int *age)
{
    // allocate memory for the person structure
    Person *newPerson = (Person*)malloc(sizeof(Person)); 
    if(newPerson ==NULL)
    {
        //check if allocation failed
        printf("error: memory allocation failed for person"); 
        exit(EXIT_FAILURE); 
    }
    printf("allocated person struct at address: %p\n", (void*)newPerson); 


    //allocate memory for the name 
    newPerson-> name= (char*)malloc((strlen(name)+1)*sizeof(char)); 
    if(newPerson->name==NULL)
    {
        printf("error; memory allocation failed for name"); 
        free(newPerson); 
        exit(EXIT_FAILURE); 
    }
    strcpy(newPerson->name, name); //copy name into allocated memory
    printf("allocated name address at:  %p\n", (void*)newPerson->name); 


    //allocate memory for the age 
    newPerson->age = (int*)malloc(sizeof(int)); 
    if(newPerson->age ==NULL)
    {
        printf("error; memory allocation for age failed"); 
        free(newPerson->name);
        free(newPerson); 
        exit(EXIT_FAILURE);
    }
    *(newPerson->age)=*age; 
    printf("allocated age at address: %p\n", (void*)newPerson->age); 

    return newPerson; 

}

*/



//funciton to add a new person to the linked list 












//need to define other funtions inorder for compilation proper

//free and print functions for allocation of person

//function to free all dynamically allocated memory for a person 

/* used for array , we are now using LL
void freePerson(Person *person)
{
    if(person != NULL)
    {
        printf("freeing name at address: %p\n",(void*)person->name); 
        free(person->name); // free mem allocated for name
        printf("freeing age at address: %p\n", (void*)person->age); 
        free(person->age); //free mem allocated for age
        printf("freeing person struct at address: %p\n", (void*)person); 
        free(person); //free mem allocated for person struct
    }
}

 */


//func to print details of the person 


/*used or array 
void printPerson( Person *person)
{
    if(person!=NULL)
    {
        printf("Name: %s, Age: %d\n", person->name, *(person->age)); // Print the name and the value of age 

    }
}
*/









/* 


notes for the freepersons() function via for functionality with fgets() 
- so that i can understand how to fix/modify when making dynamic


You still need freePersons() because you manually allocate memory (malloc()) for names, ages, and linked list nodes.


If a variable is stored on the stack, it is automatically deallocated when the function exits. No free() is needed.
If a variable is stored on the heap (using malloc()), it persists beyond function execution and must be manually freed.


*/





/*
notes
strings decay to char* 

each name is a string of char* in memory?

dereference; access or retrieve the value stored 
at the memory address a pointer is pointing to 



By adding:


while (getchar() != '\n'); // Clear input buffer
This loop consumes all leftover characters in the input buffer until it finds a newline (\n).
Now, when fgets() is called, the input buffer is empty, so it correctly waits for user input instead of reading an unwanted leftover newline.

🔹 What is the Input Buffer?
The input buffer is a temporary memory region where user input is stored before being processed by your program.
When you type something and press Enter (⏎), the input first goes into this buffer before functions like scanf() or fgets() process it.
🔹 Where is the Input Buffer Stored?
It is typically stored in memory by the OS and managed by standard input (stdin).
It behaves like a queue:
Characters are added when you type.
Characters are removed when a function reads from it.
If there are leftover characters, they remain until explicitly cleared.









*/

Person* addPerson(Person *head, const char *name, const int *age) {
    // Allocate memory for the new person structure
    Person *newPerson = (Person*) malloc(sizeof(Person)); 
    if (newPerson == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for person struct\n");
        exit(EXIT_FAILURE); 
    }
    // Log the memory address where the new person struct is allocated
    printf("\n[ALLOC] Person '%s' struct at %p\n", name, (void*)newPerson);

    // Allocate memory for the person's name dynamically
    // This ensures we store a copy of the name and do not reference the original input buffer
    newPerson->name = (char*) malloc((strlen(name) + 1) * sizeof(char)); 
    if (newPerson->name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for name\n");
        free(newPerson);  // Free the struct since name allocation failed
        exit(EXIT_FAILURE); 
    }
    // Copy the name into the newly allocated memory
    strcpy(newPerson->name, name);
    // Log the memory address where the name is stored
    printf("[ALLOC] Name  '%s' at %p\n", name, (void*)newPerson->name);

    // Allocate memory for the person's age dynamically
    newPerson->age = (int*) malloc(sizeof(int)); 
    if (newPerson->age == NULL) {
        fprintf(stderr, "Error: Memory allocation for age failed\n");
        free(newPerson->name);  // Free previously allocated memory before exiting
        free(newPerson);
        exit(EXIT_FAILURE); 
    }
    *(newPerson->age) = *age;  // Store the age value in the allocated memory
    // Log the memory address where the age is stored
    printf("[ALLOC] Age   '%s' at %p\n", name, (void*)newPerson->age);

    newPerson->next = NULL;  // Initialize the next pointer to NULL

    // Append the new person to the linked list
    if (head == NULL) {  
        // If the list is empty, this new person becomes the head
        printf("First person added to the linked list\n\n");
        return newPerson;
    } else {
        // Traverse to the last node in the list and append the new person
        Person *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPerson;
    }

    // Print confirmation that the person has been added
    printf("Person '%s' added to the linked list\n\n", name);
    return head;  // Return the head of the list (unchanged)
}

void freePersons(Person *head) {
    // Print header for better visualization
    printf("\n--- Freeing Memory (Matching Allocations) ---\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("| %-15s | %-18s | %-18s | %-18s |\n", "Person Name", "Struct Addr", "Name Addr", "Age Addr");
    printf("-----------------------------------------------------------------------------\n");

    Person *current = head;
    while (current != NULL) {
        Person *next = current->next;  // Save the next person before freeing memory

        // Store name in a temporary variable before freeing it
        char *nameCopy = strdup(current->name); // Duplicate the name safely
        if (!nameCopy) {
            fprintf(stderr, "Error: Memory allocation failed while copying name.\n");
            exit(EXIT_FAILURE);
        }

        // Print the memory addresses in table format
        printf("| %-15s | %-18p | %-18p | %-18p |\n",
               nameCopy, (void*)current, (void*)current->name, (void*)current->age);

        // Free the dynamically allocated name and log the action
        if (current->name != NULL) {
            printf("[FREE] Name  '%s' at %p\n", nameCopy, (void*)current->name);
            free(current->name);
        }

        // Free the dynamically allocated age and log the action
        if (current->age != NULL) {
            printf("[FREE] Age   '%s' at %p\n", nameCopy, (void*)current->age);
            free(current->age);
        }

        // Free the struct itself and log the action
        printf("[FREE] Person '%s' struct at %p\n", nameCopy, (void*)current);
        free(current);

        free(nameCopy); // Free the duplicated name

        current = next;  // Move to the next person in the list
    }

    // Print closing separator
    printf("-----------------------------------------------------------------------------\n");
}



void printPersons(Person *head) {
    Person *current = head;
    while (current != NULL) {
        printf("Name: %s, Age: %d\n", current->name, *(current->age));
        current = current->next;
    }
}

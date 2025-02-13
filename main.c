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
Person* addPerson(Person *head, const char *name, const int *age) {
    // Allocate memory for the new person structure
    Person *newPerson = (Person*) malloc(sizeof(Person)); 
    if (newPerson == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for person struct\n");
        exit(EXIT_FAILURE); 
    }
    printf("\nAllocated person struct at location: %p\n", (void*)newPerson);

    // Allocate memory for the person's name
    newPerson->name = (char*) malloc((strlen(name) + 1) * sizeof(char)); 
    if (newPerson->name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for name\n");
        free(newPerson); // Clean up already allocated person struct before exiting
        exit(EXIT_FAILURE); 
    }
    strcpy(newPerson->name, name); // Copy name into the newly allocated memory
    printf("Allocated name at location: %p\n", (void*)newPerson->name);

    // Allocate memory for the person's age
    newPerson->age = (int*) malloc(sizeof(int)); 
    if (newPerson->age == NULL) {
        fprintf(stderr, "Error: Memory allocation for age failed\n");
        free(newPerson->name); // Clean up name allocation
        free(newPerson); // Clean up person struct allocation
        exit(EXIT_FAILURE); 
    }
    *(newPerson->age) = *age; // Dereference age pointer and assign it to allocated memory
    printf("Allocated age at location: %p\n", (void*)newPerson->age);

    newPerson->next = NULL; // Initialize the next pointer to NULL

    // Check if the linked list is empty, if so, the new person becomes the head
    if (head == NULL) {
    printf("First person added to the linked list\n\n");  // Print message for the first person added
    return newPerson;  // The first person added becomes the head of the list
} else {
    // Otherwise, append the new person to the end of the list
    Person *current = head;
    while (current->next != NULL) {
        current = current->next;  // Traverse to the end of the list
    }
    current->next = newPerson;  // Append the new person
}
printf("Person added to the linked list\n\n");  // Confirmation message for every person added
return head;  // Return the head of the list

}













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

void printPersons(Person *head) {
    Person *current = head;
    while (current != NULL) {
        printf("Name: %s, Age: %d\n", current->name, *(current->age));
        current = current->next;
    }
}

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


void freePersons(Person *head) {
    Person *current = head;
    while (current != NULL) {
        Person *next = current->next; // Save the next person before freeing memory

        // Log and free the name
        if (current->name != NULL) {
            printf("Freeing name structure at location: %p\n", (void*)current->name);
            free(current->name);
        }

        // Log and free the age
        if (current->age != NULL) {
            printf("Freeing age structure at location: %p\n", (void*)current->age);
            free(current->age);
        }

        // Log and free the person structure
        printf("Freeing person structure at location: %p\n", (void*)current);
        free(current);

        // Move to the next person in the list
        current = next;
    }
}



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
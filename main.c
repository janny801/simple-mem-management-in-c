//simple memory management system 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct Person
{
    //dynamically allocated ptrs 
    char *name; 
    int *age; 
}Person; 

//function prototypes (used for best prac-- defined later)
Person* allocatePerson(const char *name, const int *age); //allocate memory for a person and initializes it
void freePerson(Person *person); //frees all allocated memory for a person
void printPerson(Person * person); //prints details of a person



int main()
{
    //main

    int capacity = 10; //initial capacity for the array of person pointers
    int count =0; 
    Person **persons = malloc(capacity *sizeof(Person*)); //array of pointers to person structs
    if (persons ==NULL)
    {
        fprintf(stderr, "failed to allocate memory for persons array.\n");
        exit(EXIT_FAILURE); 
    }

    while(1) //loop to take in person names and ages for input 
    {   
        char nameBuffer[100]; 
        int age; 
        printf("enter a name (or type 'done' to finish):  "); 
        scanf("%99s", nameBuffer); //read up to 99 chars 
        if(strcmp(nameBuffer, "done") ==0) break; //exit loop if 'done' is entered 

        printf("enter an age: "); 
        scanf("%d", &age); //store age 

        //check if array needs to be expanded based on capacity var (originally 10 ppl )
        if(count >= capacity) 
        {
            capacity +=1; //increase capacity by one if needed
            persons = realloc(persons, capacity * sizeof(Person*)); 
            if(persons ==NULL)
            {
                fprintf(stderr, "failed to reallocate memory for persons array.\n"); 
                exit(EXIT_FAILURE); 
            }
        }
        //allocate memory for a new person and initialize with the user input
        persons[count++] = allocatePerson(nameBuffer, &age); 
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

     */




   //print details of the allocated person 
   printPerson(person); 

   //free dynamically allocated memory to avoid memory leaks
   freePerson(person); 

   return 0; //prog ends
    



}


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


//need to define other funtions inorder for compilation proper

//free and print functions for allocation of person

//function to free all dynamically allocated memory for a person 

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

//func to print details of the person 

void printPerson( Person *person)
{
    if(person!=NULL)
    {
        printf("Name: %s, Age: %d\n", person->name, *(person->age)); // Print the name and the value of age 

    }
}





/*
notes
strings decay to char* 

each name is a string of char* in memory?

dereference; access or retrieve the value stored 
at the memory address a pointer is pointing to 



*/
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

    char nameBuffer[100]; //temp array to hold user input for name
    int age; //temp variable to hold user input for age 


    printf("enter a name: "); 
    scanf("%99s", nameBuffer); //read up to 99 char(prevent overflow)
    //dont need to use &nameBuffer since array naturally
    //decay to string in c


    //prompt the user to enter an age
    printf("enter an age: "); 
    scanf("%d", &age); //store age 






}
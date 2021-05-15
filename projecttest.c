//Tobias Lennon
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Student struct.
typedef struct student{
    char *name;
    char initial;
    char *surname;
    int year;
    char *course;
    char group;
    int average;
}Student;

//Node struct.
typedef struct node{
    Student *data;
    struct node *next;
}Node;

//Global head.
Node *head = NULL;

//Method takes Student struct and linked list head and instantiates a new node to be added to the linked list containing the student struct.
Node *addNode(Student *data, Node *head){
    Node *currentNode = head;
    Node *newNode;
    //Traverses until at end of list.
    while ( currentNode != NULL && currentNode->next != NULL) {
    currentNode = currentNode->next;
    }
    //Allocates space for Node.
    newNode = malloc(sizeof(Node));
    //Sets the payload.
    newNode->data = data;
    newNode->next = NULL;
    if (currentNode != NULL){
        currentNode->next = newNode;
    }
    else {
        head = newNode;
    }
    //Returns new head.
    return head;
}
//Traverses each node and prints data.
void printDB(Node *head){
    Node *currentNode = head;
    while(currentNode != NULL){
        printf("%s %c %s %d %s %c %d\n", currentNode->data->name, currentNode->data->initial, currentNode->data->surname, currentNode->data->year, currentNode->data->course, currentNode->data->group, currentNode->data->average);
        currentNode = currentNode->next;
    }
}
//My fscanf implementation.
int my_fscanf(FILE *fp, char *formatString, Node *listNode){
    int res = 0;
    char c, tempString[50] = {'\0'}, tempChar;
    int i = 0, j = 0, k, l, tempIntArray[50], tempInt = 0;

    Student *student;
    student = malloc(sizeof(Student));

    //Looping through format string.
    for (i = 0; i < strlen(formatString); i++){
        if(formatString[i] == '%'){
            switch (formatString[i + 1]){
                case 'c':
                     while(1){
                        c = getc(fp);
                        if(c == ' ' || c == '\n'){
                            res += 1;
                            break;
                        }
                        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                            tempChar = c;
                        }
                        if(c == EOF){
                            break;
                        }
                    }

                    break;

                case 'd':

                    while(1){
                        c = getc(fp);
                        if(c == ' ' || c == '\n'){
                            res += 1;
                            break;
                        }
                        //Checks if char is not a digit.
                        if (c < '0' || c > '9'){
                            printf("\nError, character '%c' where int expected.", c);
                            break;
                        }
                        //Converts char to int and stores in int array.
                        tempIntArray[j] = c - '0';

                        j++;
                        //Handling EOF
                        if(c == EOF){
                            printf("End of file reached");
                            break;
                        }
                    }
                    //Takes all ints from array and turns it into one integer.
                    for (l = 0; l < j; l++){
                        tempInt = 10 * tempInt + tempIntArray[l];
                    }

                    j = 0;
                    break;

                case 's':

                    while(1){
                        c = getc(fp);
                        if(c == ' ' || c == '\n'){
                            res += 1;
                            j = 0;
                            break;
                        }
                        tempString[j] = c;
                        j++;

                        if(c == EOF){
                            printf("\nEnd of file reached");
                            break;
                        }
                    }

                    break;

                default:
                    printf("Format string formatted incorrectly.");
                    break;
            }

            //Switch case uses res(matched results) to correspond to student param.
            switch(res){
                case 1: 
                    //Allocating memeory for dynamic string length.
                    student->name = malloc(strlen(tempString));
                    strcpy(student->name, tempString);
                    break;
                case 2:
                    student->initial = tempChar;
                    break;    
                case 3:
                    student->surname = malloc(strlen(tempString));
                    strcpy(student->surname, tempString);
                case 4:
                    student->year = tempInt;
                    break;    
                case 5:
                    student->course = malloc(strlen(tempString));
                    strcpy(student->course, tempString);
                    break;
                case 6:
                    student->group = tempChar;
                    break;
                case 7:
                    student->average = tempInt;
                    break;
            }
            

            //Resetting tempName and tempInt.
            memset(tempString, 0, sizeof(tempString));
            tempInt = 0;
        }
    }
    
    if (student->surname != NULL){
        head = addNode(student, head);
    }
    return res;
}

void main(int argc, char *argv[]){
    int i = 0, m = 0;
    char a[255];
    //If no command line argument given.
    if (argc == 1){
        printf("Please enter a command line argument argument.");
    }
    else {
        //Declaring file pointer.
        FILE *fp;
        //Opening file passed through command line argument.
        fp = fopen(argv[1], "r");
        //If file not found.
        if (!fp){
            printf("File not found.");
        }
    
        while ((i = my_fscanf(fp, "%s (%c) %s %d %s %c %d", head)) == 7){
            m += 1;
        }

        printf("\n%d students added to the database.", m);
        
        printf("\n\n-------- Printing Student Database --------\n\n");
        //Printing the student database.
        printDB(head);

        //Closing file.
        fclose(fp);
    }
}
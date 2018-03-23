// A complete working C program to implement a student data system using linked list
//Minh Nguyen Nhat  -  17089544  -  EEE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//     ******  STARTING OF LINKED LIST PART  ******

//  [LINKED LIST]  Declaring a structure for a student
struct Student{
  char name[50];    //Don't change size of name array!!!!
  int id;
  float marks[5];
  struct Student *next;
};

//  [LINKED LIST]  1.0) Function for introducing a new student into the linked list in alphabetical order
void Introduce_student(char student_name[], int id, struct Student** head_ref){

    //Allocating memory for a new student node
    struct Student* new_student = (struct Student*) malloc(sizeof(struct Student));
    //We copy the name and ID parameters into the name and ID of the student
    strcpy(new_student->name, student_name);
    new_student->id = id;

    //For traversing throught the list, we use two nodes next to each other moving them forward simultaniously
    //pointer to the previous student in the linked list
    struct Student* previous = (struct Student*)malloc(sizeof(struct Student));
    previous = NULL;
    //pointer to the current student in the linked list
    struct Student* current = (struct Student*)malloc(sizeof(struct Student));
    current = *head_ref;

    //Looping through the students until the name of the current is alphabetically 'bigger' then the one we want to insert
    while(NULL != current && strcmp(student_name, current->name)>0){
        previous = current;
        current = current->next;
    }
    //Insert at beginning of linked list
    if(NULL == previous){
        new_student->next = current;
        *head_ref = new_student;
    }
    //Insert between previous and current node
    else{
        previous->next = new_student;
        new_student->next = current;
    }
    //Initially, set marks for all modules to 0
    int i;
    for(i=0; i<5; i++){
        new_student->marks[i] = 0;
    }
}

//  [LINKED LIST]  1.1) Function for searching for a student with a given ID and see if it exists
int searchID(struct Student **head_ref, int key){
    struct Student* temp = *head_ref;
    int flag = 0;

    //Looping through all the students and search for the ID
    while(temp != NULL){
        if(temp->id == key){
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    /*If we found that the ID is already existing we return 1; if the ID doesn't exist yet, return 1 */
    if(flag == 1){
        return 1;}
    else{
        return 0;}
}

//  [LINKED LIST]  2) Function for deleting a student
void deleteStudent(struct Student **head_ref, int key){
    struct Student* temp = *head_ref, *prev;

    //If the first node cointains the student we want to delete
    if(temp != NULL && temp->id == key){
        *head_ref = temp->next;
        free(temp);
        return;
    }

    //Looping throught the students until we find the one that needs to be deleted
    while (temp != NULL && temp->id != key){
        prev = temp;
        temp = temp->next;
    }

    //If the student we want to delete is not in the linked list
    if (temp == NULL){
        printf("There is no student in the list with that ID.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
}

//  [LINKED LIST]  3.0) Function for introducing marks for a specific student we searched for
void marks(struct Student *student){
    printf("Insert the student marks!\n");

    //Declaring variables for looping and inserting marks
    int i;
    float mark;

    //Loop through each module (element) in the marks array and inserting a mark
    for( i=0; i<5; i++){
        printf("Insert the mark for the %d module!\n",i+1);
        scanf("%f",&mark);
        student->marks[i] = mark;
    }
}

//  [LINKED LIST]  3.1) Function for searching for a student we want to introduce marks for
void introMarks(struct Student **head_ref, int key){
    int flag = 0;
    struct Student* current = *head_ref;

    //Traversing through all the students until we find the one we want to introduce marks to
    while(current != NULL){
        //If we found it, stop looking further
        if(current->id == key){
            marks(current);
            flag = 1;
            break;
        }
        //If we haven't found it look further
        else{
            current = current->next;
        }
    }
    //Flag being 0 means we looked through all nodes but didn't find the student we want
    if(flag == 0){
        printf("\nThere is no student with that id!\n");
    }
}

//  [LINKED LIST]  4) Function for searching a student and print information about him/her
void searchPrint(struct Student **head_ref, int key){
    int i, flag = 0;
    struct Student* current = *head_ref;

    //Looping through all students and search for the one we want
    while(current != NULL){
        //If we found the one, print all the information and stop searching
        if(current->id == key){
            printf("\n----------------\n");
            printf("Name:   %s\n", current->name);
            printf("Student ID: %d \n", current->id);
            for(i=0; i<5; i++){
                printf("Module %d:  %f \n", i+1, current->marks[i]);
            }
            printf("\n");
           flag = 1;
           break;
        }
        //Search further until we found the one
        else{
            current = current->next;
        }
    }
    //If none of them is the one, the searched student is not in the linked list
    if(flag == 0){
        printf("There is no student with that id!\n");
    }
}

//  [LINKED LIST]  5) Function to print out all information of every student
void printAll(struct Student *node){
    int i;
    printf("Report of all students:\n\n");

    //Print all information about students until we reach the end
    while(node != NULL){
        printf("\n----------------\n");
        printf("Name:   %s\n", node->name);
        printf("Student ID: %d\n", node->id);
        for(i=0; i<5; i++){
            printf("Module %d:   %f\n", i+1, node->marks[i]);
        }
        node = node->next;
    }
}

//  [LINKED LIST]  6) Function to save data of all students to a binary file
void SavetoFile(struct Student *head_ref){
    //Open a file for writing data into it in binary
    FILE * pFile = fopen("studentdata.bin", "wb");

    //If we opened the file successfully
    if(pFile != NULL){
        struct Student* temp = head_ref;
        //Declaring a struct to hold the pointer to next student and initially set it to NULL
        struct Student* holdNext = NULL;

        //Looping through the whole linked list and writing all data in the node to the file in binary except the pointer to next node
        while(temp != NULL){
            //We don't want to save the pointer to next, so we store it in 'holdNext' and set 'temp->next' to NULL
            //This way we don't loose the pointer but we also can exclude it from being saved
            holdNext = temp->next;
            temp->next = NULL;

            //Write the data from the struct to the opened file
            fseek(pFile, 0, SEEK_END);
            fwrite(temp, sizeof(struct Student), 1, pFile);

            //Print out every student we successfully saved
            printf("\nSaving %s to file\n", temp->name);
            //After we saved the struct, we can put back the pointer value from 'holdNext' into 'temp->next'
            temp->next = holdNext;
            holdNext = NULL;
            //Continue the traversing through the list
            temp = temp->next;
        }
        fclose(pFile);
    }
    //If we could not open the file
    else{printf("FILE OPENING ERROR FOR WRITE\n");}
}

//  [LINKED LIST]  7.0) Function to save data from linked list to a file
struct Student* ReadNextFromFile(struct Student* head_ref, FILE* pFile){
    size_t returnValue;
    if(head_ref == NULL){
        head_ref = (struct Student*)malloc(sizeof(struct Student));
        returnValue = fread(head_ref, sizeof(struct Student), 1, pFile);
        head_ref->next = NULL;
    }
    else{
        struct Student* temp1 = head_ref;
        struct Student* temp2 = (struct Student*)malloc(sizeof(struct Student));
        while(temp1->next != NULL){
            temp1 = temp1->next;
        }
        returnValue = fread(temp2, sizeof(struct Student), 1, pFile);
        temp1->next = temp2;
        temp2->next = NULL;
    }
    return head_ref;
}

//  [LINKED LIST]  7.1) Function for retrieving student data from a file
struct Student* RetrieveFromFile(struct Student *head_ref){

    FILE * pFile = fopen("studentdata.bin", "rb");

    if(pFile != NULL){
        head_ref = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numStudents = (int)(fileSize/(sizeof(struct Student)));
        printf("Number of students contained in the file: %d", numStudents);

        int i;
        for( i=0;i < numStudents; i++){
           fseek(pFile, (sizeof(struct Student) * i), SEEK_SET);
            head_ref = ReadNextFromFile(head_ref, pFile);
       }
   }
    else{printf("FILE OPNEING ERROR FOR READ\n");}
    return head_ref;
}

//     ******  STARTING OF BINARY TREE PART  ******

//  [BINARY TREE]  Declaring a struct for binary tree implementation
struct BstStudent{
    char name[50];
    int id;
    float marks[5];
    struct BstStudent* left;
    struct BstStudent* right;
};

//  [BINARY TREE]  1) Function for inserting a student into the binary tree
void Bst_IntroduceStudent(struct BstStudent** root, char student_name[], int student_id){
    //Allocating memory and declaring the previous and current node
    struct BstStudent* new_student = (struct BstStudent*)malloc(sizeof(struct BstStudent));
    struct BstStudent* current = *root;
    struct BstStudent* previous = NULL;
    int i;

    //Declare the name, ID, marks and left/right pointers for the node, based on user input function parameters
    strcpy(new_student->name, student_name);
    new_student->id = student_id;
    new_student->left = NULL;
    new_student->right = NULL;
    for(i=0; i<5; i++){
        new_student->marks[i] = 0;
    }

    //Check if the tree is empty or not
    if(*root == NULL){
        //If the tree is empty, we make the student the root node
        *root = new_student;
    }
    else{
        //If not empty, go through the tree until we find the right spot for the student
        while(current != NULL){
            //Go left if name of new student is before the current in alphabetical order
            if(strcmp(current->name, new_student->name) > 0){
                previous = current;
                current = current->left;
            }
            //Go right if name is after current in the alphabet
            else if(strcmp(current->name, new_student->name) < 0){
                previous = current;
                current = current->right;
            }
            //If we found the same name then don't let the user to insert the same name twice; delete the new student
            else if(strcmp(current->name, new_student->name) == 0){
                printf("\n** A student with that name already exists! **\n");
                free(new_student);
                return;
            }
        }
        //If we found the right node after which we want to place the student, decide if place right or left
        if(strcmp(previous->name, new_student->name) > 0){
            previous->left = new_student;
        }
        else{
            previous->right = new_student;
        }
    }
}

//  [BINARY TREE]  2) Function for deleting a student from the binary tree
void Bst_DeleteStudent(struct BstStudent** root, char student_name[]){
    //Declaring current node and parent node of current
    struct BstStudent* current = *root;
    struct BstStudent* parent = NULL;
    int flag = 0;
    int i;

    //We loop through the list and search for the student we want to delete
    while(current != NULL){
        //Go left if the name of deleting student is before current in alphabet
        if(strcmp(current->name, student_name) > 0){
            parent = current;
            current = current->left;
        }
        //Go right if the name of deleting student is after current in alphabet
        else if(strcmp(current->name, student_name) < 0){
            parent = current;
            current = current->right;
        }
        //Run if we found the student we want to delete
        else{
            flag = 1;
            //If node has no children
            if(current->left == NULL && current->right == NULL){
                //If the node we delete is not the root
                if(parent != NULL){
                    if(parent->left == current){
                        parent->left = NULL;
                    }
                    else{
                        parent->right = NULL;
                    }
                    free(current);
                }
                //If the node we delete is the root
                else if(parent == NULL){
                    *root = NULL;
                    free(*root);
                }
                return;
            }
            //If node has one child
            else if((current->left == NULL && current->right != NULL) || (current->left != NULL && current->right == NULL)){
                //If the node we delete is not the root
                if(parent != NULL){
                    //If node has a right child
                    if(current->right != NULL && current->left == NULL){
                        //If the node is right child
                        if(parent->right == current){
                            parent->right = current->right;
                        }
                        //If the node is a left child
                        else if(parent->left == current){
                            parent->left = current->right;
                        }
                    }
                    //If node has a left child
                    else if(current->left != NULL && current->right == NULL){
                        //The node is a right child
                        if(parent->right == current){
                            parent->right = current->left;
                        }
                        //The node is a left child
                        else if(parent->left == current){
                            parent->left = current->left;
                        }
                    }
                    free(current);
                }
                //If the node we delete is the root
                else if(parent == NULL){
                    struct BstStudent* delPtr = *root;
                    //If root has a left child
                    if(current->left != NULL && current->right == NULL){
                        *root = (*root)->left;
                    }
                    //If root has a right child
                    else if(current->right != NULL && current->left == NULL){
                        *root = (*root)->right;
                    }
                    free(delPtr);
                }
                return;
            }
            //If current has two children
            else{
                struct BstStudent* swap_this = current->right;
                struct BstStudent* swap_this_prev = current;
                //Search for the minimum node in the right subtree of the node we want to remove
                while(swap_this->left != NULL){
                    swap_this_prev = swap_this;
                    swap_this = swap_this->left;
                }
                //Copy all information from minimum node to the one we want to delete
                //By doing this, we removed the node we want to but created two of the same 'swap_this' minimum node
                strcpy(current->name, swap_this->name);
                current->id = swap_this->id;
                for(i=0; i<5; i++){
                    current->marks[i] = swap_this->marks[i];
                }

                //Disconnecting the minimum node
                //If the minimum node is a left child
                if(swap_this_prev->left == swap_this){
                    swap_this_prev->left = swap_this->right;
                }
                //If the minimum node is a right child
                else if(swap_this_prev->right == swap_this){
                    swap_this_prev->right = swap_this->right;
                }
                //We don't need additional if-else statements because the minimum node cannot have a left child

                free(swap_this);
                return;
            }
        }
    }
    if(flag == 0){
        printf("\nStudent named '%s' removed\n", student_name);
    }
    else{
        printf("\nNo student named '%s' is found in the list!\n", student_name);
    }
}

//  [BINARY TREE]  3.0) Function for introducing marks for a specific student
void Bst_Marks(struct BstStudent *student){
    printf("Insert the student marks!\n");
    //Declaring variables for looping and inserting marks
    int i;
    float mark;

    //Loop through each module (element) in the marks array and inserting a mark
    for( i=0; i<5; i++){
        printf("Insert the mark for the %d module!\n",i+1);
        scanf("%f",&mark);
        student->marks[i] = mark;
    }
}

//  [BINARY TREE]  3.1) Function for searching a student we want to introduce marks for
void Bst_IntroMarks(struct BstStudent* root, char student_name[]){
    struct BstStudent* current = root;
    int flag = 0;

    //Looping throught the tree iteratively to find the student we want
    while(current != NULL){
        if(strcmp(current->name, student_name) > 0){
            current = current->left;
        }
        else if(strcmp(current->name, student_name) < 0){
            current = current->right;
        }
        //If the name matches and we found it call the function for introducing the actual marks and break the searching
        else{
            Bst_Marks(current);
            flag = 1;
            break;
        }
    }
    //If no student found
    if(flag == 0){
        printf("\nThere is no student named: %s\n", student_name);
    }
}

//  [BINARY TREE]  4) Function for searching for a student and print out all the data about him/her
void Bst_SearchPrint(struct BstStudent* root, char student_name[]){
    struct BstStudent* current = root;
    int i, flag = 0;

    //Looping through the tree and look for the student we want to print the info out
    while(current != NULL){
        //If searched name is before the current one in the alphabet go left
        if(strcmp(current->name, student_name) > 0){
            current = current->left;
        }
        //If searched name is after the current one in the alphabet go right
        else if(strcmp(current->name, student_name) < 0){
            current = current->right;
        }
        //If we found the searched student, print the info out
        else{
            printf("\n----------------\n");
            printf("Name:   %s\n", current->name);
            printf("Student ID: %d\n", current->id);
            for(i=0; i<5; i++){
                printf("Module %d:   %f\n", i+1, current->marks[i]);
            }
            flag = 1;
            break;
        }
    }
    if(flag == 0){
        printf("\nThere is no student named: %s\n", student_name);
    }
}

//  [BINARY TREE]  5) Function for printing out all the data about all the students
void Bst_PrintAll(struct BstStudent** root){
    struct BstStudent* temp = *root;
    int i;

    //Loop through the tree recursively
    if(temp == NULL){
        //If we reached the end, escape function from recursion
        return;
    }
    else{
        //Print all info about the student
        Bst_PrintAll(&temp->left);
        printf("\n----------------\n");
        printf("Name:   %s\n", temp->name);
        printf("Student ID: %d\n", temp->id);
        for(i=0; i<5; i++){
            printf("Module %d:   %f\n", i+1, temp->marks[i]);
        }
        Bst_PrintAll(&temp->right);
    }
}

//  [BINARY TREE]  Function for rotating left a node in the tree
void leftRotateBinary(struct BstStudent** current){
    //Declaring nodes we want to operate with
    struct BstStudent* temp;
    struct BstStudent* original;
    struct BstStudent* right;

    //If the node we want to operate a left rotate on is NULL or doesn't have a right child
    if(*current == NULL || (*current)->right == NULL){
        return;
    }

    original = *current;
    right = original->right;

    //Create a new node and copy the content of the 'original' node into it
    temp = (struct BstStudent*)malloc(sizeof(struct BstStudent));
    int i;
    strcpy(temp->name, original->name);
    temp->id = original->id;
    for(i=0; i<5; i++){
        temp->marks[i] = original->marks[i];
    }

    //Copy the content of 'right' node into the 'original' one
    strcpy(original->name,right->name);
    original->id = right->id;
    for(i=0; i<5; i++){
        original->marks[i] = right->marks[i];
    }

    //Perform the rotation, disconnect the right node and connect the newly created node
    temp->right = right->left;
    temp->left = original->left;
    original->right = right->right;
    original->left = temp;
    //Delete the 'right' node
    free(right);
}

//  [BINARY TREE]  Function for rotating a node right in the tree
void rightRotateBinary(struct BstStudent** current){
    //Declaring nodes we want to operate with
    struct BstStudent* temp;
    struct BstStudent* original;
    struct BstStudent *left;

    //If the node we want to operate a right rotate on is NULL or doesn't have a left child
    if(*current == NULL || (*current)->left == NULL){
        return;
    }

    original = *current;
    left = original->left;

    //Create a new node and copy the content of the 'original' node into it
    temp = (struct BstStudent*)malloc(sizeof(struct BstStudent));
    int i;
    strcpy(temp->name, original->name);
    temp->id = original->id;
    for(i=0; i<5; i++){
        temp->marks[i] = original->marks[i];
    }

    //Copy the content of 'left' node into the 'original' one
    strcpy(original->name, left->name);
    original->id = left->id;
    for(i=0; i<5; i++){
        original->marks[i] = left->marks[i];
    }

    //Perform the rotation, disconnect the 'left' node and connect the newly created node
    temp->left = left->right;
    temp->right = original->right;
    original->left = left->left;
    original->right = temp;

    //Delete the 'left' node
    free(left);
}

//  [BINARY TREE]  Function for balancing the tree using DSW algorithm
void balanceBinary(struct BstStudent **root){
    struct BstStudent* current = *root;
    int expected, i, odd_node;
    int num_nodes = 0;

    //Creating a straight backbone of nodes by right rotating every node that has a left child
    //Every node only has a right child
    while(current != NULL){
        while(current->left != NULL){
            rightRotateBinary(&current);
        }
        current = current->right;
        //Calculate how many nodes are there
        num_nodes++;
    }

    //Calculate how many nodes we expect at the bottom level
    expected = num_nodes - (pow(2,(floor(log2(num_nodes+1)))) - 1);
    current = *root;

    for(i=0; i<expected; i++){
        leftRotateBinary(&current);
        current = current->right;
    }

    //Rotate all odd nodes along the binary tree
    current = *root;
    num_nodes = num_nodes - expected;
    odd_node = (num_nodes+1)/2;
    while(odd_node > 1){
        //Rotates the root node left
        leftRotateBinary(&(*root));

        for(i=0; i<(odd_node-1); i++){
            leftRotateBinary(&(current->right));
            current = current->right;
        }
        //Increments odd nodes
        odd_node = (odd_node+1)/2;
    }
}

//Main
int main(int argc, char* argv[]){
    int a;
    //Only start the program if the user enters a second command for choosing data structure
    if(argc > 1){
        if(strcmp(argv[1],"linkedlist") == 0){
            //Declare the headnode of an empty linked list
            struct Student* head_node = NULL;

            //Declare all the variables needed for the program
            int user_choice;
            char new_name[100];
            int new_ID, marks_ID, report_ID;
            int delete_ID;
            int exit = 0;

            //Keep displaying the menu until the user decides to quit the program
            do{
                //Purge input if the user inputs an invalid character
                fpurge(stdin);
                //Main menu
                printf("\nManage data for students: (Type an option and press ENTER)\n");
                printf("1) Introduce new student:\n");
                printf("2) Remove student:\n");
                printf("3) Introduce marks for a student:\n");
                printf("4) Print report for a student:\n");
                printf("5) Print report for all students:\n");
                printf("6) Save to a file:\n");
                printf("7) Retrieve data from a file:\n");
                printf("8) Quit\n\n");

                //Ask the user to choose from the menu options above
                scanf("%d", &user_choice);

                switch(user_choice){
                    case 1:
                        //Option to exit within a user input prompt
                        printf("Do you want to proceed?\nPress 1 for yes, any other number for main menu\n");
                        scanf("%d", &a);
                        if(a == 1){
                            //Ask the user for the name and ID of student he wants to introduce
                            printf("Insert the name of new student: \n");
                            scanf("%s", new_name);
                            printf("Insert the id of new student: \n");
                            scanf("%d", &new_ID);
                            //If the given ID doesn't exist, introduce the new student
                            if(searchID(&head_node, new_ID) == 0){
                                Introduce_student(new_name, new_ID, &head_node);
                            }
                            //Don't allow the user to introduce the student if the ID already exist
                            else{
                                printf("\nA student with that ID already exists!\n");
                            }
                        }
                        break;
                    case 2:
                        //Option to exit within a user input prompt
                        printf("Do you want to proceed?\nPress 1 for yes, any other number for main menu\n");
                        scanf("%d", &a);
                        if(a == 1){
                            //Ask user for the student he wants to remove
                            printf("Enter the ID of the student you wish to delete! \n");
                            scanf("%d", &delete_ID);
                            //Removing the student from the list
                            deleteStudent(&head_node, delete_ID);
                        }
                        break;
                    case 3:
                        printf("Do you want to leave?\nPress 1 for yes, any other number for main menu\n");
                        scanf("%d", &a);
                        if(a == 1){
                            //Ask user for which student he wants to introduce marks
                            printf("Insert the ID of the student you want to introduce marks for!\n");
                            scanf("%d", &marks_ID);
                            //Insert the marks
                            introMarks(&head_node, marks_ID);
                        }
                        break;
                    case 4:
                        //Ask the user which student's report want to be printed
                        printf("Insert the ID of the student you want to print a report!\n");
                        scanf("%d", &report_ID);
                        //Print the report for that student
                        searchPrint(&head_node, report_ID);
                        break;
                    case 5:
                        //Print report for all students
                        printAll(head_node);
                        break;
                    case 6:
                        SavetoFile(head_node);
                        break;
                    case 7:
                        head_node = RetrieveFromFile(head_node);
                        break;
                    case 8:
                        //Quit the program
                        printf("\nProgram ended!\n");
                        exit = 1;
                        break;
                    default:
                        printf("\nInvalid option!\n");
                }
            }
            while(exit != 1);
        }

        //If the user chooses binary tree
        else if(strcmp(argv[1],"binarytree") == 0){
            struct BstStudent* rootPtr = NULL;

            int user_choice2;
            char new_name[20], new_name2[20], marks_name[20], report_name[20], delete_name[20];
            int new_ID, new_ID2;
            int exit = 0;

            //Keep displaying the menu until the user decides to quit the program
            do{
                //Purge input if the user inputs an invalid character
                fpurge(stdin);
                //Main menu
                printf("\nManage data for students: (Type an option and press ENTER)\n");
                printf("1) Introduce new student:\n");
                printf("2) Remove student:\n");
                printf("3) Introduce marks for a student:\n");
                printf("4) Print report for a student:\n");
                printf("5) Print report for all students:\n");
                printf("6) Quit\n\n");

                //Ask the user to choose from the menu options above
                scanf("%d", &user_choice2);

                switch(user_choice2){
                    case 1:
                        //Option to exit within a user input prompt
                        printf("Do you want to proceed?\nPress 1 for yes, any other number for main menu\n");
                        scanf("%d", &a);
                        if(a == 1){
                            //Ask the user for the name and ID of student he wants to introduce
                            printf("Insert the name of new student: \n");
                            scanf("%s", new_name);
                            printf("Insert the id of new student: \n");
                            scanf("%d", &new_ID);
                            //Insert the student and balance the tree right away
                            Bst_IntroduceStudent(&rootPtr, new_name, new_ID);
                            balanceBinary(&rootPtr);
                        }
                        break;
                    case 2:
                        //Option to exit within a user input prompt
                        printf("Do you want to proceed?\nPress 1 for yes, any other number for main menu\n");
                        scanf("%d", &a);
                        if(a == 1){
                            //Ask the user for name wanted to be deleted
                            printf("Insert the name of student you want to remove: \n");
                            scanf("%s", delete_name);
                            //Delete student and balance the tree
                            Bst_DeleteStudent(&rootPtr, delete_name);
                            balanceBinary(&rootPtr);
                        }
                        break;
                    case 3:
                        //Option to exit within a user input prompt
                        printf("Do you want to proceed?\nPress 1 for yes, any other number for main menu\n");
                        scanf("%d", &a);
                        if(a == 1){
                            printf("Insert the ID of the student you want to introduce marks for!\n");
                            scanf("%s", marks_name);
                            //Insert the marks
                            Bst_IntroMarks(rootPtr, marks_name);
                        }
                        break;
                    case 4:
                        //Ask the user which student's report want to be printed
                        printf("Insert the ID of the student you want to print a report!\n");
                        scanf("%s", report_name);
                        //Print the report for that student
                        Bst_SearchPrint(rootPtr, report_name);
                        break;
                    case 5:
                        printf("Print report of all students:\n\n");
                        Bst_PrintAll(&rootPtr);
                        break;
                    case 6:
                        //Quit the program
                        printf("\nProgram ended!\n");
                        exit = 1;
                        break;
                    default:
                        printf("\nInvalid option!\n");
                }
            }
            while(exit == 0);
        }
        //If the second command is invalid
        else{
            printf("\nRun the program again!\n");
            printf("Type 'linkedlist' in command line as the second command for using linked list as data structure\n");
            printf("Type 'binarytree' in command line as the second command for using binary tree as data structure\n\n");
        }
    }
    //If the user doesn't type a second command
    else{
        printf("\nRun the program again!\n");
        printf("Type 'linkedlist' in command line as the second command for using linked list as data structure\n");
        printf("Type 'binarytree' in command line as the second command for using binary tree as data structure\n\n");
    }
    return 0;
}

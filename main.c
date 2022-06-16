#include <stdio.h>
#include <stdlib.h>

struct Supervisor{
    char name [255];
    char staffID[7];
    char contactNo [15];
};

struct Student{
    char name [255];
    char stdID [7];
    struct Supervisor supervisor;
};

struct PTA{
    struct Student student;
    char PTATitle [255];
};

struct Progress{
    struct PTA pta;
    char startTime[100];
    char endTime[100];
    char discussionDetails [255];
    int week;
    char platform [100];
    char svFeedback [100];

    struct Progress *nextNode;
}
*top = NULL;

struct Progress *newProgress;

//functions
struct PTA EnterDetails(struct Student, struct PTA);
void DisplayDetails(struct PTA);
void AddProgress();
void DisplayProgress();
void RemoveProgress();
void SearchProgress();

int main(void) {
    //Structure references
    struct Student student;
    struct PTA pta;
    struct Progress progress;

    int choice;

    printf("### Welcome to FYP Logbook ###\n");

    pta = EnterDetails(student, pta);

    do {
        //Menu List
        printf("\n\n\t1. Modify student details\n");
        printf("\t2. Display student details\n");
        printf("\t3. Enter new progress\n");
        printf("\t4. List all progress\n");
        printf("\t5. Remove progress\n");
        printf("\t6. Search progress\n");
        printf("\t7. Exit\n");

        printf("Enter a choice: ");
        scanf("%d", &choice);

        switch(choice) {
          case 1:
                printf("Editing...\n");
                pta = EnterDetails(student, pta);
                break;
          case 2:
                printf("Retrieving data\n");
                DisplayDetails(pta);
                break;
          case 3:
                printf("In progress\n");
                AddProgress();
                break;
          case 4:
                printf("Retrieving data...\n");
                DisplayProgress();
                break;
          case 5:
                printf("Removing data...\n");
                RemoveProgress();
                break;
          case 6:
                printf("Searching...\n");
                SearchProgress();
                break;
          case 7:
                break;
          default:
                printf("\nPlease choose a valid option!\n");
                break;
        }
    }while(choice != 7);

    return 0;
}

struct PTA EnterDetails(struct Student student, struct PTA pta){
    fflush(stdin);
    printf("\nEnter your name: ");
    scanf("%[^\n]", &student.name);
    fflush(stdin);
    printf("\nEnter your student id: ");
    scanf("%s", &student.stdID);
    fflush(stdin);
    printf("\nEnter your supervisor name: ");
    scanf("%s", &student.supervisor.name);
    fflush(stdin);
    printf("\nEnter your supervisor staff ID: ");
    scanf("%s", &student.supervisor.staffID);
    fflush(stdin);
    printf("\nEnter your supervisor contact no: ");
    scanf("%s", &student.supervisor.contactNo);
    fflush(stdin);
    printf("\nEnter your PTA title: ");
    scanf("%s", &pta.PTATitle);
    pta.student = student;
    return pta;
}

void DisplayDetails(struct PTA pta){
    fflush(stdout);
    printf("\nStudent name: %s", pta.student.name);
    fflush(stdout);
    printf("\nStudent ID: %s", pta.student.stdID);
    fflush(stdout);
    printf("\nSupervisor name: %s", pta.student.supervisor.name);
    fflush(stdout);
    printf("\nSupervisor ID: %s", pta.student.supervisor.staffID);
    fflush(stdout);
    printf("\nSupervisor contact: %s", pta.student.supervisor.contactNo);
    return;
}

void AddProgress(){
    //allocate memory
    newProgress = (struct Progress*) malloc(sizeof(struct Progress));
    //user input
    printf("\nWeek: ");
    scanf("%d", &newProgress->week);
    printf("Enter start time: ");
    scanf("%s", &newProgress->startTime);
    printf("Enter end time: ");
    scanf("%s", &newProgress->endTime);
    fflush(stdin);
    printf("Enter discussion details: ");
    scanf("%[^\n]", &newProgress->discussionDetails);
    printf("Enter platform used: ");
    scanf("%s", &newProgress->platform);
    fflush(stdin);
    printf("Enter your supervisor's feedback: ");
    scanf("%[^\n]", &newProgress->svFeedback);

    if(newProgress == NULL){
        printf("\nAN ERROR HAS OCCURRED"); //STACK OVERFLOW
        exit(1);
    }

    newProgress->nextNode=top;
    top=newProgress;
    return;
}

void RemoveProgress(){
    struct Progress *delProgress;

    int choice;

    //Choices
    printf("\n\t1. Delete specific progress");
    printf("\n\t2. Delete recent progress.");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if(choice == 1) {

        DisplayProgress();
        printf("\nPlease enter which progress you want to delete: ");
        scanf("%d", &choice);

        struct Progress *temp;
        struct Progress *prev;

        temp = top;
        //If stack/progress is empty
        if(temp==NULL){
            printf("\nNo existing progress\n");
            return;
        }

        int count = 1;

        //Traverse the list
        while(temp){
            //Find the linked list of choice
            if(count==choice){
                if(choice == 1) {
                    //If the choice is the first node, set the Head to next node address
                    top = temp->nextNode;
                    //Delete/Deallocate the first node
                    free(temp);
                } else {
                    //Reassign the previous node's address to the next in list
                    prev->nextNode = temp->nextNode; // [(1)] -> [Choice to delete(2)] -> [(3)] Reassign 1's nextNode to 3's address
                    //Delete/Deallocate the node of choice
                    free(temp);
                }
            }
            //Assign previous to current node
            prev = temp;
            //Traverse to next node
            temp=temp->nextNode;
            count++;
        }


    } else if(choice == 2) {

        //Pop operation
        if(top ==NULL) {
        printf("\nNo existing progress\n");
        }
        else {
        delProgress = top;
        top = delProgress->nextNode;
        free(delProgress);
        }

    } else {
        printf("\nInvalid choice!");
        return;
    }

    return;
}


void DisplayProgress(){
    struct Progress *temp;
    temp = top;
    if(temp==NULL){
        printf("\nNo existing progress\n");
        return;
    }

    int count = 1;

    while(temp){
        printf("\n\t-------------- [ %d ] --------------", count);
        printf("\n\tWeek: %d",temp->week);
        printf("\n\tStart time: %s",temp->startTime);
        printf("\n\tEnd time: %s",temp->endTime);
        printf("\n\tDiscussion details: %s",temp->discussionDetails);
        printf("\n\tPlatform: %s",temp->platform);
        printf("\n\tSupervisor's feedback: %s\n",temp->svFeedback);
        temp=temp->nextNode;
        count++;
    }
    return;
}

void SearchProgress(){
    int searchKey;
    struct Progress *temp;
    temp = top;
    printf("\nEnter week: ");
    scanf("%d", &searchKey);
    if(temp==0){
        printf("\nThere is no existing progress stored!");
        return;
    }
    else{
        int flag = 0;
        while(temp){
            if(temp->week == searchKey){
                printf("\n\tWeek: %d",temp->week);
                printf("\n\tStart time: %s",temp->startTime);
                printf("\n\tEnd time: %s",temp->endTime);
                printf("\n\tDiscussion details: %s",temp->discussionDetails);
                printf("\n\tPlatform: %s",temp->platform);
                printf("\n\tSupervisor's feedback: %s\n",temp->svFeedback);
                flag = 1;
            }
            temp=temp->nextNode;
        }
        if(flag == 0) {
            printf("\nNo results found!\n");
        }
    }

    return;
}

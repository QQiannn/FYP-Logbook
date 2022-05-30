#include <stdio.h>
#include <time.h>

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
    time_t startTime;
    time_t endTime;
    char discussionDetails [255];
    char date [100];
};

int main(void) {
  
    
  return 0;
}
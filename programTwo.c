/*
 * Sara Hrnciar
 * Program 2
 * Operating Systems
 * replicates process tracing
 */

#include<stdio.h>
#include<string.h>
#include <malloc.h>
#include <time.h>
int num; //DEFINE GLOBALS
int processesFinished;
int runs;
struct Process{ //PROCESS STRUCT
    int pid;
    char processName[10];
    int priority;
    int runTime;
    int elapsedTime;
};

int findHighestPrioritysIndex(struct Process pList[]){ //FINDS HIGHEST PRIORITY
    int highestP = 1;

    if (num>highestP) { //IF THE LIST IS BIG ENOUGH TO SEARCH THRU
        for (int i = highestP+1; i <= num; i++) {
            if ((pList[highestP].priority > pList[i].priority) & (pList[i].runTime - pList[i].elapsedTime >0)){ //CHANGE HIGHESTP IF U FIND A HIGHER PRIORITY PROCESS WHICH ISNT FINISHED
                highestP = i;
            }
        }
        if ((highestP==1)&(pList[1].priority == 50)){ //JUST TO MAKE SURE UR NOT TOTALLY DONE
            return 0;
        }
    }
    return highestP;
}

int main(void) {
    processesFinished = 0;
    struct Process pList[10]; //ASK ABT THIS, IF 10 IS OK
    num=1; //REPS NUMBER OF PROCESSES (INCLUDING DISPATCHER)
    int pid = 1000;
    int priority;
    char name[10];
    int pTime;
    int compare; //JUST FOR INITIAL LOOP ENTRY. IK IT GETS SHADOWED IN SCOPE, BUT IDC CUS IT WORKS.
    pList[0].pid = 6787; //DISPATCHER PID!
    strcpy(pList[0].processName,"DISPATCHER");
    pList[0].priority = 0;
    pList[0].runTime=3;
    srand(time(NULL)); //FOR RANDOM SEED
    while (compare != 0){ //TAKE INPUT UNTIL USER ENTERS Q (0 MEANS INPUT EQUALS Q)
        printf("Enter the process details: \n");
        scanf("%s", name);
        int compare = strcmp(name,"Q"); //CHECK IF IS Q
        if(compare==0){ //IF USER INPUT Q THEN BREAK
            break;
        }
        scanf("%d", &priority);
        scanf("%d", &pTime);
        pid = (rand()%3001) + 1000; //SAVE DETAILS TO PUT INTO PROCESS

        pList[num].pid = pid;
        strcpy(pList[num].processName,name);
        pList[num].priority = priority;
        pList[num].runTime = pTime;
        pList[num].elapsedTime = 0; //INPUT PROCESS DETAILS
        num++;
    }
    while(processesFinished!= num-1) { //WHILE YOU HAVENT FINISHED ALL PROCESSES
        int index = findHighestPrioritysIndex(pList); //find which process must run
        if (index == 0) { break; } //index 0 means theyre all done, just a safeguard
        runs = 5; //bc process must run for 5

        while (runs > 0) {
            printf("%s          %d %d %d\n", pList[index].processName, pList[index].pid, pList[index].priority,
                   (pList[index].runTime - pList[index].elapsedTime));
            runs -= 1; //BC YOU COMPLETED A RUN
            pList[index].elapsedTime += 1; //SO YOU RAN IT FOR A SECOND
            if (pList[index].runTime - pList[index].elapsedTime <= 0) {
                pList[index].priority = 50; //MAKE SURE UR NOT DONE
                processesFinished += 1; //IF U R THEN NOTE THAT U FINISHED AND STOP RUNNING THE PROCESS
                break;
            }
        }
        for (int i = 3; i >= 0; i--) { //DISPATCHER TIME!!!
            printf("%s          %d %d %d\n", pList[0].processName, pList[0].pid, pList[0].priority, i);
        }
        for (int i = 0; i < num; i++) { //INCREASE PRIORITY OF THE OTHER PROCESSES BESIDES U, UNLESS PROCESS IS ALR AT HIGHEST PRIORITY OR IS FINISHED
            if ((i != index) & (pList[i].priority > 0 & pList[i].priority!=50)) {
                pList[i].priority--;
            }
        }
    }
    return 0;
}

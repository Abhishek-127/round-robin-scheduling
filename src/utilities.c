#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

void readCmdLine(int argc, char **argv, char *filename, bool *detailedMode, bool *verboseMode, bool *rrMode, int *quantumMode){

    if(argc == 0){
        return;
    }

for(int x = 0; x < argc; x++){

    if(strcmp(argv[x], "-d") == 0){
        *detailedMode = true;
    }
    else if(strcmp(argv[x], "-v") == 0){
        *verboseMode = true;
    }
    else if(strcmp(argv[x], "-r") == 0){
        *rrMode = true; 
    }
    else{
        *quantumMode = atoi(argv[x]);
    }
}

// set the filename;
strncpy(filename, argv[argc-1], strlen(argv[argc-1] ) + 2);


}
//****************************************************************************************
Thread* createThread(){
    Thread *thread = calloc(1, sizeof(Thread));
    thread->threadID = 0;
    thread->arrival_time = 0;
    thread->number_of_CPU = 0;
    thread->cpu = initializeList(printCPU_BURST, deleteCPU_BURST, compareCPU_BURST);

    return thread;
}
void deleteThread(void *toBeDeleted){
    if(toBeDeleted == NULL){
        return;
    }
    Thread *thread = (Thread*)toBeDeleted;
    clearList(&thread->cpu);

    free(thread);
}
char *printThread(void *toBePrinted){
    if(toBePrinted == NULL){
        return NULL;
    }
    char *str = calloc(1000, sizeof(char));
    return str;
}
int compareThread(const void *first, const void *second){
    return 0;
}

//************************************************************************************************************************


//**********************************************************************************************************************
CPU_Burst* createCPU_BURST(){
    CPU_Burst *burst = calloc(1, sizeof(CPU_Burst));
    burst->cpu_time = 0;
    burst->io_time = 0;

    return burst;
}
void deleteCPU_BURST(void *toBeDeleted){
    if(toBeDeleted == NULL){
        return;
    }

    CPU_Burst *burst = (CPU_Burst*)toBeDeleted;

    free(burst);
}
char *printCPU_BURST(void *toBePrinted){
    if(toBePrinted == NULL){
        return NULL;
    }
    char *str = calloc(100, sizeof(char));
    return str;
}
int compareCPU_BURST(const void *first, const void *second){
    return 0;
}

//************************************************************************************************************************


//*******************************************************************************************************************

Process *createProcess(){
    
    Process *process = calloc(1, sizeof(Process));
    process->process_id = 0;
    process->number_of_threads = 0;
    process->thread = initializeList(printThread, deleteThread, compareThread);


    process->total_service_time = 0;
    process->total_IO_time = 0;
    process->turnaround_time = 0;
    process->finish_time = 0;
    process->finalTime = 0;
    process->wasteTime = 0;
    process->total_cpu_time = 0;
    process->switch_time = 0;

    return process;
}
void deleteProcess(void *toBeDeleted){
    if(toBeDeleted == NULL){
        return;
    }
    Process *process = (Process*)toBeDeleted;
    clearList(&process->thread);
    free(process);
}
char *printProcess(void *toBePrinted){

    if(toBePrinted == NULL){
        return NULL;
    }

    char *str = calloc(100, sizeof(char));
    return str;
}
int compareProcess(const void *first, const void *second){

    return 0;
}



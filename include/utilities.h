#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>
#include <string.h>
#include "LinkedListAPI.h"

// typedef struct{


// }

typedef struct{
    int threadID;
	int arrival_time;
	int number_of_CPU;
    List cpu;		
}Thread;

Thread* createThread();
void deleteThread(void *toBeDeleted);
char *printThread(void *toBePrinted);
int compareThread(const void *first, const void *second);


typedef struct {
	int cpu_time;
	int io_time;
}CPU_Burst;

CPU_Burst* createCPU_BURST();
void deleteCPU_BURST(void *toBeDeleted);
char *printCPU_BURST(void *toBePrinted);
int compareCPU_BURST(const void *first, const void *second);



typedef struct{
	int process_id;
	int number_of_threads;
	List thread;


	int total_service_time;
    int total_IO_time;
    int turnaround_time;
    int finish_time;
    int finalTime;
	int wasteTime;
    int total_cpu_time;
    int switch_time;
}Process;

Process *createProcess();
void deleteProcess(void *toBeDeleted);
char *printProcess(void *toBePrinted);
int compareProcess(const void *first, const void *second);


void readCmdLine(int argc, char **argv, char *filename, bool *detailedMode, bool *verboseMode, bool *rrMode, int *quantumMode);



#endif
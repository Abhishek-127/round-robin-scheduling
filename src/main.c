#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "utilities.h"
#include "LinkedListAPI.h"

int FinalCompletion = 0;
int FinalWaste = 0;
double CPUUU = 0.0;
int AverageTURN = 0;
int TotalArrival = 0;

int main(int argc, char *argv[]){

    bool *detailedMode;
    bool *verboseMode;
    bool *rrMode;
    int *quantumMode;

    detailedMode = calloc(1, sizeof(bool));
    verboseMode = calloc(1, sizeof(bool));
    rrMode = calloc(1, sizeof(bool));
    quantumMode = calloc(1, sizeof(int*));

    *detailedMode = false;
    *verboseMode = false;
    *rrMode = false;
    *quantumMode = 0;

    int TotalProcess = 0;
    int ThreadSwitch = 0;
    int ProcessSwitch = 0;
    int ProcessCount = 0;
    int ThreadCount = 0;
    int CPUCount = 0;
    int garbage = 0;

    // ints to do the calulations;
    int total_service_time = 0;
    int total_IO_time = 0;
    //int turnaround_time = 0;
   // int finish_time = 0;
    int finalTime = 0;
    int wasteTime = 0;

    int total_cpu_time = 0;
    int switch_time = 0;
    int AThread = 0;

    List MyList = initializeList(printProcess, deleteProcess, compareProcess);

    int total_time = 0;

    char *filename = calloc(250, sizeof(char));
    readCmdLine(argc, argv, filename, detailedMode, verboseMode, rrMode, quantumMode);


    fscanf(stdin, "%d %d %d", &TotalProcess, &ThreadSwitch, &ProcessSwitch);
    finalTime = finalTime + (ThreadSwitch * TotalProcess);
    wasteTime = wasteTime + (TotalProcess * ProcessSwitch);
    switch_time += ProcessSwitch;
    while(ProcessCount < TotalProcess){
        
        Process *processStruct = createProcess();
        processStruct->finalTime = finalTime;//added
        processStruct->wasteTime = wasteTime;
        processStruct->switch_time = switch_time;//added
        finalTime = finalTime + (ThreadSwitch * TotalProcess);
        wasteTime = wasteTime + (TotalProcess * ProcessSwitch);
        switch_time += ProcessSwitch;
 
        //
        fscanf(stdin, "%d %d", &processStruct->process_id, &processStruct->number_of_threads);
        int x = processStruct->number_of_threads;
        
        processStruct->wasteTime = processStruct->wasteTime + (ThreadSwitch * x);
        processStruct->finalTime = processStruct->finalTime + (ThreadSwitch * x);

        ThreadCount = 0;

        while(ThreadCount < processStruct->number_of_threads){

            AThread++;
            Thread *threadStruct = createThread();
            fscanf(stdin, "%d %d %d", &threadStruct->threadID, &threadStruct->arrival_time, &threadStruct->number_of_CPU);
            CPUCount = 0;
            while(CPUCount < (threadStruct->number_of_CPU - 1)){

                CPU_Burst *CPUStruct = createCPU_BURST();

                fscanf(stdin, "%d %d %d", &garbage, &CPUStruct->cpu_time, &CPUStruct->io_time);
                //printf("CPU Time: %d IO Time: %d\n", CPUStruct->cpu_time, CPUStruct->io_time);
                total_IO_time += CPUStruct->io_time;
                total_cpu_time += CPUStruct->cpu_time;
                processStruct->total_IO_time += CPUStruct->io_time;//
                processStruct->total_cpu_time += CPUStruct->cpu_time;//

                
                insertBack(&threadStruct->cpu, CPUStruct);

                if(CPUCount + 1 == (threadStruct->number_of_CPU - 1)){
                    
                    int save = 0;
                    CPU_Burst *CPUStruct = createCPU_BURST();

                    fscanf(stdin, "%d %d", &garbage, &CPUStruct->cpu_time);
                    CPUStruct->io_time = save;

                    // adding here;
                    total_service_time += CPUStruct->cpu_time;
                    processStruct->total_service_time += CPUStruct->cpu_time;

                    //printf("CPU Time: %d IO Time: %d\n", CPUStruct->cpu_time, CPUStruct->io_time);

                    insertBack(&threadStruct->cpu, CPUStruct);
                }
                CPUCount++;
            }
            ThreadCount++;
            insertBack(&processStruct->thread, threadStruct);
        }
        ProcessCount++;
        insertBack(&MyList, processStruct);
    }

    // Node;
    Node *node = MyList.head;
    while(node != NULL){
        Process *p = node->data;
        wasteTime += p->wasteTime;
        finalTime += p->finalTime;

        node = node->next;
    }

  // printf("%d %d\n", finalTime, wasteTime);


    Node *potato = MyList.head;  // Potato means Processes 
    
    int temp_io  = 0;
    int temp_service_time = 0;
    //int total_time =  0;

    while(potato != NULL){ //You are iterating through a list of process structs not potato
        //Process *p = (Process*)potato->data;

      
       FinalCompletion = finalTime;
       FinalWaste = wasteTime;

        Node *Mythreads = ((Process*)potato->data)->thread.head;
        if(*detailedMode == true){
            printf("Process: %d Number of Threads: %d\n", ((Process*)(potato->data))->process_id, ((Process*)(potato->data))->number_of_threads);
        }
        while(Mythreads != NULL){
            

            Node *MyCPU = ((Thread*)Mythreads->data)->cpu.head;
        if(*detailedMode == true){
            printf("Thread: %d Arrival Time: %d Number of CPU: %d\n", ((Thread*)(Mythreads->data))->threadID, ((Thread*)(Mythreads->data))->arrival_time, ((Thread*)(Mythreads->data))->number_of_CPU);
        }
            TotalArrival = TotalArrival + ((Thread*)Mythreads->data)->arrival_time;
            while(MyCPU != NULL){

                    temp_io += ((CPU_Burst*)MyCPU->data)->io_time; 
                    temp_service_time += ((CPU_Burst*)MyCPU->data)->cpu_time;
                    total_time  +=((CPU_Burst*)MyCPU->data)->io_time;
                    total_time  += ((CPU_Burst*)MyCPU->data)->cpu_time;
                if(*detailedMode == true){
                    printf("CPU Time: %d    I/O Time: %d\n", ((CPU_Burst*)MyCPU->data)->cpu_time, ((CPU_Burst*)MyCPU->data)->io_time);
                    
                    
                }
                MyCPU = MyCPU->next;
                
            }
            if(*detailedMode == true){
               // printf("IO %d     Service Time: %d \n", temp_io, temp_service_time);
                printf("IO: %d \t service Time: %d\n",temp_io, temp_service_time);
                printf("Finish: %d\n", (temp_io + temp_service_time)/4 );

            }
            temp_io = 0;
            temp_service_time = 0;
            if(*detailedMode == true){
                printf("\n\n");
            }
            Mythreads = Mythreads->next;
        }
        
        potato = potato->next;
        
    }



        int parth = total_cpu_time + total_IO_time + ThreadSwitch + ProcessSwitch;
        int avgParth = parth - TotalArrival;
        int turnParth = avgParth/AThread;
       // AverageTURN = (wasteTime + FinalCompletion + TotalArrival);
        CPUUU = total_time - wasteTime;
        CPUUU = (CPUUU/(float)total_time) * 100;



        printf("Total Time Required Is: %d\n", (total_time));
        printf("Average TurnAround Time Is: %d\n", turnParth);
        printf("CPU Utilization Is %.2lf%%\n", CPUUU);



    return 0;
}
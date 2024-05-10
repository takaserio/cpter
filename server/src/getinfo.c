#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../../lib/infomation.h"

void getcpu_name(char *cpu_name) {
    FILE *file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) {
        printf("ERROR: opening file");
        exit(0);
    }

    // keep reading lines from the file until you encounter the line containing the CPU name
    for (int i = 0; i < 5; i++) {
        fgets(cpu_name, 255, file);
    }

    // exchange first \n for \0
    int index = 0;
    while (1) {
        if (cpu_name[index] == '\n') {
            cpu_name[index] = '\0';
            break;
        }

        index++;
    }

    fclose(file);
}

//int getcpu_temperture() {}

void getmemory_total(char *memory_total) {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        printf("ERROR: opening file");
        exit(0);
    }

    // keep reading lines from the file until you encounter the line containing the CPU name
    for (int i = 0; i < 1; i++) {
        fgets(memory_total, 255, file);
    }

    // exchange first \n for \0
    int index = 0;
    while (1) {
        if (memory_total[index] == '\n') {
            memory_total[index] = '\0';
            break;
        }

        index++;
    }
}

void getmemory_usage(char *memory_usage) {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        printf("ERROR: opening file");
        exit(0);
    }

    // keep reading lines from the file until you encounter the line containing the CPU name
    for (int i = 0; i < 7; i++) {
        fgets(memory_usage, 255, file);
    }

    // exchange first \n for \0
    int index = 0;
    while (1) {
        if (memory_usage[index] == '\n') {
            memory_usage[index] = '\0';
            break;
        }

        index++;
    }
}

void getcpu(struct Cpu *cpu) {
    getcpu_name(&cpu->cpu_name);
    //cpu->cpu_temperture = getcpu_temperture();
}

void getmemory(struct Memory *memory) {
    getmemory_total(&memory->mem_total);
    getmemory_usage(&memory->mem_usage);
}

// the function read all info defined in Info stract to its instance.
// basycally almost infomation is got from /pros.
void getinfo(struct Info *info) {
    getcpu(&info->cpu);
    getmemory(&info->memory);
}
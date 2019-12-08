/*
omp_tokenizer.c

A tool which tokenizes the words in multiple files, using OpenMP
author: Philippe Nadon
date: Nov 29, 2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <time.h> 
#include "queue.h"

#define NUM_FILES 4
#define QUEUE_SIZE 256
#define MAX_FNAME 16
#define TOKEN_SEPARATOR ' '

Queue queues[NUM_FILES];

void produce_to_queue(int my_rank, char fname[]) {
    FILE *file_pointer = NULL;
    int idx = 0;
    file_pointer = fopen(fname, "r");
    char c;
    printf("PRODUCING FROM THREAD %d\n", omp_get_thread_num());
    while ((c = fgetc(file_pointer)) != EOF && idx < QUEUE_SIZE)
    {
        insert(&queues[my_rank], c);
        idx++;
        if(idx == QUEUE_SIZE) {
            printf("WARNING: THREAD %d REACHED QUEUE_SIZE!\n", my_rank);
        }
    }
    if(idx != QUEUE_SIZE) {
        insert(&queues[my_rank], EOF);
    }
}

void consume_from_queue(int my_rank, char fname[]) {
    FILE *file_pointer = NULL;
    int idx = 0;
    char c;
    file_pointer = fopen(fname, "w+");
    printf("CONSUMING FROM THREAD %d\n", omp_get_thread_num());
    while ((c = pop(&queues[my_rank])) != EOF && idx < QUEUE_SIZE) {
        if( c == TOKEN_SEPARATOR) {
            fprintf(file_pointer, "\n");
        } else {
            fprintf(file_pointer, "%c", c);
        }
        idx++;
        if(idx == QUEUE_SIZE) {
            printf("WARNING: THREAD %d REACHED QUEUE_SIZE!\n", my_rank);
        } else while (isEmpty(&queues[my_rank]));
    }
}

int main() {
    clock_t seconds = clock();
    // double start_time = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp for schedule(static) nowait
        for( int i = 0; i < NUM_FILES; i++) {
            initializeQueue(&queues[i]);
            char fname[16];
            sprintf(fname, "./texts/%d.txt", i);
            produce_to_queue(i, fname);
        }
        #pragma omp for schedule(static)
        for( int i = 0; i < NUM_FILES; i++) {
            char fname[16];
            sprintf(fname, "./output/%d.txt", i);
            consume_from_queue(i, fname);
        }
    }
    // printf("\n\ntime: %lf\n", omp_get_wtime() - start_time);
    printf("\n\ntime: %f\n", (double)(clock() - seconds) / CLOCKS_PER_SEC);
}
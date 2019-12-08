/*
queue.h

A library which implements a queue
author: Philippe Nadon
date: Nov 29, 2019
*/

#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE 2048
#define MAX_LINE 256
#define MAX_QUEUES 4

typedef struct {
    char array[MAX_QUEUE][MAX_LINE];
    int front;
    int rear;
    int num_items;
    int max;
    bool in_use;
} Queue;

typedef struct {
   Queue array[MAX_QUEUES];
   int jobs_left;
} Queues;

void initializeQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->num_items = 0;
    queue->max = MAX_QUEUE;
    queue->in_use = false;
}

void initializeQueues(Queues *queues, int num_jobs) {
   for(int i = 0; i < MAX_QUEUES; i++) {
      initializeQueue(&queues->array[i]);
   }
   queues->jobs_left = num_jobs;
}

bool isInUse(Queue *queue) {
   return queue->in_use;
}

bool occupyQueue(Queue *queue) {
   if(!isInUse(queue)) {
      queue->in_use = true;
      return true;
   } else {
      return false;
   }
}

void leaveQueue(Queue *queue) {
   queue->in_use = false;
}

void peek(Queue *queue, char *res) {
   strcpy(res, queue->array[queue->front++]);
}

bool isEmpty(Queue *queue) {
   return queue->num_items == 0;
}

bool isFull(Queue *queue) {
   return queue->num_items == queue->max;
}

int size(Queue *queue) {
   return queue->num_items;
}  

void insert(Queue *queue, char* data) {

   if(!isFull(queue)) {
	
      if(queue->rear == queue->max-1) {
         queue->rear = -1;            
      }       

      strcpy(queue->array[++queue->rear], data);
      queue->num_items++;
   }
}

int pop(Queue *queue, char* res) {
   strcpy(res, queue->array[queue->front++]);
	
   if(queue->front == queue->max) {
      queue->front = 0;
   }
	
   queue->num_items--; 
   return queue->num_items;
}

#endif

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

#define MAX_QUEUE 256

typedef struct {
    char array[MAX_QUEUE];
    int front;
    int rear;
    int num_items;
    int max;
} Queue;

void initializeQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->num_items = 0;
    queue->max = MAX_QUEUE;
}

char peek(Queue *queue) {
   return queue->array[queue->front];
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

void insert(Queue *queue, char data) {

   if(!isFull(queue)) {
	
      if(queue->rear == queue->max-1) {
         queue->rear = -1;            
      }       

      queue->array[++queue->rear] = data;
      queue->num_items++;
   }
}

char pop(Queue *queue) {
   char data = queue->array[queue->front++];
	
   if(queue->front == queue->max) {
      queue->front = 0;
   }
	
   queue->num_items--;
   return data;  
}

#endif

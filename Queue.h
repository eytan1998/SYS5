
#ifndef SYS5_QUEUE_H
#define SYS5_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node,*PNode;

typedef struct Queue {
    PNode head;
    PNode tail;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} Queue,*PQueue;

PQueue createQueue();
void enqueue(PQueue queue, void* data);
void* dequeue(PQueue queue);
void freeQueue(PQueue queue);

#endif //SYS5_QUEUE_H

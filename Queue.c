
#include "Queue.h"

PQueue createQueue() {
    PQueue queue = (PQueue)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return queue;
}

void enqueue(PQueue queue, void* data) {


    PNode newNode = (PNode)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    pthread_mutex_lock(&queue->lock);

    if (queue->tail == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->lock);
}

void* dequeue(PQueue  queue) {
    pthread_mutex_lock(&queue->lock);

    while (queue->head == NULL) {
        pthread_cond_wait(&queue->cond, &queue->lock);
    }

    PNode temp = queue->head;
    void* data = temp->data;

    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(temp);

    pthread_mutex_unlock(&queue->lock);

    return data;
}

void freeQueue(PQueue queue) {
    pthread_mutex_lock(&queue->lock);

    PNode current = queue->head;
    while (current != NULL) {
        PNode  temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    pthread_mutex_unlock(&queue->lock);
    pthread_mutex_destroy(&queue->lock);
    pthread_cond_destroy(&queue->cond);
    free(queue);
}

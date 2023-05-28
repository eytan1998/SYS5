

#ifndef SYS5_AO_H

#include "Queue.h"

typedef void (*handler_t)(void *data, void *ao);

typedef struct ActiveObject {
    PQueue queue;
    pthread_t thread;
    handler_t func;
    int untilFinish;
    struct ActiveObject *next;
} ActiveObject, *PAO;

PAO createActiveObject(handler_t func, int N, PAO next);

PQueue getQueue(PAO this);

void stop(PAO this);

#define SYS5_AO_H

#endif //SYS5_AO_H

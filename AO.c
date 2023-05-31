
#include "AO.h"

//thread function
void AO_function(PAO this) {
    while (this->untilFinish > 0) {
        void *data = dequeue(this->queue);
        this->func(data, this->next);
        this->untilFinish--;
    }
}

PAO createActiveObject(handler_t func, int N, PAO next) {
    PAO ao = (PAO) malloc(sizeof(ActiveObject));
    ao->queue = createQueue();
    ao->func = func;
    ao->untilFinish = N;
    ao->next = next;
    pthread_create(&ao->thread, NULL, (void *(*)(void *)) AO_function, ao);
    return ao;
}

PQueue getQueue(PAO this) {
    return this->queue;
}

void stop(PAO this) {
    //wait for loop to end (dont need)
    pthread_join(this->thread, NULL);
    //free all
    freeQueue(this->queue);
    free(this);

}

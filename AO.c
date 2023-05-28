
#include "AO.h"

void AO_function(PAO ao) {
    while (ao->untilFinish != 0) {
        void *data = dequeue(ao->queue);
        ao->func(data, ao->next);
        ao->untilFinish--;

    }
    stop(ao);

}

PAO createActiveObject(handler_t func, int N, PAO next) {
    PAO ao = (PAO) malloc(sizeof(ActiveObject));
    ao->queue = createQueue();
    ao->func = func;
    ao->untilFinish = N;
    ao->next = next;
    pthread_create(&ao->thread, NULL, (void *(*)(void *)) AO_function, ao);
    printf("create-------%p-------\n",&ao->thread);

    return ao;
}

PQueue getQueue(PAO this) {
    return this->queue;
}

void stop(PAO this) {
    printf("free-------%p-------\n",&this->thread);
    pthread_mutex_lock(&this->queue->lock);
    pthread_cond_broadcast(&this->queue->cond);
    pthread_mutex_unlock(&this->queue->lock);
    //wait for loop to end (dont need)
    pthread_join(this->thread, NULL);
    //free all
    pthread_mutex_destroy(&this->queue->lock);
    pthread_cond_destroy(&this->queue->cond);
    freeQueue(this->queue);
    free(this);

}

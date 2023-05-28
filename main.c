#include <stdio.h>
#include <unistd.h>
#include "AO.h"

#define FALSE 0
#define TRUE 1
#define ERROR 1

unsigned int isPrime(unsigned int num) {
    unsigned int i;

    // 0 and 1 are not prime numbers
    if (num < 2) {
        return FALSE;
    }

    // Check for divisibility from 2 to the square root of the number
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return FALSE;  // Not prime
        }
    }

    return TRUE;  // Prime
}


typedef struct AO1_Data {
    int N;
    unsigned int seed;
} AO1_Data, *PAO1_Data;

void AO1(void *data, PAO next_ao) {

    if (data == NULL)return;

    PAO1_Data pao1Data = (PAO1_Data) data;
    int randomNumber =0;
    srand(pao1Data->seed);
    for (int i = 0; i < pao1Data->N; ++i) {
        randomNumber = rand() % 900000 + 100000;
        int * ptr = (int*)malloc(sizeof(int));
        *ptr = randomNumber;

        enqueue(next_ao->queue, ptr);
        usleep(1);
    }
    free(pao1Data);

}

void AO2(void *data, PAO next_ao) {
    printf("AO2 ");

    if (data == NULL)return;

    int*  num = (int*)data;

    printf("%d\n", *num);
    printf((isPrime(*num) ? "true\n" : "false\n"));
    *num += 11;
    enqueue(next_ao->queue, (num));
}

void AO3(void *data, PAO next_ao) {
    printf("AO3 ");

    if (data == NULL)return;

    int* num = (int*)data;
    printf("%d\n", *num);
    printf((isPrime(*num) ? "true\n" : "false\n"));
    *num -= 13;
    enqueue(next_ao->queue, (num));
}

void AO4(void *data, PAO next_ao) {
    printf("AO4 ");

    if (data == NULL)return;

    int* num = (int*)data;
    printf("%d\n", *num);
    *num += 2;
    printf("%d\n", *num);
    free(data);

}

int main(int argc, char *argv[]) {
    PAO1_Data pao1 = malloc(sizeof(AO1_Data));
    pao1->N = 0;
    pao1->seed = time(NULL);
    if (argc == 2) {
        pao1->N = atoi(argv[1]);
    } else if (argc == 3) {
        pao1->N = atoi(argv[1]);
        pao1->seed = atoi(argv[2]);
    } else {
        printf("usage: ./st_pipeline <N> <seed>.\n");
        return ERROR;
    }

    PAO ao4 = createActiveObject((handler_t) AO4,pao1->N, NULL);
    PAO ao3 = createActiveObject((handler_t) AO3,pao1->N, ao4);
    PAO ao2 = createActiveObject((handler_t) AO2,pao1->N, ao3);
    PAO ao1 = createActiveObject((handler_t) AO1,1, ao2);
    enqueue(ao1->queue, pao1);


    //wait for last

    if(ao4 != NULL)
        pthread_join(ao4->thread,NULL);
    printf("%p",&ao3->thread);
    return 0;
}

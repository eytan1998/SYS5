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

    PAO1_Data initData = (PAO1_Data) data;
    int randomNumber;
    srand(initData->seed);
    for (int i = 0; i < initData->N; ++i) {
        randomNumber = rand() % 900000 + 100000;
        int *ptr = (int *) malloc(sizeof(int));
        *ptr = randomNumber;

        enqueue(next_ao->queue, ptr);
        usleep(1000);//1 ms
    }
    //no longer needed
    free(initData);

}

void AO2(void *data, PAO next_ao) {
    if (data == NULL)return;

    int *num = (int *) data;

    printf("%d\n%s\n", *num,(isPrime(*num) ? "true" : "false"));
    *num += 11;
    enqueue(next_ao->queue, (num));
}

void AO3(void *data, PAO next_ao) {

    if (data == NULL)return;

    int *num = (int *) data;
    printf("%d\n%s\n", *num,(isPrime(*num) ? "true" : "false"));
    *num -= 13;
    enqueue(next_ao->queue, (num));
}

void AO4(void *data, PAO next_ao) {

    if (data == NULL)return;

    int *num = (int *) data;
    printf("%d\n%s\n", *num,(isPrime(*num) ? "true" : "false"));
    *num += 2;
    printf("%d\n", *num);
    free(data);

}

int main(int argc, char *argv[]) {
    PAO1_Data init_data = malloc(sizeof(AO1_Data));
    init_data->N = 0;
    init_data->seed = time(NULL);
    if (argc == 2) {
        init_data->N = atoi(argv[1]);
    } else if (argc == 3) {
        init_data->N = atoi(argv[1]);
        init_data->seed = atoi(argv[2]);
    } else {
        printf("usage: ./st_pipeline <N> <seed>.\n");
        return ERROR;
    }


    PAO pao4 = createActiveObject((handler_t) AO4, init_data->N, NULL);
    PAO pao3 = createActiveObject((handler_t) AO3, init_data->N, pao4);
    PAO pao2 = createActiveObject((handler_t) AO2, init_data->N, pao3);
    PAO pao1 = createActiveObject((handler_t) AO1, 1, pao2);
    enqueue(pao1->queue, init_data);

    stop(pao1);
    stop(pao2);
    stop(pao3);
    stop(pao4);

    return 0;
}

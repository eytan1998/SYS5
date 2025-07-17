#How to install
    https://github.com/eytan1998/SYS5.git
    cd SYS5
    make all

#How to run
    to run the main() :
   ./st_pipeline <N> <seed(optional)>

    N- the amount of numbers that will be produced
    seed (optional) - seed for rand(for the production of the numbers),
                        default: seed = time(NULL)


    There are running examples in screenshots below.

#Program explain
    #Pipeline
    The pipeline use 4 active object;
    1. get two numbers (N,seed) and generate N rnd numbers with seed
    2. get num from queue, print, check if prime, add 11 and enqueue to next ao
    3. get num from queue, print, check if prime, sub 13 and enqueue to next ao
    2. get num from queue print, check if prime, add 2 and print (should be same num as beginning)

    #Active object

    typedef struct ActiveObject {
        PQueue queue;
        pthread_t thread;
        handler_t func;
        int untilFinish;
        struct ActiveObject *next;
    } ActiveObject, *PAO;

    Queue - can hold this* and thread safe,
                on top of that use cond to ensure to wait to value on dequeue.
    Func - the function the main is doing foreach data from the queue.
    untilFinish - to know how much till end thread-loop
    next - to know the next ao in line

/*
Գրեք C ծրագիր, որը զանգվածը բաժանում է հատվածների և 
յուրաքանչյուր հատվածը փոխանցում է առանձին thread-ի։ 
Յուրաքանչյուր thread պետք է գումարի իր հատվածի տարրերը
և թարմացնի գլոբալ գումարի փոփոխականը։
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREAD_COUNT 4

typedef struct Args{
    int* ptr;
    int end;
    int start;
} Args;

int global_sum = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* sum_elem(void*);

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9};

    pthread_t td[THREAD_COUNT];

    int size = (sizeof(arr)/sizeof(arr[0]));
    int part = size / THREAD_COUNT;

    Args array[THREAD_COUNT];

    for(int i = 0; i < THREAD_COUNT; ++i){
        
        array[i].ptr = arr;
        array[i].start = i * part;

        if(i == THREAD_COUNT - 1){
            array[i].end = size;
        }
        else{
            array[i].end = (i + 1) * part;
        }

        if(pthread_create(&td[i], NULL, sum_elem, (void*)&array[i]) != 0){
        printf("Error");
        }
    }

    for(int i = 0; i < THREAD_COUNT; ++i){
        pthread_join(td[i], NULL);
    }
    printf("Count of array is %d\n", global_sum);


    return 0;
}

void* sum_elem(void * arguments){
    Args* array = (Args*) arguments;
    int* arr = array->ptr;
    int start = array->start;
    int end = array->end;

    int local_sum = 0;

    for(int i = start; i < end; ++i){
        local_sum += arr[i];
    }

    pthread_mutex_lock(&mtx);
    global_sum += local_sum;
    pthread_mutex_unlock(&mtx);

    return NULL;
}

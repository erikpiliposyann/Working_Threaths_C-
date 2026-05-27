/*Գրել ծրագիր, որը ստեղծում է 2 thread, 
որոնք միաժամանակ աշխատելով տպում են զանգվածի անդամները 
ճիշտ հաջորդականությամբ։ Առաջինը տպում է միայն զույգ  ինդեքսներով 
էլեմենտները, երկրորդը՝  միայն կենտերը։
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define THREAD_COUNT 2

typedef struct Args{
    int* ptr;
    int size;
} Args;

int glob_stat = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* print_even(void*);
void* print_odd(void*);

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int size = (sizeof(arr)/sizeof(arr[0]));

    pthread_t td[THREAD_COUNT];

    Args array;
    array.ptr = arr;
    array.size = size;

    if(pthread_create(&td[0], NULL, print_even, (void*)&array) != 0){
        printf("Error");
    }
    if(pthread_create(&td[1], NULL,print_odd, (void*)&array) != 0){
        printf("Error");
    }
    
    for(int i = 0; i < THREAD_COUNT; ++i){
        pthread_join(td[i], NULL);
    }


    return 0;
} 

void *print_even(void * args){
    Args *array = (Args*)args;
    int *arr = array->ptr;
    int size = array->size;

    for(int i = 0; i < size; i += 2){

        pthread_mutex_lock(&mtx);

        if(glob_stat){
            pthread_cond_wait(&cond,&mtx);
        }
        printf("Even index %d\n", arr[i]);

        glob_stat = 1;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond);
    }
    return NULL;
}

void *print_odd(void * args){
    Args *array = (Args*)args;
    int *arr = array->ptr;
    int size = array->size;

    for(int i = 1; i < size; i += 2){
        pthread_mutex_lock(&mtx);

        if(!glob_stat){
            pthread_cond_wait(&cond,&mtx);
        }
        printf("Odd index %d\n", arr[i]);
        
        glob_stat = 0;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond);
    }
    return NULL;
}

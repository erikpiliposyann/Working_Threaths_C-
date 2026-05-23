/*
Գրել ծրագիր, որը կստեղծի 2 thread, 1-ին thread-ի կանչած 
ֆունկցիան դինամիկ հիշողությունից կվերցնի զանգված և կլցնի 
զանգվածի մեջ մինչև N-ը եղած բոլոր պարզ թվերը։ 
2-րդ thread-ը ստանալու է 1-ին thread-ում ստեղծված 
զանգվածը և կտպի էկրանին զանգվածի տարրերը, 
ինչպես նաև կազատի դինամիկ հիշողությունից վերցրած տարածքը։
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct array{
    int* ptr;
    int n;
    int count;
}Array;

int is_prime(int n){
    if(n == 0 || n == 1){
        return 0;
    }
    else if(n == 2){
        return 1;
    }

    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

void* prime_array(void* args){
    Array *array = (Array*)args;
    int *arr = array->ptr;
    int n = array->n;

    int index = 0;

    for(int i = 0; i < n; ++i){
        if (is_prime(i)){
            arr[index] = i;
            index++;
        }
    }
    array->count = index;
    pthread_exit(NULL);
}

void* print_array(void* args){
    Array *array = (Array*)args;
    int *arr = array->ptr;
    int count = array->count;

    for (int i = 0; i < count; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    pthread_exit(NULL);
}

int main(){
    pthread_t t1;
    pthread_t t2;

    Array array;

    printf("Input your number.");
    scanf("%d",&array.n);

    array.count = 0;

    int* arr = (int*) calloc(array.n, sizeof(int));
    array.ptr = arr;

    if(pthread_create(&t1, NULL, prime_array, &array) != 0){
        printf("Error");
    }

    pthread_join(t1, NULL);

    if(pthread_create(&t2, NULL, print_array, &array) != 0){
        printf("Error");
    }
    
    pthread_join(t2, NULL);

    return 0;
}

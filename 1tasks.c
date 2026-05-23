/*
Գրել ծրագիր, որի կատարման արդյունքում կստեղծվի 
thread և thread-ը կկանչի ֆունկցիա, որը որպես 
արգումենտ ստանալու է զանգված և չափ։ Ֆունկցիան
վերադարձնելու է զանգվածի տարրերից երրորդ մեծագույնը։ 
Ֆունկցիայի վերադարձված արժեքը տպել էկրանին։ 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct Array{
    int* ptr;
    int size;
}Array;

void* third_max(void* args){
    Array *array = (Array*)args;
    int *arr = array->ptr;
    int size = array->size;

    for(int i = 0; i < size-1; ++i){
        for(int j = 0; j < size-1-i; ++j){
            if(arr[j] < arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    if(size < 3){
        pthread_exit(NULL);
    }
    else{
        int *result = malloc(sizeof(int));
        *result = arr[2];
        pthread_exit(result);
    }
}

int main(){
    pthread_t td;

    int arr[6] = {7, 15, 3, 20, 10, 18};

    Array array;
    array.ptr = arr;
    array.size = 6;

    if(!pthread_create(&td , NULL, third_max, &array)){
        printf("Error");
    }
    
    int *res;

    pthread_join(td, (void**) &res);

    pthread_join(td, (void**) &res);

    if(res == NULL){
        printf("Third maximum does not exist\n");
    }
    else{
        printf("%d\n", *res);
        free(res);
    }

    return 0;
}

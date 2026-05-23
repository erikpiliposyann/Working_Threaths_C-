/*
Իրականացնել ծրագիր, որը ստեղծում է  N x N չափանի մատրից և 
արժեքավորում է այն։ Պետք է ստեղծել միաժամանակ աշխատող 4 t
hread-ներ, որոնցից յուրաքանչյուրը ունի առանձին ֆունկցիոնալություն.
Գտնում և տպում է մատրիցի մեծագույն արժեքը։
Գտնում և տպում է մատրիցի փոքրագույն արժեքը։
Տպում է մատրիցի  գլխավոր և երկրորդական անկյունագծերը (խաչաձև)։
Հաշվում և վերադարձնում է մատրիցի  արժեքների միջին թվաբանականը։
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* matrix_max_elem(void*);
void* matrix_min_elem(void*);
void* print_two_diagonal(void*);
void* average_of_nums(void*);

int n; 

int main(){


    printf("Input matrix size.\n");
    scanf("%i", &n);

    int** matrix = (int**) malloc(n * sizeof(int*));

    for(int i = 0; i < n; ++i){
        matrix[i] = (int*) malloc(n * sizeof(int));
    }
    printf("\nInput Matrix elements.\n");
    for (int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {	
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nMatrix\n");
    for (int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {	
            printf("%d ", matrix[i][j]);   
        }
        printf("\n");
    }

    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;
    
    if(pthread_create(&t1, NULL, matrix_max_elem, matrix) != 0){
        printf("Error");
    }
    if(pthread_create(&t2, NULL, matrix_min_elem, matrix) != 0){
        printf("Error");
    }
    if(pthread_create(&t3, NULL, print_two_diagonal, matrix) != 0){
        printf("Error");
    }
    if(pthread_create(&t4, NULL, average_of_nums, matrix) != 0){
        printf("Error");
    }
    
    double* res;
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, (void**)&res);

    if(res == NULL){
        printf("Third maximum does not exist\n");
    }
    else{
        printf("Average matrix is %.2lf\n", *res);
        free(res);
    }
    free(matrix);

    return 0;
}

void* matrix_max_elem(void* args){
    int** mtx = (int**) args;

    int max = mtx[0][0];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mtx[i][j] > max){
                max = mtx[i][j];
            }
        }
    }
    printf("Maximum number is: %d", max);
    pthread_exit(NULL);
}

void* matrix_min_elem(void* args){
    int** mtx = (int**) args;

    int min = mtx[0][0];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mtx[i][j] < min){
                min = mtx[i][j];
            }
        }
    }
    printf("\nMinimum number is: %d\n", min);
    pthread_exit(NULL);
}

void* print_two_diagonal(void* args){
    int** mtx = (int**) args;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j || i == n - j - 1){
                 printf("%d ", mtx[i][j]);
            }   
            else{
                printf("  ");
            }
        }
        printf("\n");
    }

    pthread_exit(NULL);
}

void* average_of_nums(void* args){
    int** mtx = (int**) args;

    int average = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            average += mtx[i][j];
        }
    }
    double* result = (double*) malloc(sizeof(double));
    *result = average / n;
    pthread_exit(result);
}

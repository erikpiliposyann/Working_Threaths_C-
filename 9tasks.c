/*
Օգտվողից կստանա ամբողջ թիվ n։
Կստեղծի երկու թրեդ․
Առաջին թրեդը կգրի զույգ թվերը 0-ից մինչև n ֆայլում, որի անունը կլինի even.txt։
Երկրորդ թրեդը կգրի կենտ թվերը 0-ից մինչև n ֆայլում, որի անունը կլինի odd.txt։
Յուրաքանչյուր թրեդ պետք է ֆայլի մեջ գրի միայն իր համար նախատեսված թվերը։
*/

#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>

void* wrinth_even(void*);
void* wrinth_odd(void*);



int main(){
    int n = 0;
    printf("Input your number.");
    scanf("%i", &n);

    pthread_t td1;
    pthread_t td2;

    if(pthread_create(&td1, NULL, wrinth_even, &n) != 0){
        printf("Error.");
    }
    if(pthread_create(&td2, NULL, wrinth_odd, &n) != 0){
        printf("Error.");
    }

    pthread_join(td1,NULL);
    pthread_join(td2,NULL);

    return 0;
}

void* wrinth_even(void* arg){
    int* x = (int*) arg;

    FILE* even = fopen("even.txt", "w");

    if(even == NULL) {
        printf("File doesn't open\n");
        exit(1);
    }

    for(int i = 0; i <= (*x); ++i){
        if(i % 2 == 0){
            fprintf(even, "%d ", i);
        }
    }   
    fclose(even);
    return NULL;
}

void* wrinth_odd(void* arg){
    int* x = (int*) arg;

    FILE* odd = fopen("odd.txt", "w");

    if(odd == NULL) {
        printf("File doesn't open\n");
        exit(1);
    }
    for(int i = 0; i <= (*x); ++i){
        if(i % 2 != 0){
            fprintf(odd, "%d ", i);
        }
    }   
    fclose(odd);
    return NULL;
}

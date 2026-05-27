/*
Գրել ծրագիր, որը․
Կունենա գլոբալ հաշվիչ (counter)՝ սկզբում 0։
Օգտվողից կստանա չորս ամբողջ թիվ՝
n1 և count1 առաջին թրեդի համար,
n2 և count2 երկրորդ թրեդի համար։
Առաջին թրեդը պետք է կատարի n1 քայլ, և յուրաքանչյուր քայլում հաշվիչը 
ավելացնի count1-ով։Երկրորդ թրեդը պետք է կատարի n2 քայլ, և
յուրաքանչյուր քայլում հաշվիչը ավելացնի count2-ով։
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int glob_count;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct Data{
    int n;
    int count;

}typedef Data;

void* increment_count(void*);

int main(){
    pthread_t td1, td2;

    Data d1, d2;

    printf("Input n1 and count1. ");
    scanf("%d %d", &d1.n, &d1.count);

    printf("Input n2 and count2. ");
    scanf("%d %d", &d2.n, &d2.count);

    if(pthread_create(&td1, NULL, increment_count, &d1) != 0){
        printf("Error.");
    }
    if(pthread_create(&td2, NULL, increment_count, &d2) != 0){
        printf("Error.");
    }

    pthread_join(td1,NULL);
    pthread_join(td2,NULL);
    
    printf("Count: %d\n", glob_count);
    return 0;
}

void* increment_count(void* Args){
    Data* data = (Data*) Args;
    int n = data->n;
    int count = data->count;

    for(int i = 0; i < n; ++i){
        pthread_mutex_lock(&mtx);
        glob_count += count;
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

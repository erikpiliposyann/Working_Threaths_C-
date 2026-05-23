/*
Ունենք գլոբալ 0-ով արժեքավորված փոփոխական, իրականացնել ծրագիր, 
որը յուրաքանչյուր thread֊ի միջոցով ավելացնում է փոփոխականի արժեքը 100֊ով։
Օգտագործելով mutex` վստահ եղեք, որ արդյունքը կլինի 100֊ի բազմապատիկ։ 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int glob = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* add_100_glob(void*);

int main(){
    pthread_t t1;
    pthread_t t2;

    if(pthread_create(&t1 , NULL, add_100_glob, NULL) != 0){
        printf("Error");
    }
    if(pthread_create(&t2 , NULL, add_100_glob, NULL) != 0){
        printf("Error");
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mtx);

    printf("glob = %d\n", glob);
    return 0;
}

void* add_100_glob(void* args){
    pthread_mutex_lock(&mtx);
    glob += 100;
    pthread_mutex_unlock(&mtx);

    pthread_exit(NULL);
}

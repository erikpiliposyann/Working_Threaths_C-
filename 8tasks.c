/*
Ծրագիրը պետք է հարցնի օգտվողից մի ամբողջ թիվ n. Ստեղծի թրեդ (thread), 
որը ստանում է այս թիվը որպես արգումենտ. Թրեդը պետք է տպի բոլոր զույգ թվերը 
0-ից մինչև n.
*/

#include <stdio.h>
#include <pthread.h>


void* print_evens(void*);

int main(){
    int n = 0;
    printf("Input your number.");
    scanf("%i", &n);

    pthread_t td;

    if(pthread_create(&td, NULL, print_evens, &n) != 0){
        printf("Error");
    }

    pthread_join(td,NULL);

    return 0;
}

void *print_evens(void * arg){
    int* x = (int*) arg;
    for(int i = 0; i <= (*x); ++i){
        if(i % 2 == 0){
            printf("%d ", i);
        }
    }
    printf("\n");
    return NULL;
}

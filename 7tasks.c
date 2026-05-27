/*
Գրել C֊ական ծրագիր, որը որպես մուտքային տվյալ ընդունում է 
ֆայլի անուն։Ստեղծում է երկու thread, որոնք պետք է աշխատեն 
հետևյալ կերպ. առաջին thread֊ը  պետք է կարդա ֆայլից մի տող, 
այն կոդավորի  և լցնի coded.txt  ֆայլի մեջ։Երկրորդ  thread֊ը 
պետք է coded.txt֊ից վերցնի կոդավորված տողը, ապակոդավորի 
և լցնի new_"your_input_name".txt ֆայլի մեջ։ 
Thread֊ները պետք է աշխատեն իրար հաջորդելով։ 
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024

char buf[BUFFSIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_encode = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_decode = PTHREAD_COND_INITIALIZER;

int ready = 0;
int done = 0;

void encode(char *str){
    for(int i = 0; str[i] != '\0'; i++)
        str[i]++;
}

void decode(char *str){
    for(int i = 0; str[i] != '\0'; i++)
        str[i]--;
}

void* encoder_thread(void* arg){
    char* filename = (char*)arg;

    FILE* fin = fopen(filename, "r");
    FILE* fcoded = fopen("coded.txt", "w");

    if(!fin || !fcoded){
        perror("encoder fopen");
        exit(1);
    }

    while(1){
        pthread_mutex_lock(&mutex);

        while(ready == 1)
            pthread_cond_wait(&can_encode, &mutex);

        if(fgets(buf, BUFFSIZE, fin) == NULL){
            done = 1;
            pthread_cond_signal(&can_decode);
            pthread_mutex_unlock(&mutex);
            break;
        }

        encode(buf);
        fputs(buf, fcoded);
        fflush(fcoded);

        ready = 1;

        pthread_cond_signal(&can_decode);
        pthread_mutex_unlock(&mutex);
    }

    fclose(fin);
    fclose(fcoded);
    return NULL;
}

void* decoder_thread(void* arg){
    char* filename = (char*)arg;

    FILE* fcoded = fopen("coded.txt", "r");
    FILE* fdecoded = fopen(filename, "w");

    if(!fcoded || !fdecoded){
        perror("decoder fopen");
        exit(1);
    }

    while(1){
        pthread_mutex_lock(&mutex);

        while(ready == 0 && done == 0)
            pthread_cond_wait(&can_decode, &mutex);

        if(done == 1 && ready == 0){
            pthread_mutex_unlock(&mutex);
            break;
        }

        if(fgets(buf, BUFFSIZE, fcoded) != NULL){
            decode(buf);
            fputs(buf, fdecoded);
        }

        ready = 0;

        pthread_cond_signal(&can_encode);
        pthread_mutex_unlock(&mutex);
    }

    fclose(fcoded);
    fclose(fdecoded);
    return NULL;
}

int main(){
    char filename[100];
    char newfile[120];

    printf("Input file name: ");
    scanf("%s", filename);

    sprintf(newfile, "new_%s", filename);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, encoder_thread, filename);
    pthread_create(&t2, NULL, decoder_thread, newfile);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

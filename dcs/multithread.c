#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define siz 15
#define max 71
#define tym 35
 
// A normal C function that is executed as a thread when its name
// is specified in pthread_create()

int rank=1;

double dist[15][15] = {
    {0, 633, 257,  91, 412, 150,  80, 134, 259, 505, 353, 324,  70, 211, 268},
    {633, 0, 390, 661, 227, 488, 572, 530, 555, 289, 282, 638, 567, 466, 420},
    {257, 390, 0, 228, 169, 112, 196, 154, 372, 262, 110, 437, 191, 74,  53},
    {91, 661, 228, 0, 383, 120,  77, 105, 175, 476, 324, 240,  27, 182, 239},
    {412, 227, 169, 383, 0, 267, 351, 309, 338, 196,  61, 421, 346, 243, 199},
    {150, 488, 112, 120, 267, 0,  63,  34, 264, 360, 208, 329,  83, 105, 123},
    {80, 572, 196,  77, 351,  63, 0, 29, 232, 444, 292, 297,  47, 150, 207},
    {134, 530, 154, 105, 309,  34,  29,   0, 249, 402, 250, 314,  68, 108, 165},
    {259, 555, 372, 175, 338, 264, 232, 249,   0, 495, 352,  95, 189, 326, 383},
    {505, 289, 262, 476, 196, 360, 444, 402, 495,   0, 154, 578, 439, 336, 240},
    {353, 282, 110, 324,  61, 208, 292, 250, 352, 154,   0, 435, 287, 184, 140},
    {324, 638, 437, 240, 421, 329, 297, 314,  95, 578, 435,   0, 254, 391, 448},
    {70, 567, 191,  27, 346,  83,  47,  68, 189, 439, 287, 254,   0, 145, 202},
    {211, 466,  74, 182, 243, 105, 150, 108, 326, 336, 184, 391, 145,   0,  57},
    {268, 420,  53, 239, 199, 123, 207, 165, 383, 240, 140, 448, 202,  57,   0}
};

int tim[2] = {10,15};
void *myThreadFun(void *nod)
{

    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    pthread_attr_setstacksize(&attrs, 1024);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    
    char *prev = (char *)nod;
    int val = prev[strlen(prev)-1] - 97;
    int preval = prev[strlen(prev)-6] - 97;

    sleep((int)(dist[preval][val]/tym));

    if(strlen(prev) == max)
     {
        int sum=0,i;

        sleep((int)(dist[val][0]/tym));

        for(i=0;i<70;i+=5)
          sum += dist[prev[i]-97][prev[i+5]-97];
        sum += dist[prev[70]-97][0];

        printf("Destination Reached : %s Rank = %d sum = %d\n",prev,rank,sum);
        rank++;
//        exit(0);
        pthread_detach(pthread_self());
     }
//    printf("Current Node - %d Prev Node - %d\n", val,preval);

//    printf("%s \n",prev);

    pthread_t *tid = (pthread_t *) malloc (sizeof(pthread_t) * siz);

    int i=0;
    char c[2];
    for(i=0;i<siz;i++)
     {
        c[0] = i + 97;
        c[1] = '\0';
//        printf("c = %s\n",c);
        if(i==val || strstr(prev, c ) != NULL)
         continue;
        char *msg = malloc(sizeof(char) * 1000);       
        strcpy(msg,prev);
        sprintf(msg,"%s -> %c",msg, 97+i);
//        printf("msg - %s\n",msg);
        int chk = pthread_create(&tid[i], NULL, myThreadFun, (void *) msg);
//        printf("%d %d\n",i,chk);
     }
    pthread_detach(pthread_self());
}
  
int main()
{
    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    pthread_attr_setstacksize(&attrs, 1024);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);

    printf("Before Thread\n");
    char *message = "a";
    int size = sizeof(dist[0])/sizeof(dist[0][0]);
    printf("size : %d\n",size);
    pthread_t *tid = (pthread_t *) malloc (sizeof(pthread_t) * size);
    int i=0;
    for(i=0;i<size;i++)
     {
        if(i==0)
         continue;
        char *msg = malloc(sizeof(char) * 1000);       
        strcpy(msg,message);
        sprintf(msg,"%s -> %c",msg,97+i);
        printf("msg - %s\n",msg);
        int chk = pthread_create(&tid[i], NULL, myThreadFun, (void *) msg);
//        printf("%d %d\n",i,chk);
     }
    sleep(10000);
    printf("After Thread\n");
    exit(0);
}


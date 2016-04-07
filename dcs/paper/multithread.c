#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define siz 15
#define max 71
#define tym 29
 
// A normal C function that is executed as a thread when its name
// is specified in pthread_create()

int rank=1;

double dist[15][15] = {
        { 0    ,    29,        82,        46,        68,        52,        72,        42,        51,        55,        29,        74,        23,        72,        46},
        { 29   ,      0,        55,        46,        42,        43,        43,        23,        23,        31,        41,        51,        11,        52,        21},
        { 82,        55,         0,        68,        46,        55,        23,        43,        41,        29,        79,        21,        64,        31,        51},
        { 46,        46,        68,         0,        82,        15,        72,        31,        62,        42,        21,        51,        51,        43,        64},
        { 68,        42,        46,        82,         0,        74,        23,        52,        21,        46,        82,        58,        46,        65,        23},
        { 52,        43,        55,        15,        74,         0,        61,        23,        55,        31,        33,        37,        51,        29,        59},
        { 72,        43,        23,        72,        23,        61,         0,        42,        23,        31,        77,        37,        51,        46,        33},
        { 42,        23,        43,        31,        52,        23,        42,         0,        33,        15,        37,        33,        33,        31,        37},
        { 51,        23,        41,        62,        21,        55,        23,        33,         0,        29,        62,        46,        29,        51,        11},
        { 55,        31,        29,        42,        46,        31,        31,        15,        29,         0,        51,        21,        41,        23,        37},
        { 29,        41,        79,        21,        82,        33,        77,        37,        62,        51,         0,        65,        42,        59,        61},
        { 74,        51,        21,        51,        58,        37,        37,        33,        46,        21,        65,         0,        61,        11,        55},
        { 23,        11,        64,        51,        46,        51,        51,        33,        29,        41,        42,        61,         0,        62,        23},
        { 72,        52,        31,        43,        65,        29,        46,        31,        51,        23,        59,        11,        62,         0,        59},
        { 46,        21,        51,        64,        23,        59,        33,        37,        11,        37,        61,        55,        23,        59,         0}
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


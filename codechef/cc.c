#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
 {
    return (*(int *)a - *(int *)b);
 }

int main()
 {
    int t,n,m,i,cut,j,arr[100000],join;
    scanf("%d",&t);

    while(t--)
     {
        scanf("%d%d",&n,&m);

        cut=0;
        i=arr[0]=1;

        while(i<=m)
         scanf("%d",&arr[i++]);

        qsort(arr,m+1,sizeof(int),cmp);

        i=2;
        while(i<=m)
         arr[i++]+=arr[i-1];

        i=1;
        join=arr[1]+1;

        while(arr[i]+i<m-1)
          i++;

        cut = arr[i-1];
        join = cut+i-1;
        j = m-1-join;

        if(arr[i]-arr[i-1]+1==j)
         j -= 1;

        cut += j;

        printf("%d\n",cut);
     }
 }

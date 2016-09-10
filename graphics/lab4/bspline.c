#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

void Spline(double x[],double y[],int N)
{
    setcolor(GREEN);
    double w[10];
    double h[10];
    double ftt[11];
    double A[10],B[10],C[10],D[10];
    for (int i=0; i<N; i++)
    {   
      //  printf("### %lf %lf\n",x[i+1],x[i]);
        w[i] = (x[i+1]-x[i]);
       // printf("%d ",w[i]);
        h[i] = (y[i+1]-y[i]);
        h[i] /= w[i];
      //  printf("%d\n",h[i]);
    }

    ftt[0] = 0;
    for (int i=0; i<N; i++)
    {
        ftt[i+1] = 3*(h[i+1]-h[i]);
        ftt[i+1]= ftt[i+1]/(w[i+1]+w[i]);
    }
    ftt[N] = 0;

    for (int i=0; i<N; i++)
    {
        A[i] = (ftt[i+1]-ftt[i])/(6*w[i]);
        B[i] = ftt[i]/2;
        C[i] = h[i]-w[i]*(ftt[i+1]+2*ftt[i])/6;
        D[i] = y[i];
    }
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL);
    
    line(100,100,600,100);
    line(100,25,100,200);

    for (int i=0; i<N; i++)
       putpixel (x[i], y[i], YELLOW);

    for (int i=0; i<N; i++)
    {
        double yt=0;
        for(double j=x[i];j<=x[i+1];j+=0.005)
        {
            double temp = A[i]*pow(j-x[i],3);
            temp+= B[i]*pow(j-x[i],2);
            temp+= C[i]*pow(j-x[i],1);
            temp+= D[i]*1;
            yt=temp;
            putpixel (j, yt, GREEN);
        }
    }

    getch();
    closegraph();
}

int main()
{
    int n;
    double x[]={100,125,150,175,200,225,250,275,300,325};
    double y[]={100,50,100,150,100,50,150,100,50,100};
    n=10;
    //printf("Enter the %d control points:\n",n);
    Spline(x,y,n-1);
    return 0;
}

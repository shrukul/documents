#include<stdio.h>
#include<graphics.h>
#include<math.h>
/*void drawcircleal(int x,int y, int p, int q)
{
   putpixel(x+p,y+q,LIGHTGREEN);
   putpixel(x-p,y+q,LIGHTGREEN);
   putpixel(x+p,y-q,LIGHTGREEN);
   putpixel(x-p,y-q,LIGHTGREEN);
   putpixel(x+q,y+p,LIGHTGREEN);
   putpixel(x-q,y+p,LIGHTGREEN);
   putpixel(x+q,y-p,LIGHTGREEN);
   putpixel(x-q,y-p,LIGHTGREEN);

   putpixel(x+p+1,y+q,GREEN);
   putpixel(x-p-1,y+q,GREEN);
   putpixel(x+p,y-q-1,GREEN);
   putpixel(x-p-1,y-q-1,GREEN);
   putpixel(x+q+1,y+p,GREEN);
   putpixel(x-q-1,y+p,GREEN);
   putpixel(x+q,y-p-1,GREEN);
   putpixel(x-q-1,y-p-1,GREEN);
}*/
void drawcircle(int x, int y, int p, int q)
{
   putpixel(x+p,y+q,YELLOW);
   putpixel(x-p,y+q,YELLOW);
   putpixel(x+p,y-q,YELLOW);
   putpixel(x-p,y-q,YELLOW);
   putpixel(x+q,y+p,YELLOW);
   putpixel(x-q,y+p,YELLOW);
   putpixel(x+q,y-p,YELLOW);
   putpixel(x-q,y-p,YELLOW);
}	
void circle(int xc, int yc, int r)
{
	float d,y1,y2,frac,x;
	int k;
	for(x=xc-r;x<=xc+r;)
	{
		d=sqrt(pow(r,2)-pow(x-xc,2));
		y1=yc-d;
		y2=yc+d;
		k=(int)y1;
		frac=y1-k;
		if(frac>=0.5)
		{
			putpixel(x,k,GREEN);
			putpixel(x,k+1,GREEN);
			putpixel(x,k-1,GREEN);
		}
		else
		{
			putpixel(x,k,GREEN);
			putpixel(x,k+1,GREEN);
			putpixel(x,k-1,GREEN);
		}
		k=(int)y2;
		frac=y2-k;
		if(frac>=0.5)
		{
			putpixel(x,k,GREEN);
			putpixel(x,k+1,GREEN);
			putpixel(x,k-1,GREEN);
		}
		else
		{
			putpixel(x,k,GREEN);
			putpixel(x,k+1,GREEN);
			putpixel(x,k-1,GREEN);
		}
		x=x+0.01;
	}
}
void brec(int xc, int yc, int r)
{
	int p,q,d;	
	q=r,p=0;
  	d=3-2*r;
    while(p<q)
  	{
  	  drawcircle(xc,yc,p,q);
  	  p=p+1;
  	  if(d<0)
  	  {
 	     d=d+4*p+6;
   	  }
      else
      {
      	q--;
        d=d+4*(p-q)+10;
      }
  	}
}
/*void brecal(int xc, int yc, int r)
{
	int p,q,d;	
	q=r,p=0;
  	d=3-2*r;
    while(p<q)
  	{
  	  drawcircleal(xc,yc,p,q);
  	  p=p+1;
  	  if(d<0)
  	  {
 	     d=d+4*p+6;
   	  }
      else
      {
      	q--;
        d=d+4*(p-q)+10;
      }
  	}
}*/		
int main()
{
	int gd=DETECT, gm;
	initgraph(&gd,&gm,NULL);
	brec(250,250,50);
	// delay(3000);
	// cleardevice();
	circle(350,350,50);
	delay(50000);
	closegraph();
	return 0;
}

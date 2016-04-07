#include<math.h>
#include<graphics.h>
#include<stdio.h>

void putpixelx(int x, int y, int col)
{
	putpixel(2*x-1,2*y-1,col);
	putpixel(2*x,2*y-1,col);
	putpixel(2*x-1,2*y,col);
	putpixel(2*x,2*y,col);
}

void putpixell1(int x, int y, int col)
{
	putpixel(2*x-1,2*y-1,15);
	putpixel(2*x,2*y-1,col);
	putpixel(2*x-1,2*y,col);
	putpixel(2*x,2*y,0);
}

void putpixell2(int x, int y, int col)
{
	putpixel(2*x-1,2*y-1,0);
	putpixel(2*x,2*y-1,col);
	putpixel(2*x-1,2*y,col);
	putpixel(2*x,2*y,15);
}

void putpixell3(int x, int y, int col)
{
	putpixel(2*x-1,2*y-1,col);
	putpixel(2*x,2*y-1,0);
	putpixel(2*x-1,2*y,15);
	putpixel(2*x,2*y,col);
}

void putpixell4(int x, int y, int col)
{
	putpixel(2*x-1,2*y-1,col);
	putpixel(2*x,2*y-1,15);
	putpixel(2*x-1,2*y,0);
	putpixel(2*x,2*y,col);
}

void draw(int x, int y, int p, int q, int col)
{
    putpixelx(x+p, y+q, col);
    putpixelx(x-p, y-q, col);
    putpixelx(x+p, y-q, col);
    putpixelx(x-p, y+q, col);
    putpixelx(x+q, y+p, col);
    putpixelx(x-q, y-p, col);
    putpixelx(x+q, y-p, col);
    putpixelx(x-q, y+p, col);
}
 
 void drawl(int x, int y, int p, int q, int col)
{
    putpixell1(x+p, y+q, col);
    putpixell2(x-p, y-q, col);
    putpixell3(x+p, y-q, col);
    putpixell4(x-p, y+q, col);
    putpixell1(x+q, y+p, col);
    putpixell2(x-q, y-p, col);
    putpixell3(x+q, y-p, col);
    putpixell4(x-q, y+p, col);
}

void drawcircle(int xc, int yc, int R,int col)
{
	  int x=R,y=0;
	  float x1,y1;
	  double theta=0,dtheta=1.0/R;
	  draw(xc,yc,x,y,col );
	  while(x>y)
	  {
		    theta+=dtheta;
		    x1=R*cos(theta);
		    y1=R*sin(theta);
		    x=round(R*cos(theta));
		    y=round(R*sin(theta));
		    if(x1-x>0 && y1-y>0)
		    	drawl(xc,yc,x+1,y+1,col);
		    else if(x1-x>0)
		    	drawl(xc,yc,x+1,y,col);
		    else if(y1-y>0)
			drawl(xc,yc,x,y+1,col);
		    draw(xc,yc,x,y,col);
	  } 
}

void drawcirclen(int xc, int yc, int R,int col)
{

	  int x=R,y=0;
	  float x1,y1;
	  double theta=0,dtheta=1.0/R;
	  draw(xc,yc,x,y,col );
	  while(x>y)
	  {
		    theta+=dtheta;
		    x1=R*cos(theta);
		    y1=R*sin(theta);
		    x=round(R*cos(theta));
		    y=round(R*sin(theta));

		    draw(xc,yc,x,y,col);
	  } 
}

void pixel(int xc,int yc,int x,int y,int col)
{
            putpixelx(xc+x,yc+y,col);
            putpixelx(xc+y,yc+x,col);
            putpixelx(xc-y,yc+x,col);
            putpixelx(xc-x,yc+y,col);
            putpixelx(xc-x,yc-y,col);
            putpixelx(xc-y,yc-x,col);
            putpixelx(xc+y,yc-x,col);
            putpixelx(xc+x,yc-y,col);
}

int main()
{
	   int gd = DETECT, gm;
	   initgraph(&gd, &gm, NULL);


	   int r=25;
	     
	   drawcirclen(150,85,r,10);
	     
	   getch();
	     
	   drawcircle(150,85,r,10);
	     

	     
	   getch();
	   closegraph();
	   return 0;
}

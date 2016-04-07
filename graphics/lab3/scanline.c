#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char**argv)
{
	int gd = DETECT, gm;
	initgraph(&gd,&gm,NULL);
	//before
	  //b1
	line(200,50,270,50);
	line(200,50,100,150);
	line(100,150,100,200);
	line(100,200,170,200);
	line(170,200,270,100);
	line(270,100,270,50);
	line(200,50,200,100);
	line(200,100,100,200);
	line(100,150,170,150);
	line(170,150,170,200);
	line(170,150,270,50);
	line(200,100,270,100);
	   //b2
	line(30,200,100,200);
	line(30,200,60,175);
	line(60,175,125,175);
	line(125,175,100,200);
	line(30,200,30,270);
	line(30,270,100,270);;
	line(100,270,100,200);
	line(125,175,125,245);
	line(100,270,125,245);
	line(60,175,60,245);
	line(60,245,125,245);
	line(30,270,60,245);
	delay(2000);
	int x,y;
	for(x=31;x<100;x++)
	{
	  for(y=201;y<270;y++)
	  {
	     if(getpixel(x,y)!=0)
	     {
	        putpixel(x,y,0);
	      }
	   }
	 }
	 for(x=101;x<170;x++)
	{
	  for(y=151;y<200;y++)
	  {
	     if(getpixel(x,y)!=0)
	     {
	        putpixel(x,y,0);
	      }
	   }
	 }
	 setcolor(BLACK);
	 line(60,175,60,200);
	 line(100,245,125,245);
	 line(200,100,100,200);
	 line(200,50,200,100);
	 line(200,100,270,100);
	/* for(x=61;x<=100;x++)
	{
	  for(y=175;y<200;y++)
	  {
	     if(getpixel(x,y)!=0)
	     {
	        putpixel(x,y,0);
	      }
	   }
	 }*/
	// int pts={100,150,200,50,270,50,170,150,100,150}
	 
	 //for(x=201,x>100;x--)
	 //{
	   //for(y=
	//floodfill(185,70,0);
	
	
	delay(10000);
	getch();
	//closegraph();

	return 0;
}

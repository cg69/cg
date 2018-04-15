#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

int r;


void Init()
{
glClearColor(0,0,0,0);
gluOrtho2D(-600,600,-600,600);
glClear(GL_COLOR_BUFFER_BIT);
}

void putpixel(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);	
	glEnd();
	glFlush();
}

void circle(int r)
{
	int x=0,y=r;
	int d;
	d=3-(2*r);
	do{
	putpixel(x,y);
	putpixel(y,x);
	putpixel(x,-y);
	putpixel(-y,x);
	putpixel(-x,y);
	putpixel(y,-x);
	putpixel(-x,-y);
	putpixel(-y,-x);
		if(d<=0)
			{
				d=d+(4*x)+6;	
				x++;
			}
		else
			{
				d=d+(4*(x-y))+10;
				x++;
				y--;
			}
	}while(x<=y);
	
}

void dda(int x1,int y1,int x2,int y2)
{
	float x,y,len,dx,dy,xinc,yinc;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dx>dy)
		len=dx;
	else 
		len=dy;
	xinc=(x2-x1)/len;
	yinc=(y2-y1)/len;
	x=x1;
	y=y1;
	int i=1;
	while(i<=len)
	{
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
		x=x+xinc;
		y=y+yinc;
		glFlush();
		i++;
	}


}

void triangle()
{
	dda(0,r,r*(sqrt(3)/2),-(r/2));
	dda(0,r,(-(r*(sqrt(3)/2))),-(r/2));
	dda(r*(sqrt(3)/2),-(r/2),(-(r*(sqrt(3)/2))),-(r/2));
}
void display()
{
	glColor3f(1.0,1.0,1.0);
	circle(r);
	glColor3f(1.0,1.0,1.0);
	triangle();
	glColor3f(1.0,1.0,1.0);
	circle(r/2);
	

}

int main(int argc,char **argv)
{
	printf("Enter the radius of the circle\n");
	scanf("%d",&r);
	glutInit(&argc,argv);
	glutInitWindowSize(1000,1000);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutCreateWindow("INCIRCLE");
	Init();
	glutDisplayFunc(display);
	glutMainLoop();		


}

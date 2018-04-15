#include<GL/glut.h>
#include<stdio.h>
int x1,x2,yy1,y2;


void dda(int x1,int yy1,int x2,int y2)
{
	float x,y,len,dx,dy,xinc,yinc;
	dx=abs(x2-x1);
	dy=abs(y2-yy1);
	if(dx>dy)
		len=dx;
	else 
		len=dy;
	xinc=(x2-x1)/len;
	yinc=(y2-yy1)/len;
	x=x1;
	y=yy1;
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
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	dda(x1,yy1,x2,yy1);
	dda(x2,yy1,x2,y2);
	dda(x2,y2,x1,y2);
	dda(x1,y2,x1,yy1);
	glColor3f(1.0,1.0,1.0);
	dda(x1,(yy1+y2)/2,(x1+x2)/2,y2);
	dda(x2,(yy1+y2)/2,(x1+x2)/2,y2);
	dda(x2,(yy1+y2)/2,(x1+x2)/2,yy1);
	dda((x1+x2)/2,yy1,x1,(yy1+y2)/2);
	glColor3f(1.0,1.0,1.0);
	dda((((x1+((x1+x2)/2)))/2),((((yy1+y2)/2)+y2)/2),(((x1+x2)/2+x2)/2),((y2+((yy1+y2)/2))/2));
	dda(((((x1+x2)/2)+x2)/2),((y2+((yy1+y2)/2))/2),((((x1+x2)/2)+x2)/2),((((yy1+y2)/2)+yy1)/2));
	dda(((((x1+x2)/2)+x2)/2),((((yy1+y2)/2)+yy1)/2),((((x1+x2)/2)+x1)/2),((((yy1+y2)/2)+yy1)/2));
	dda(((((x1+x2)/2)+x1)/2),((((yy1+y2)/2)+yy1)/2),((x1+((x1+x2)/2))/2),((((yy1+y2)/2)+y2)/2));	
glFlush();
}

void Init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(-600.0,600.0,-600.0,600.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc,char **argv)
{
	printf("Enter the end Points Of Diagonals(x1,yy1,x2,y2)\n");
	scanf("%d%d%d%d",&x1,&yy1,&x2,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Pattern");
	Init();
	glutDisplayFunc(Display);
	glutMainLoop();
}

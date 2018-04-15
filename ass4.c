#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
int count=0;

float mat[3][16],trans[3][3],res[3][16];

float x;

typedef struct pixel
{
GLubyte red,green,blue;
}pixel;
pixel c, boundary,fill;

void Init()
{
  glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT );
  glColor3ub(0,0,0);
  gluOrtho2D(0 , 1020 , 0 , 660);
}


void mult()
{
 int i,j,k;
 for(i=0;i<3;i++)
 {
  for(j=0;j<16;j++)
  {
   res[i][j]=0;
   for(k=0;k<3;k++)
   {
    res[i][j]+=trans[i][k]*mat[k][j];
   }
  }
 }
}

 int sign(int a)
 {
 	if(a>=0)
 		return 1;
 	else 
 		return -1;
 }
 
void breshnam(int xp1,int yp1,int xp2,int yp2)
{
  int x,y,dx,dy,dx2,dy2,sdx,sdy,steps,pk,i;
  char str[10];

  dx=xp2-xp1;
  dy=yp2-yp1;
  if(abs(dy)>abs(dx))
  {
   steps=abs(dy);
   if(yp1<yp2)
   {
    x=xp1;y=yp1;
   }
   else
   {
    x=xp2;y=yp2;
    dx=xp1-xp2;dy=yp1-yp2;
   }
  
   dx2=2*abs(dx);
   dy2=2*abs(dy);
   sdx=sign(dx);
   sdy=sign(dy);
   
  pk=dx2-abs(dy);
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  
  for(i=0;i<steps;i++)
  {
   if(pk<0)
   {
    y++;
    pk=pk+dx2;
   }
   else
   {
    y++;x=x+sdx;
    pk=pk+dx2-dy2;
   }
   glVertex2i(x,y);
  }
 
  glEnd();
  glFlush();
 }
 
 else
 {
  steps=abs(dx);
  if(xp1<xp2)
  {
   x=xp1;y=yp1;
  }
  else
  {
   x=xp2;y=yp2;
   dx=xp1-xp2;dy=yp1-yp2;
  }
  
   dx2=2*abs(dx);
   dy2=2*abs(dy);
   sdx=sign(dx);
   sdy=sign(dy);
   
  pk=dy2-abs(dx);
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  
  for(i=0;i<steps;i++)
  {
   if(pk<0)
   {
    x++;
    pk=pk+dy2;
   }
   else
   
   {
    y=y+sdy;x++;
    pk=pk+dy2-dx2;
   }
   glVertex2i(x,y);
  }
  glEnd();
  glFlush();
 }
}

void initmat()
{
 int ymax=glutGet(GLUT_WINDOW_HEIGHT),xmax=glutGet(GLUT_WINDOW_WIDTH);

 int a=xmax/2+100,b=100-200,i;

 for(i=0;i<5;i++)
 {
  	mat[0][i]=a;
  	mat[1][i]=b;
  	mat[2][i]=1;
  	a+=30;
 }
 	a=xmax/2+220;b=130-200;
 for(i=5;i<9;i++)
 {
  	mat[0][i]=a;
 	mat[1][i]=b;
 	mat[2][i]=1;
  b+=30;
 }
 	a=xmax/2+190;b=220-200;
 for(i=9;i<13;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  a-=30;
 }
 	a=xmax/2+100;b=190-200;
 for(i=13;i<16;i++)
 {
  	mat[0][i]=a;
  	mat[1][i]=b;
  	mat[2][i]=1;
  	b-=30;
 }
 
 trans[0][0]=cos(x);
 trans[0][1]=-sin(x);
 trans[1][0]=sin(x);
 trans[1][1]=cos(x);

 trans[2][1]=trans[2][0]=trans[0][2]=trans[1][2]=0;
 
 trans[2][2]=1;
 
}

void drawcb(float mat[3][16])
{
int i;

  breshnam(mat[0][0],mat[1][0],mat[0][4],mat[1][4]);
  for(i=0;i<5;i++)
  {
  	breshnam(mat[0][i],mat[1][i],mat[0][12-i],mat[1][12-i]);
 
  }
 
 for(i=5;i<9;i++)
 {
  	breshnam(mat[0][i],mat[1][i],mat[0][20-i],mat[1][20-i]);
 }
}

void boundary_fill(int x,int y,pixel b,pixel f)
{
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
	if(c.red!=b.red && c.green!=b.green && c.blue!=b.blue && c.red!=f.red && c.green!=f.green && c.blue!=f.blue)
	{
		glColor3ub(f.red,f.green,f.blue);
		glBegin(GL_POINTS);
  		glVertex2i(x,y);
  		glEnd();
		boundary_fill(x+1,y,b,f);
		boundary_fill(x-1,y,b,f);
		boundary_fill(x,y+1,b,f);
		boundary_fill(x,y-1,b,f);
		
 		glFlush();
	}
}

void mouse(int btn,int state,int x,int y)
{
  int ymax=glutGet(GLUT_WINDOW_HEIGHT);

  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
 	boundary_fill(x,ymax-y,boundary,fill);
  }
}

void draw()
{
	initmat();
	//drawcb(mat);
	mult();
	drawcb(res);
}

int main(int argc,char ** argv)
{
  int p;

  fill.red = 0.647059;
  fill.green = 0.164076;
  fill.blue = 0.164076;

  boundary.red = 10;
  boundary.green = 10;
  boundary.blue = 10;

  printf("ENTER THE ANGLE FOR ROTATION : ");
  scanf("%d",&p);
  x=(p*3.14)/180;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1020,660);
  glutCreateWindow("chess board");
  Init();

  glutDisplayFunc(draw);	
  glutMouseFunc(mouse);												
  glutMainLoop();
  return 0;
}


#include <GL/glut.h>    // Header File For The GLUT Library 
#include<stdio.h>

float rt = 0.0;

void init()         
{
  // This Will Clear The Background Color To Black
  glClearColor(0.0, 0.0, 0.0, 0.0);  
/* two matrix modes-  GL_PROJECTION (for setting the projection transformation)  &
                      GL_MODELVIEW (for setting the modeling and viewing transformations) */
  glMatrixMode(GL_PROJECTION);
   //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,50.0f); //View angle,aspect-ratio, viewer near,far distance from clipping plane
glOrtho(-50.0,50.0,-50.0,50.0,-50.0,50.0);
  glMatrixMode(GL_MODELVIEW);
}

float ballX = -5.0;                
float ballY = 0.0;
float ballZ = 0.0;

/* The main drawing function. */
void Draw()
{
  glClear(GL_COLOR_BUFFER_BIT);        // Clear The Screen And The Depth Buffer
  glLoadIdentity();                // Reset The View..Replace the current matrix with the identity matrix
  glTranslatef(rt,0.0,0.0);        // used  to Move scene forward ...  
   glBegin(GL_POLYGON);                // start drawing a polygon
  glColor3f(1.0,0.0,0.0);            // Set The Color To Red
  glVertex3f(-10.0, 10.0, 0.0);        // Top left
  glVertex3f(4.0, 10.0, 0.0);
  glVertex3f(10.0, 4.0, 0.0);
  glColor3f(0.0,1.0,0.0);            // Set The Color To Green
  glVertex3f( 10.0,0.0, 0.0);        // Bottom Right
  glColor3f(0.0,0.0,1.0);            // Set The Color To Blue
  glVertex3f(-10.0,0.0, 0.0);// Bottom Left    

  glEnd();                 
 
        glColor3f(1.0, 1.0, 0.0); //set ball colour
        glTranslatef(ballX,ballY,ballZ); //moving it toward the screen a bit on creation
        glutSolidSphere (3.0, 20, 20); //create ball. radius,longitude,latitute
        glTranslatef(ballX+15.0,ballY,ballZ); //moving it toward the screen a bit on creation
        glutSolidSphere (3.0, 20, 20);
 
  rt+=2.0;                    // Increase The Rotation Variable For The Triangle
  if(rt>50)                       //Set to left corner   
      rt=-40.0;
 
    glutSwapBuffers();  // swap the buffers to display, since double buffering is used. 
}


int main(int argc, char **argv) 
{  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA);     // GLUT_SINGLE fast movement
  glutInitWindowSize(1000, 1000);  
  glutInitWindowPosition(0, 0);  
  glutCreateWindow("Moving Car"); 
  
  glutDisplayFunc(Draw);  
  glutIdleFunc(Draw);   //global idle callback for continuous animation 
  
  /* Initialize our window. */
     init();
    /* Start Event Processing Engine */  
  glutMainLoop();  

  return 0;
}



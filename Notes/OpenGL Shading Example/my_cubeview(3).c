
/* Modified rotating cube with camera/viewer movement from Chapter 5 */
/* Cube definition and display similar to rotating--cube program */

/* Two cubes are created but only one is rotated.*/
/* Rotate the object using mouse buttons. 
 * Move the camera using keys: x-X, y-Y, z-Z. */

/* We use the Lookat function in the display callback to point
the viewer, whose position can be altered by the x,X,y,Y,z, and Z keys.
The perspective view is set in the reshape callback */

/* KP: Modified April 5, 2013 for MU CS4610 Computer Graphics class*/

#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
	{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
	{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

void polygon(int a, int b, int c , int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glNormal3fv(normals[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glNormal3fv(normals[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glNormal3fv(normals[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glNormal3fv(normals[d]);
		glVertex3fv(vertices[d]);
	glEnd();
																										}

void colorcube()
{
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {2.5, 0.0, 20.0}; /* initial camera/viewer location */

void display(void)
{

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* Update camera/viewer position in modelview matrix */

	glLoadIdentity();
	/* gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);*/
   /* Defn: gluLookAt(GLdouble eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
   /* Set the center-location the camera is looking the same as the x-coord
    * of the camera/viewer.*/
	gluLookAt(viewer[0],viewer[1],viewer[2], viewer[0], 0.0, 0.0, 0.0, 1.0, 0.0);

/* Rotate object/cube */

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

   colorcube();

  /* This is an example of moving the object with a fixed camera.
  * The second cube remains stationary while the first cube rotates.
  */
   glLoadIdentity();
   gluLookAt(viewer[0],viewer[1],viewer[2], viewer[0],  0.0, 0.0, 0.0, 1.0, 0.0);
   glTranslatef(5.0, 0.0, 0.0);
   colorcube();

   glFlush();
	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	theta[axis] += 10.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	display();
}

void keys(unsigned char key, int x, int y)
{

/* Use x, X, y, Y, z, and Z keys to move camera/viewer.
   We make the x-X changes behave like a translation of the
   camera by changing the gluLookAt() function in the diplay() 
   module above. */

   if(key == 'x') viewer[0]-= 1.0;
   if(key == 'X') viewer[0]+= 1.0;
   if(key == 'y') viewer[1]-= 1.0;
   if(key == 'Y') viewer[1]+= 1.0;
   if(key == 'z') viewer[2]-= 1.0;
   if(key == 'Z') viewer[2]+= 1.0;
   display();
}

void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);

/* Use a perspective view */

 glMatrixMode(GL_PROJECTION); 
 glLoadIdentity();
 
 /*
  * You can set up the camera using glFrustum as shown below.
  *
  * Defn: glFrustum(GLdouble left, right, bottom, top, nearVal, farVal);
  *
	if(w<=h) glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 
       2.0* (GLfloat) h / (GLfloat) w, 2.0, 20.0);
	else glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h, 
       2.0* (GLfloat) w / (GLfloat) h, 2.0, 20.0);
 
 */

 /* Or you can set up the camera using gluPerspective as below.
  * Defn: gluPerspective(GLdouble fovy, aspect, zNear, zFar);
 /* The -10 and +10 clipping planes are incorrect. Try it and the 
  * object won't be visible. */
 /* gluPerspective(45.0, w/h, -10.0, 10.0); */

 gluPerspective(45.0, w/h, 2.0, 50.0);

 glMatrixMode(GL_MODELVIEW);
}

void
main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
 glutCreateWindow("colorcube");
 glutReshapeFunc(myReshape);
 glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glEnable(GL_DEPTH_TEST);
 glutMainLoop();
}

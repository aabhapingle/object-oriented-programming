#include<stdlib.h>   // general purpose lib
#include<math.h>     // for cos and sin functions 
#include<GL/glut.h>  // contains utilities of OPENGL , for i/p o/p, keyboard and mouse operation
#include<iostream>

using namespace std;
float xr = 0, yr = 0;

void display() {
    float theta;
    glClear(GL_COLOR_BUFFER_BIT);   // clears buffer to preset values
    glColor3f(0.8, 0.36, 0.36);     // sets the color, new value for color, values b/w 0 to 1
    glBegin(GL_POLYGON);            // draws a polygon, given the vertices, if given, here circle is drawn
    for (int i = 0; i < 360; i++) { // one degree increment every time
        theta = (i * 3.142) / 180;  // convert the angle from degree to radians
        glVertex2f(xr + 200 + 50 * cos(theta), yr + 200 + 50 * sin(theta));  // parameters x and y
    }

    glEnd(); // glBegin and glend functions delimit the vertices that define a primitive or a group of like primitives.
    glFlush(); // function forces execution of OpenGL functions in finite time.
    glutPostRedisplay(); // glutPostRedisplay marks the current window as needing to be redisplayed.
    glutSwapBuffers();   // If the current pixel format for the window referenced by the device context does not include a back buffer, this call
    // has no effect and the content of the back buffer is undefined when the function returns.

}

void keyFunction(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        yr = yr + 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        yr = yr - 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        xr = xr - 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        xr = xr + 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_INSERT:
        // right up
        yr = yr + 50;
        xr = xr + 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_HOME:
        // right down
        yr = yr - 50;
        xr = xr + 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_UP:
        // left up
        yr = yr + 50;
        xr = xr - 50;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN:
        // left down
        yr = yr - 50;
        xr = xr - 50;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  // initialise the glut library

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // sets the initial display mode // bitwise OR-ing of GLUT display mode bit masks
    glutInitWindowSize(400, 400);                 // black window size
    glutInitWindowPosition(600, 50);              // window position
    glutCreateWindow("window");                   // creates a window with the specified name 

    glutDisplayFunc(display);  // display callback func
    glClearColor(0, 0, 0, 0);  // specify clear values for the color buffers
    gluOrtho2D(0.0, 400, 0.0, 400);  //gluOrtho2D — define a 2D orthographic projection matrix
    glutSpecialFunc(keyFunction); // glutSpecialFunc sets the special keyboard callback for the current window.

    glutMainLoop();   // glutMainLoop enters the GLUT event processing loop.
    return 0;
}

// gl clear--
// takes parameter as bitwise OR of the masks that indicate the buffer has to be cleared
// three masks are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, and GL_STENCIL_BUFFER_BIT
// GL_COLOR_BUFFER_BIT - buffers currently enabled for color writing.

// gl vertex--
// The glVertex function commands are used within glBegin/glEnd pairs to specify point, 
// line, and polygon vertices
// The current color, normal, and texture coordinates are associated with the vertex 
// when glVertex is called.
// When only x and y are specified, z defaults to 0.0 and w defaults to 1.0.
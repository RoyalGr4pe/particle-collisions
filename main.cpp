#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "src/particles.cpp"
#include <iostream>
using namespace std;



void display() {
    while (true) {

        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red

        Particle particle1(-0.5f, 0.0f, 0.025f);  // Create a circle object
        particle1.update();
        particle1.draw();  // Draw the circle

        Particle particle2(0.5f, 0.0f, 0.025f);  // Create a circle object
        particle2.update();
        particle2.draw();  // Draw the circle

        glFlush();
    }
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate the aspect ratio
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    // Adjust the projection matrix to maintain the aspect ratio
    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -1.0, 1.0);
    } else {
        glOrtho(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, -1.0, 1.0);
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set the display mode
    glutInitWindowSize(1920, 1080);  // Set the window size
    glutCreateWindow("Circle Drawing");  // Create the window
    glutDisplayFunc(display);  // Set the display callback function
    glutReshapeFunc(reshape);  // Set the reshape callback function
    glutMainLoop();  // Enter the GLUT event loop
    return 0;
}
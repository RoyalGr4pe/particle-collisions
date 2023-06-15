#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "src/particles.cpp"
#include <iostream>
using namespace std;



bool isRunning = true;  // Flag to control the program loop

void windowCloseCallback(GLFWwindow* window) {
    isRunning = false;  // Set the flag to false when the window is closed
}


void display(GLFWwindow* window) {
    static float prevTime = glfwGetTime();  // Initialize prevTime with the current time
    static std::vector<Particle> particles = createParticleArray(10); 

    while (isRunning) {  // Check the flag to continue running the program
        float currentTime = glfwGetTime();  // Get the current frame time
        float deltaTime = currentTime - prevTime;  // Calculate the time difference
        
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0f, 0.0f, 1.0f);  // Set color to red

        for (int idx = 0; idx <= particles.size(); ++idx) {
            Particle& particle = particles[idx];
            particle.update(deltaTime);
            particle.draw();
        }

        prevTime = currentTime;  // Update the previous time

        glFlush();
        glfwSwapBuffers(window);  // Swap the front and back buffers

        glfwPollEvents();  // Poll for events
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
    // Initialize GLFW
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Particle Simulator", NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    // Set the window context
    glfwMakeContextCurrent(window);

    // Register the window close callback function
    glfwSetWindowCloseCallback(window, windowCloseCallback);

    // Set the viewport and projection matrix
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    reshape(width, height);

    while (!glfwWindowShouldClose(window)) {
        display(window);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>

class Particle {
private:
    float x;
    float y;
    float radius;
    float velocity;
    float acceleration;

public:
    Particle(float xPos, float yPos, float r) {
        x = xPos;
        y = yPos;
        radius = r;
        velocity = 0.0f;
        acceleration = -0.01f;  // Set the acceleration due to gravity
    }


    void update() {
        // Update the velocity and position based on acceleration
        velocity += acceleration;
        y += velocity;

        // Reverse the velocity when the circle hits the ground
        if (y - radius < -1.0f) {
            velocity *= -1.0f;
        }
    }

    void draw() {
        const int numSegments = 100;
        const float theta = 2.0 * 3.1415926 / numSegments;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(x, y, 0.0f);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);  // Center vertex

        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * theta;
            float xPos = radius * cos(angle);
            float yPos = radius * sin(angle);
            glVertex2f(xPos, yPos);
        }
        glEnd();
    }
};
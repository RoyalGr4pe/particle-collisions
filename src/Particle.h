#ifndef PARTICLE_H
#define PARTICLE_H

#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>


struct ParticleAttributes {
    float x;
    float y;
    float mass;
    float radius;
    float horizontalVel;
    float verticalVel;
    float red;
    float green;
    float blue;
};


class Particle {
    public:
        Particle(ParticleAttributes& particle) {
            x = particle.x;
            y = particle.y;
            mass = particle.mass;
            radius = particle.radius;
            horizontalVel = particle.horizontalVel;
            verticalVel = particle.verticalVel;
            red = particle.red;
            green = particle.green;
            blue = particle.blue;
        }
        float x;
        float y;
        float mass;
        float radius;
        float horizontalVel;
        float verticalVel;
        float red;
        float green;
        float blue;


    void applyHorizontalVelocity(float deltaTime) {
        const float xLeft = -1.825f;
        const float xRight = 1.825f;

        x += horizontalVel * deltaTime;
        
        if (x + radius > xRight) {
            horizontalVel = -1.0 * horizontalVel;

            x = xRight - radius;
        } else if (x - radius < xLeft) {
            horizontalVel = -1.0 * horizontalVel;

            x = xLeft + radius;
        }
    }

    void applyVerticalVelocity(float deltaTime) {
        const float yTop = 1.0f;
        const float yBottom = -1.0f;

        y += verticalVel * deltaTime;
        
        if (y + radius > yTop) {
            verticalVel = -1.0 * verticalVel;

            y = yTop - radius;
        } else if (y - radius < yBottom) {
            verticalVel = -1.0 * verticalVel;

            y = yBottom + radius;
        }
    }


    void applyGravity(float deltaTime) {
        const float gravity = -0.5f;  // Set the gravitational force
        const float restitution = 1.0f;       // Set the restitution coefficient
        const float yTop = 1.0f;
        const float yBottom = -1.0f;

        // Update the velocity and position based on acceleration
        verticalVel += gravity * deltaTime;
        y += verticalVel * deltaTime;

        // Reverse the velocity when the circle hits the ground
        if (y - radius < yBottom) {
            // Reverse the velocity
            verticalVel = -1.0 * verticalVel * restitution;

            // Make sure the particle is above the ground
            y = yBottom + radius;
        } else if (y + radius > yTop) {
            verticalVel = -1.0 * verticalVel * restitution;

            y = yTop - radius;
        }
    }


    void update(float deltaTime) {
        applyHorizontalVelocity(deltaTime);
        applyVerticalVelocity(deltaTime);
        //applyGravity(deltaTime);
    }


    void draw() {
        const int numSegments = 100;
        const float theta = 2.0 * 3.1415926 / numSegments;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(x, y, 0.0f);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);  // Center vertex

        glColor3f(red, green, blue);

        // Drawing of the particle
        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * theta;
            float xPos = radius * cos(angle);
            float yPos = radius * sin(angle);
            glVertex2f(xPos, yPos);
        }
        glEnd();
    }
};

#endif
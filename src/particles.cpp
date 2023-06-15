#include "mechanics.cpp"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <random>


class Particle {
    private:
        float x;
        float y;
        float radius;
        float verticalVel;
        float horizontalVel;

    public:
        Particle(float xPos, float yPos, float r, float vVel, float hVel) {
            x = xPos;
            y = yPos;
            radius = r;
            verticalVel = vVel;
            horizontalVel = hVel;
        }


    void update(float deltaTime) {
        checkCollision(x, y, horizontalVel, verticalVel, radius, deltaTime);
        applyHorizontalVelocity(horizontalVel, x, radius, deltaTime);
        applyGravity(verticalVel, y, radius, deltaTime);
    }

    void draw() {
        const int numSegments = 100;
        const float theta = 2.0 * 3.1415926 / numSegments;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(x, y, 0.0f);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);  // Center vertex

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

// Create an array of Particles
std::vector<Particle> createParticleArray(int numParticles) {
    std::vector<Particle> particles;
    float xPos = -1.5;
    float yPos = 0.60f;
    const float radius = 0.10f;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform distribution
    std::uniform_int_distribution<int> dist(-1, 1);  // Generates random numbers between 1 and 100 (inclusive)

    for (int i = 0; i < numParticles; ++i) {
        // Generate a random horizontal velocity
        int horizontalVel = dist(gen);
        // Generate a random vertical velocity
        int verticalVel = dist(gen);

        particles.push_back(Particle(xPos, yPos, radius, verticalVel, horizontalVel));
        
        xPos += 2*radius + 0.05;
        yPos += 0.05*radius;
    }

    return particles;
}
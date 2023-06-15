#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>


class Particle {
    private:
        float x;
        float y;
        float radius;
        float velocity;

    public:
        Particle(float xPos, float yPos, float r) {
            x = xPos;
            y = yPos;
            radius = r;
            velocity = 0.0f;
        }


    void update(float deltaTime) {
        const float gravity = -0.010f;  // Set the gravitational force
        const float restitution = 0.8f;       // Set the restitution coefficient
        
        // Update the velocity and position based on acceleration
        velocity += gravity * deltaTime;
        y += velocity * deltaTime;

        // Reverse the velocity when the circle hits the ground
        if (y - radius < -1.0f) {
            // Reverse the velocity
            velocity = -1.0 * velocity * restitution;

            // Make sure the particle is above the ground
            y = -1.0f + radius;
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


std::vector<Particle> createParticleArray(int numParticles) {
    std::vector<Particle> particles;
    float xPos = -1.5f;

    for (int i = 0; i <= numParticles; ++i) {
        particles.push_back(Particle(xPos, 0.80f, 0.025f));
        xPos += 0.10;
    }

    return particles;
}
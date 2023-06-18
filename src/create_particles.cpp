#include "Particle.h"
#include <vector>
#include <random>



// Create an array of Particles
std::vector<Particle>& createParticleArray(int numParticles) {
    static std::vector<Particle> particlesArray;
    float xPos = -1.7;
    float yPos = 0.0f;
    float radius = 0.05f;
    float mass = 0.5f;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform distribution
    std::uniform_int_distribution<int> dist(-1, 1);  // Generates random numbers between 1 and 100 (inclusive)

    for (int i = 0; i < numParticles; ++i) {
        // Generate a random horizontal velocity
        float horizontalVel = dist(gen);
        // Generate a random vertical velocity
        float verticalVel = dist(gen);

        ParticleAttributes particle;

        particle.x = xPos;
        particle.y = yPos;

        particle.horizontalVel = horizontalVel;
        particle.verticalVel = verticalVel;

        particle.mass = mass;
        particle.radius = radius;
        
        particle.red = 1.0f;
        particle.green = 1.0f;
        particle.blue = 1.0f;

        particlesArray.push_back(Particle(particle));
        
        xPos += 2*radius;
        yPos += 0.05*radius;
    }

    return particlesArray;
}
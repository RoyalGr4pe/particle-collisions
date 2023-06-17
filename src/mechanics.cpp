#include <vector>
#include <math.h>
#include "Particle.h"


void checkCollisions(std::vector<Particle>& particles, float deltaTime) {
    const float coefficient_of_restitution = 1.0f;

    for (int i = 0; i < particles.size(); ++i) {
        for (int j = i + 1; j < particles.size(); ++j) {
            Particle& particleA = particles[i];
            Particle& particleB = particles[j];

            float inverseMassA = 1.0 / particleA.mass;
            float inverseMassB = 1.0 / particleB.mass;

            // Calculate the distance between the centers of the particles
            float dx = particleB.x - particleA.x;
            float dy = particleB.y - particleA.y;
            float distance = sqrt(dx * dx + dy * dy);

            // Check if the particles have collided
            if (distance <= particleA.radius + particleB.radius) {
                // Calculate the normal and tangential vectors
                float nx = dx / distance;
                float ny = dy / distance;
                float tx = -ny;
                float ty = nx;

                // Calculate the relative velocity in the normal direction
                float dvx = particleB.horizontalVel - particleA.horizontalVel;
                float dvy = particleB.verticalVel - particleA.verticalVel;
                float relativeVelocityNormal = dvx * nx + dvy * ny;

                // Calculate the impulse magnitude
                float impulseMagnitude = (-(1 + coefficient_of_restitution) * relativeVelocityNormal) / (inverseMassA + inverseMassB);

                // Apply impulses to the particles
                float impulseAx = impulseMagnitude * inverseMassA * nx;
                float impulseAy = impulseMagnitude * inverseMassA * ny;
                float impulseBx = -impulseMagnitude * inverseMassB * nx;
                float impulseBy = -impulseMagnitude * inverseMassB * ny;

                particleA.horizontalVel -= impulseAx;
                particleA.verticalVel -= impulseAy;
                particleB.horizontalVel -= impulseBx;
                particleB.verticalVel -= impulseBy;

                // Separate the particles to avoid overlap
                float overlap = (particleA.radius + particleB.radius) - distance;
                float separationAx = -overlap * 0.5f * nx;
                float separationAy = -overlap * 0.5f * ny;
                float separationBx = overlap * 0.5f * nx;
                float separationBy = overlap * 0.5f * ny;

                particleA.x += separationAx;
                particleA.y += separationAy;
                particleB.x += separationBx;
                particleB.y += separationBy;
            }
        }
    }
}

void applyHorizontalVelocity(float& horizontalVel, float& x, float radius, float deltaTime) {
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

void applyGravity(float& verticalVel, float& y, float radius, float deltaTime) {
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
#include "projectile.h"
#include <cmath>
extern float angle;
extern float velocity;
extern float maxHeight;
extern float range;
extern float timeOfFlight;
extern float currentTime;
extern bool isAnimating;

const float g = 9.8f; // Acceleration due to gravity

void calculateProjectile(float angle, float velocity) {
    float radianAngle = angle * M_PI / 180.0f; // Convert angle to radians
    float vx = velocity * cos(radianAngle);    // Horizontal velocity
    float vy = velocity * sin(radianAngle);    // Vertical velocity

    timeOfFlight = (2 * vy) / g;              // Time of flight
    maxHeight = (vy * vy) / (2 * g);          // Maximum height
    range = vx * timeOfFlight;                // Range
}

void getProjectilePosition(float t, float& x, float& y) {
    float radianAngle = angle * M_PI / 180.0f;
    float vx = velocity * cos(radianAngle);
    float vy = velocity * sin(radianAngle);

    x = vx * t;
    y = vy * t - 0.5f * g * t * t;
}

#ifndef PROJECTILE_H
#define PROJECTILE_H

extern float angle, velocity;
extern float maxHeight, range;
extern float timeOfFlight;
extern float currentTime;
extern bool isAnimating;

void calculateProjectile(float angle, float velocity);
void getProjectilePosition(float t, float& x, float& y);

#endif // PROJECTILE_H

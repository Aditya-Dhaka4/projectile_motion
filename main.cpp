#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <string>
#include "projectile.h"
#include "background.h"

// In main.cpp, define and initialize the variables:
float angle, velocity;
float maxHeight, range;
float timeOfFlight;
float currentTime = 0.0f;
bool isAnimating = true;

int main(int argc, char** argv) {
    // Get user input
    std::cout << "Enter the angle of projection (in degrees, 0-90): ";
    std::cin >> angle;
    std::cout << "Enter the initial velocity (in m/s, e.g., 10-50): ";
    std::cin >> velocity;

    // Validate input
    if (angle < 0 || angle > 90 || velocity <= 0) {
        std::cerr << "Invalid input! Angle must be between 0 and 90 degrees, and velocity must be positive." << std::endl;
        return 1;
    }

    // Calculate projectile motion parameters
    calculateProjectile(angle, velocity);

    // Display results in the console
    std::cout << "Maximum Height: " << maxHeight << " meters" << std::endl;
    std::cout << "Range: " << range << " meters" << std::endl;
    std::cout << "Time of Flight: " << timeOfFlight << " seconds" << std::endl;

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Projectile Motion Simulation");

    // Set up the display and timer functions
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0); // Start the timer

    // Initialize OpenGL settings
    init();

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}

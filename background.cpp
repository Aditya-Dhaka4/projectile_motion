#include <GL/glut.h>
#include <cmath>
#include <string>
#include "background.h"
#include "projectile.h"

extern float angle;
extern float velocity;
extern float maxHeight;
extern float range;
extern float timeOfFlight;
extern float currentTime;
extern bool isAnimating;

// Function to draw text on the screen
void drawText(float x, float y, const std::string& text) {
    glColor3f(1.0, 1.0, 1.0); // White color for text
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Function to draw a realistic tree
void drawTree(float x, float y) {
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color for the trunk
    glBegin(GL_POLYGON);
    glVertex2f(x - 3, y);
    glVertex2f(x + 3, y);
    glVertex2f(x + 3, y + 30);
    glVertex2f(x - 3, y + 30);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.0f); // Green color for the leaves
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + 50); // Top center of the tree
    for (int i = 0; i <= 360; i += 20) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + 15 * cos(angle), y + 30 + 10 * sin(angle));
    }
    glEnd();
}

// Function to draw the sun
void drawSun(float x, float y) {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the sun
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + 40 * cos(angle), y + 40 * sin(angle));
    }
    glEnd();
}

// In background.cpp
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + 25 * cos(angle), y + 15 * sin(angle));
    }
    glEnd();
}

// Function to draw the ground
void drawGround() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f); // Dark green at the bottom
    glVertex2f(0, 0);
    glVertex2f(range, 0);
    glColor3f(0.0f, 0.8f, 0.0f); // Light green at the top
    glVertex2f(range, 50);
    glVertex2f(0, 50);
    glEnd();
}

// Function to draw the sky
void drawSky() {
    glBegin(GL_POLYGON);
    glColor3f(0.53f, 0.81f, 0.92f); // Light blue at the bottom
    glVertex2f(0, maxHeight + 200);
    glVertex2f(range, maxHeight + 200);
    glColor3f(0.0f, 0.2f, 0.8f); // Deeper blue at the top
    glVertex2f(range, maxHeight + 300);
    glVertex2f(0, maxHeight + 300);
    glEnd();

    drawCloud(200, maxHeight + 100);
    drawCloud(400, maxHeight + 150);
    drawCloud(600, maxHeight + 50);
    drawSun(range / 2, maxHeight + 150);
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Set background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, std::max(range, 100.0f), 0, std::max(maxHeight, 100.0f) + 200);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the sky and ground
    drawSky();
    drawGround();
    
    // Draw trees
    drawTree(100, 50);
    drawTree(300, 50);
    drawTree(500, 50);

    // Draw the trajectory and the projectile
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= currentTime; t += 0.01f) {
        float x, y;
        getProjectilePosition(t, x, y);
        glVertex2f(x, y);
    }
    glEnd();

    // Display the projectile
    float x, y;
    getProjectilePosition(currentTime, x, y);
    glColor3f(0.0f, 0.0f, 0.0f);
    // Draw a filled circle
    glBegin(GL_POLYGON);
    float radius = 1.2;
    int numSegments = 50; 
    for (int i = 0; i < numSegments; i++) {
       float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
       float cx = radius * cosf(theta);
       float cy = radius * sinf(theta);
       glVertex2f(x + cx, y + cy);
    }
    glEnd();

    // Draw text on the screen
    drawText(10, maxHeight + 40, "Height: " + std::to_string(y) + " m");
    drawText(10, maxHeight + 20, "Range: " + std::to_string(x) + " m");
    drawText(10, maxHeight, "Time: " + std::to_string(currentTime) + " s");

    glutSwapBuffers();
}

// Timer function for animation
void timer(int value) {
    if (isAnimating) {
        currentTime += 0.01f;
        if (currentTime > timeOfFlight) {
            isAnimating = false;
        }
        glutPostRedisplay();
        glutTimerFunc(16, timer, 0); // 60 FPS
    }
}

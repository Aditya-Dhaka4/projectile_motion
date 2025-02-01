#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>

void drawText(float x, float y, const std::string& text);
void drawTree(float x, float y);
void drawCloud(float x, float y);
void drawSun(float x, float y);
void drawGround();
void drawSky();
void display();
void timer(int value);
void init();

#endif // UTILS_H

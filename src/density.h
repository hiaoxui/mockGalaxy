#ifndef DENSITY
#define DENSITY

#include <cmath>
#include <random>

#include "util.h"

using namespace std;

// calculate the density of specific position
float rhoCal(float x, float y, float z, float F1, float F2);

// return whether there is a star at given position
bool hasPlanet(int x, int y, int z, float F1 = 10.0f, float F2 = 1.5f);

// a helper function of Monte Carlo
int amendStep(int pos, float &step, float direction, int Boundary);

// detect whether there is any star in a specific direction
// use the Monte Carlo algorithm
bool MC_Detect(int pos_x, int pos_y, int pos_z, float rx, float ry, float rz, float F1,float F2);

// paint a point in canvas
void _pointBG(byte *ret, unsigned color, int i, int j);

// paint a solid circle at a given position
void pointBG(byte *ret, unsigned color, int i, int j, int division);

// get the background picture data
byte *getBg(int pos_x, int pos_y, int pos_z, float F1, float F2);

#endif // DENSITY


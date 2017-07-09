#include "util.h"
#include "body.h"
#include "sphere.h"
#include "ddsvec.h"
#include "objloader.h"
#include "space.h"
#include "ship.h"

vector<sphere> objs;

dvec3 ship::r, ship::beta, ship::front(0,0,-1), ship::up, ship::right;
dmat3 ship::shipMatrix;
bool ship::needUpdate, ship::relative;
double ship::gamma,ship::t;
space* ship::evm_pt;

ddsvec textures;

void rotateTheta(float &x, float &y, float theta)
{
    float s = sin(theta);
    float c = cos(theta);
    float newX = x * c - y * s;
    float newY = x * s + y * c;
    x = newX;
    y = newY;
}

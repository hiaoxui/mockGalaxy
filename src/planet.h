#ifndef ADDPLANET
#define ADDPLANET

#include <vector>
#include <string>
#include <iostream>
#include <random>

#include "util.h"
#include "body.h"

using namespace std;

// planet
class planet : public body
{
public:
    // get current position
    void getPosition(float t, float &x, float &y, float &z);

    // constructor
    planet(int randNum, int rank, body *parent);

private:

    // the star the planet orbit around
    body *parent;

    // some parameters about planet
    float inclinationTheta;
    float inclinationPhi;
    float orbitRadius;
    float beginPhi;
};

// add some planet to a star
void addPlanet(vector<planet> &planetVec, int randNum, body *parent);

#endif // ADDPLANET

#include "planet.h"
#ifndef M_PI
	#define M_PI 3.141592654
#endif

planet::planet(int randNum, int rank, body *parent):
    body()
{
    srand(randNum);
    orbitRadius = rank / 10.0f + (rand() * 0.05f / RAND_MAX - 0.025f);
    radius = rand() * 0.001f / RAND_MAX + 0.002f;
    beginPhi = rand() * M_PI / RAND_MAX;
    inclinationTheta = rand() * 0.1f / RAND_MAX - 0.05f;
    inclinationPhi = rand() * 0.1f / RAND_MAX - 0.05f;

    this->parent = parent;

    identity = PLANET;
    mass = 0;

}

void planet::getPosition(float t, float &x, float &y, float &z)
{
    float phi = beginPhi + t * GM * sqrt(parent->mass) * pow(orbitRadius, -1.5);
    float tmpX = orbitRadius * cos(phi);
    float tmpY = orbitRadius * sin(phi);
    rotateTheta(tmpX, tmpY, inclinationPhi);
    tmpX *= cos(inclinationTheta);
    rotateTheta(tmpX, tmpY, -inclinationPhi);
    x = tmpX + parent->x;
    y = tmpY + parent->y;
    z = tmpX * sin(inclinationTheta) + parent->z;
}

void addPlanet(vector<planet> &planetVec, int randNum, body *parent)
{
    srand(randNum % 77719);
    int planetCnt = rand() % 6 + 2;
    for(int cnt = 0; cnt < planetCnt; ++ cnt)
    {
        randNum = rand();
        planetVec.push_back(planet(randNum, cnt + 1, parent));
		planetVec[planetVec.size() - 1].bindBuffer(4, 10);// rand() % 10 + 10);
    }
}

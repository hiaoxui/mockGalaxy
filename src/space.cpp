#include "space.h"

//#define DEBUGSPACE
#define LOADBG

space::space(float curr_x, float curr_y, float curr_z) {
    zone_x = curr_x;
    zone_y = curr_y;
    zone_z = curr_z;
    bodyVec.push_back(body(STAR, 0, 6, 0, 0, 0));
    bodyVec[0].bindBuffer(5);
    _flush();
}

void space::moveSky()
{
    bodyVec[0].x = position[0];
    bodyVec[0].y = position[1];
    bodyVec[0].z = position[2];
}

int space::flush() {
	int ret = 0;
	while (position[0] > 1 + THRESHOLD)
	{
#ifdef DEBUGSPACE
		cout << "x" << position[0] << endl;
#endif
		zone_x += 1;
		position[0] -= 1;
		ret |= X | FORWARD;
}
	while (position[0] <  0 - THRESHOLD)
	{
#ifdef DEBUGSPACE
		cout << "x" << position[0] << endl;
#endif
		zone_x -= 1;
		position[0] += 1;
		ret |= X | BACK;
	}
	while (position[1] > 1 + THRESHOLD)
	{
#ifdef DEBUGSPACE
		cout << "y" << position[1] << endl;
#endif
		zone_y += 1;
		position[1] -= 1;
		ret |= Y | FORWARD;
	}
	while (position[1] < -THRESHOLD)
	{
#ifdef DEBUGSPACE
		cout << "y" << position[1] << endl;
#endif
		zone_y -= 1;
		position[1] += 1;
		ret |= Y | BACK;
	}
	while (position[2] > 1 + THRESHOLD)
	{
#ifdef DEBUGSPACE
		cout << "z" << position[2] << endl;
#endif
		zone_z += 1;
		position[2] -= 1;
		ret |= Z | FORWARD;
	}
	while (position[2] < -THRESHOLD)
	{
#ifdef DEBUGSPACE
		cout << "z" << position[2] << endl;
#endif
		zone_z -= 1;
		position[2] += 1;
		ret |= Z | BACK;
	}
	if(ret)_flush();
	return ret;
}

void space::setRelativePosition(float magnify)
{
    rx = 0.25 + rand() * 0.5f / RAND_MAX;
    ry = 0.25 + rand() * 0.5f / RAND_MAX;
    rz = 0.25 + rand() * 0.5f / RAND_MAX;
    randMass = rand() * 0.5f / RAND_MAX + 1.0f ;
    randRadius = rand() * 0.1f / RAND_MAX + 0.1f;
    randRadius *= magnify;
    randTextureID = rand() % 10;
}

int space::size() {
    return bodyVec.size();
}

body &space::operator[](int idx)
{
    return bodyVec[idx];
}

void space::_flush() {
    if(!ableToFlush)
        return;
#ifdef LOADBG
    bodyVec[0].x = position[0];
    bodyVec[0].y = position[1];
    bodyVec[0].z = position[2];
#endif
    bodyVec.erase(bodyVec.begin() + 1, bodyVec.end());
    int cnt = 0;
    int randNum;
    bool empty = true;
    if(hasPlanet(zone_x, zone_y, zone_z)) {
        ++ cnt;
        setRelativePosition(0.1f);
        bodyVec.push_back(body(CENTRALSTAR, randMass, randRadius, rx, ry, rz));
        bodyVec[bodyVec.size() - 1].bindBuffer(4, randTextureID);
        randNum = rand();
        empty = false;
    }

    for(int i = -5; i <= 5; ++i)
    {
        for(int j = -5; j <= 5; ++j )
        {
            for(int k = -5; k <= 5; ++k)
            {
                if((i != 0 || j != 0 || k != 0)
                        && hasPlanet(zone_x + i, zone_y + j, zone_z + k))
                {
                    ++cnt;
                    int fine = 1;
                    if( i * i + j * j + k * k < 5)
                        fine = 2;
                    setRelativePosition(0.1f);
                    bodyVec.push_back(body(STAR, randMass, randRadius,
                                           i + rx, j + ry, k + rz));
                    bodyVec[bodyVec.size() - 1]
                            .bindBuffer(fine, randTextureID);
                }
            }
        }
    }

    planetVec.clear();
    if(!empty)
        addPlanet(planetVec, randNum, &bodyVec[1]);

	bgLoader.factor2 = cnt * 3 + 1;
	bodyVec[0].textureBuffer = bgLoader.genBuffer(*this);
}

vector<planet> &space::getPlanets()
{
    return planetVec;
}

#include "density.h"
#ifndef M_PI
	#define M_PI 3.141592654
#endif

float rhoCal(float x, float y, float z, float F1, float F2)
{
    if (x < -0.1f || x > 0.1f)
    {
        return 0;
    }
    if (y < -1.f || y > 1.f)
    {
        return 0;
    }
    if (z < -1.f || z > 1.f)
    {
        return 0;
    }
    float r = sqrt(y * y + z * z);
    rotateTheta(y, z, r * 4 * M_PI);
    r = sqrt(x * x + y * y);
    return exp(- F1 * r) / F2;
}

bool hasPlanet(int x, int y, int z, float F1, float F2)
{
    float rho = rhoCal(x * 0.1f / HEIGHT, y * 1.0f / WIDTH, z * 1.f / WIDTH, F1, F2 );
    x = x % 79;
    x += 19;
    y = y % 15107;
    y += 13;
    z = z % 39373;
    z += 17;
    unsigned seed = x * y * z;
    srand(seed);
    return rand() * 1.0f / RAND_MAX < rho;
}

int amendStep(int pos, float &step, float direction, int Boundary)
{
    if((pos + step * direction) < -Boundary)
    {
        if(direction <= 0)
            return -1;
        else
        {
            step = (-Boundary - pos) / direction + 1 / direction;
            return 0;
        }
    }
    if((pos + step * direction) > Boundary)
    {
        if(direction >= 0)
            return -1;
        else
        {
            step = (Boundary - pos) / direction - 1 / direction;
            return 0;
        }
    }
    return 1;
}

bool MC_Detect(int pos_x, int pos_y, int pos_z,
               float rx, float ry, float rz,
               float F1, float F2)
{
    float step = FINE;
    while(true)
    {
        int rstX = amendStep(pos_x, step, rx, HEIGHT);
        if(rstX == -1)
            break;
        else if(rstX == 0)
            continue;
        int rstY = amendStep(pos_y, step, ry, WIDTH);
        if(rstY == -1)
            break;
        else if(rstY == 0)
            continue;
        int rstZ = amendStep(pos_z, step, rz, WIDTH);
        if(rstZ == -1)
            break;
        else if(rstZ == 0)
            continue;

        if(hasPlanet(pos_x + step * rx,
                     pos_y + step * ry,
                     pos_z + step * rz,
                     F1, F2))
            return true;

        step *= 2;
    }
    return false;
}

void _pointBG(byte *ret, unsigned color, int i, int j)
{
	if (i < 0 || i >= CONVAS || j < 0 || j >= CONVAS)return;
	ret[i * CONVAS * 3 + j * 3] = color & 0x000000ff;
	ret[i * CONVAS * 3 + j * 3 + 1] = (color >> 8) & 0x000000ff;
	ret[i * CONVAS * 3 + j * 3 + 2] = (color >> 16) & 0x000000ff;
}

void pointBG(byte *ret, unsigned color, int i, int j, int division)
{
    for(int idx1 = -division+1; idx1 < division; ++idx1)
    {
        for(int idx2 = -division+1; idx2 < division; ++idx2)
        {
            if(idx1 * idx1 + idx2 * idx2 < division * division / 2)
                _pointBG(ret, color, idx1 + i * division, idx2 + j * division);
        }
    }
}

byte *getBg(int pos_x, int pos_y, int pos_z, float F1, float F2)
{
    unsigned int color;
    byte * ret = new byte[CONVAS * CONVAS * 3];
    for(int i = 0; i < CONVAS * CONVAS * 3; ++i)
        ret[i] = 0x00;
    int division = 4;
    for(int i = 0; i < CONVAS / division; ++ i)
    {
        for (int j = 0; j < CONVAS / division; ++j)
        {
            float rx = cos(j * M_PI * 2 / (CONVAS / division) ) * sin(i * M_PI / (CONVAS / division));
            float ry = sin(j * M_PI * 2 / (CONVAS / division) ) * sin(i * M_PI / (CONVAS / division));
            float rz = cos(i * M_PI / (CONVAS / division));
            if(MC_Detect(pos_x, pos_y, pos_z, rx, ry, rz, F1, F2))
            {
                color = 0xff8888ff;
                int offset = rand() % 120;
                color += offset << 8;
                color += offset << 16;
                pointBG(ret, color, i, j, division);
            }
        }
    }
    return ret;
}

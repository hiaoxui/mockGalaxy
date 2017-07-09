#ifndef BACKGROUNDLOADER
#define BACKGROUNDLOADER

#include <string>
#include <cstring>
#include <vector>
#include <cmath>

#include "util.h"

// load the backgroung picture
class backgroundLoader
{
public:

    // constructor
    backgroundLoader();

    // generate the texture buffer
    GLuint* genBuffer(const space &evm);

    // the factors that Monte Carlo algorithm will ues
    float factor1 = 20, factor2 = 10;

private:

    // release the buffer
    void deleteBuffer();

    // helper function of genBuffer
    GLuint* _genBuffer(const space &evm);

    // the buffer ID
    GLuint *bufferID;

    // last position that background loads at
    int lastZoneX;
    int lastZoneY;
    int lastZoneZ;
};

#endif // BACKGROUNDLOADER


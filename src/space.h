#ifndef BODIES
#define BODIES

#define THRESHOLD 0.1

#include "util.h"
#include "sphere.h"
#include "density.h"
#include "body.h"
#include "backgroundloader.h"
#include "planet.h"

#define X 1
#define Y 2
#define Z 4

#define FORWARD 8
#define BACK 16

// the space, include ship, stars, planets and so on
class space {
    friend class backgroundLoader;
public:

    // whether the space need to flush
    bool ableToFlush = true;

    // constructor, given the current position of player
    space(float curr_x, float curr_y, float curr_z);

    // move the sky
    void moveSky();

    // flush the space
    int flush();

    // set the parameters of star
    void setRelativePosition(float magnify);

    // the number of stars
    int size();

    // get the idxTH star
    body &operator[](int idx);

    // get all planets
    vector<planet> &getPlanets();

    // current zone id
    int zone_x, zone_y, zone_z;

private:

    // relative positions
    float rx, ry, rz;
    // the mass of star
    float randMass;
    // the radius of star
    float randRadius;
    // the rank of star
    int randRank;
    // the texture the star will have
    int randTextureID;

    // to load the background picture
    backgroundLoader bgLoader;

    // all stars and background picture
    vector<body> bodyVec;
    // all planets
    vector<planet> planetVec;

    // will be invoked in flush function
    void _flush();
};

#endif // BODIES

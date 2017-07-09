#ifndef SHIP
#define SHIP

#include <glm/glm.hpp>

class space;

// include some infomation of ship
class ship
{
public:
    // some parameter about relativity
    static glm::dvec3 r,beta;

    // direction
    static glm::dvec3 front, up, right;
    // some information about ship
    static glm::dmat3 shipMatrix;
    // judge if the ship need to be updated
    static bool needUpdate;
    // judge if relativity need to be counted in
    static bool relative;
    // some parameters about relativity
    static double gamma,t;
    // the space the ship is in
    static space *evm_pt;
    // initiate
    static void init();

    // get Matrix
    static glm::dmat3 getMatrix();

    // default constructor is banned
    ship() = delete;

    // move forward
    static void forward(float delta);
    // move left
    static void leftward(float delta);
    // turn left
    static void turn_left(float theta);
    // turn up
    static void turn_up(float theta);
    // move to next frame
    static void nextFrame(double dt);
    // orbit around a given star
    static void makeOrbit();
};

#endif

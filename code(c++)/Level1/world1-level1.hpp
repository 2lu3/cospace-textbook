#ifndef WORLD1_LEVEL1_HPP
#define WORLD1_LEVEL1_HPP

#include "./../cospaceBasicSettings.hpp"
#include "./../judgeColorTools.hpp"

class World1
{
public:
    void setup();
    void loop();
    int shouldTeleport();
    void taskOnTeleport();

private:
    const int kFindObjDuration = 47;
};

#endif //!WORLD1_LEVEL1_HPP

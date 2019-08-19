#ifndef WORLD1_LEVEL2_HPP
#define WORLD1_LEVEL2_HPP

#include "cospaceBasicSettings.hpp"
#include "judgeColorTools.hpp"

class World1Level2
{
public:
    void setup();
    void loop();
    int shouldTeleport();
    void taskOnTeleport();

private:
    const int kFindObjDuration = 47;
};

#endif //!WORLD1_LEVEL2_HPP

#ifndef WORLD2_LEVEL1_HPP
#define WORLD2_LEVEL1_HPP

#include "./../cospaceBasicSettings.hpp"
#include "./../judgeColorTools.hpp"

class World2
{
public:
    void setup();
    void loop();

private:
    const int kFindObjDuration = 47;
    int process = 0;

    void GoToAngle(int angle);
    void GoToPosition(int x, int y);
};

#endif //!WORLD2_LEVEL1_HPP

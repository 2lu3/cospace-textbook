#ifndef WORLD2_LEVEL2_HPP
#define WORLD2_LEVEL2_HPP

#include "./../cospaceBasicSettings.hpp"
#include "./../judgeColorTools.hpp"

class World2Level2
{
public:
    void setup();
    void loop();

private:
    const int kFindObjDuration = 47;
    int process = 0;

    void GoToAngle(int angle);
    bool GoToPosition(int x, int y, int wide_judge_arrived);
};

#endif //!WORLD2_LEVEL2_HPP

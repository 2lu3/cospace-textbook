#ifndef WORLD2_LEVEL3_HPP
#define WORLD2_LEVEL3_HPP

#include "./../cospaceBasicSettings.hpp"
#include "./../judgeColorTools.hpp"

class World2Level3
{
public:
    void setup();
    void loop();

private:
    const int kFindObjDuration = 47;
    int process = 0;
    int pos_x, pos_y;

    void GoToAngle(int angle);
    bool GoToPosition(int x, int y, int wide_judge_arrived);
    int obstacle(int left, int front, int right);
};

#endif //!WORLD2_LEVEL3_HPP

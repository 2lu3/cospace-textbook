#ifndef WORLD2_LEVEL4_HPP
#define WORLD2_LEVEL4_HPP

#include "./../cospaceBasicSettings.hpp"
#include "./../judgeColorTools.hpp"

class World2Level4
{
public:
    void setup();
    void loop();

private:
    const int kFindObjDuration = 47;
    int process = 0;
    int pos_x, pos_y;
    int log_super_x = -1, log_super_y = -1; // to get super obj

    void GoToAngle(int angle);
    bool GoToPosition(int x, int y, int wide_judge_arrived);
    int obstacle(int left, int front, int right);
    void GoToSuperObj();
};

#endif //!WORLD2_LEVEL4_HPP

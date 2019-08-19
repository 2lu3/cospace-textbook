#ifndef WORLD2_LEVEL5_HPP
#define WORLD2_LEVEL5_HPP

#include <random>

#include "cospaceBasicSettings.hpp"
#include "judgeColorTools.hpp"

class World2Level5
{
public:
    void setup();
    void loop();

private:
    class RandInt
    {
    public:
        RandInt() : mt(std::random_device()()), dist(1, INT_MAX)
        {
        }

        inline int operator()()
        {
            return dist(mt);
        }

    private:
        std::mt19937 mt;
        std::uniform_int_distribution<int> dist;
    };
    RandInt rnd;

    const int kFindObjDuration = 47;
    int process = 0;
    int pos_x, pos_y;
    int log_super_x = -1, log_super_y = -1; // to get super obj

    void GoToAngle(int angle);
    bool GoToPosition(int x, int y, int wide_x, int wide_y, int wide_judge_arrived);
    int obstacle(int left, int front, int right);
    void GoToSuperObj();
};

#endif //!WORLD2_LEVEL5_HPP

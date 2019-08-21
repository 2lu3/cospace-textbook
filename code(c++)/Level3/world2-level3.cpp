#include "world2-level3.hpp"

void World2Level3::setup()
{
}

void World2Level3::loop()
{
    // for position lost area
    if (PositionX != 0 || PositionY != 0)
    {
        pos_x = PositionX;
        pos_y = PositionY;
    }
    else
    {
        // in position lost area
        PositionX = -1;
    }

    if (SuperDuration > 0)
    {
        SuperDuration--;
    }
    else if (EitherColorJudge(red_obj) && loaded_objects[RED_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[RED_LOADED_ID]++;
    }
    else if (EitherColorJudge(cyan_obj) && loaded_objects[CYAN_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[CYAN_LOADED_ID]++;
    }
    else if (EitherColorJudge(black_obj) && loaded_objects[BLACK_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[BLACK_LOADED_ID]++;
    }
    else if (EitherColorJudge(object_box) && LoadedObjects != 0)
    {
        if (BothColorJudge(object_box))
        {
            action = DEPOSIT_OBJ;
            SuperDuration = 50;
        }
        else if (ColorJudgeLeft(object_box))
        {
            motor(3, 0);
        }
        else
        {
            motor(0, 3);
        }
    }
    else if (EitherColorJudge(trap_line))
    {
        motor(-3, 3);
    }
    else if (Duration > 0)
    {
        Duration--;
    }
    else
    {
        if (process == 0)
        {
            if (GoToPosition(25, 25, 10))
            {
                ++process;
            }
        }
        else if (process == 1)
        {
            if (GoToPosition(85, 25, 10))
            {
                ++process;
            }
        }
        else if (process == 2)
        {
            if (GoToPosition(210, 170, 10))
            {
                process = 0;
            }
        }
        else
        {
            process = 0;
        }
    }

    switch (action)
    {
    case DEFINED:
        // defined by motor();
        break;
    case FIND_OBJ:
        if (Duration == kFindObjDuration || SuperDuration == kFindObjDuration)
        {
            LoadedObjects++;
        }
        LED_1 = 1;
        MyState = 0;
        WheelLeft = 0;
        WheelRight = 0;
        if (Duration == 0 && SuperDuration == 0)
        {
            LED_1 = 0;
        }
        break;
    case DEPOSIT_OBJ:
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 2;
        MyState = 0;
        LoadedObjects = 0;
        if (Duration <= 6 && SuperDuration <= 6)
        {
            // When I finish Deposit, I back
            LED_1 = 0;
            motor(-5, -5);
        }
        else
        {
            // if I go out during the deposit, I set LoadedObjects as 6 and retry deposit
            if (!BothColorJudge(object_box))
            {
                LoadedObjects = 6;
                Duration = 0;
                SuperDuration = 0;
                for (int i = 1; i < 4; i++)
                {
                    loaded_objects[i] = 2;
                }
                action = DEFINED;
            }
        }
        break;

    default:
        break;
    }
}

void World2Level3::GoToAngle(int angle)
{
    angle = angle - Compass;
    angle %= 360;
    if (angle < -180)
    {
        angle += 360;
    }
    if (angle > 180)
    {
        angle -= 360;
    }

    int classification = obstacle(10, 10, 10);
    switch (classification)
    {
    case 0:
        // abs(number) function gives the absolute value of number
        // abs(数字)関数は、数字の絶対値を返す
        if (abs(angle) < 10)
        {
            // If the target angle is on your front
            // 目的の方向が今向いている方向なら
            motor(5, 5);
        }
        else if (abs(angle) < 30)
        {
            if (angle < 0)
            {
                motor(5, 4);
            }
            else
            {
                motor(4, 5);
            }
        }
        else if (abs(angle) < 100)
        {
            if (angle < 0)
            {
                motor(5, 2);
            }
            else
            {
                motor(2, 5);
            }
        }
        else
        {
            if (angle < 0)
            {
                motor(3, -3);
            }
            else
            {
                motor(-3, 3);
            }
        }
        break;

    case 1: // left
        motor(-3, -5);
        break;
    case 2: // front
        motor(-5, -5);
        break;
    case 3: //left & front
        motor(-3, -5);
        break;
    case 4: // right
        motor(-5, -3);
        break;
    case 5: // left & right
        motor(3, 3);
        break;
    case 6: // front & right
        motor(-5, -3);
        break;
    case 7: // all
        motor(-5, 5);
        break;
    default:
        break;
    }

    // If the angle > 0, the target angle is on your left side
    // If the angle < 0, the traget angle is on your right side
    // angleが0より大きいなら、目的の方向はロボットからみて左側にある
    // angleが0より小さいなら、目的の方向はロボットから見て右側にある
}

// Problems 問題点
// If the robot is in Position Lost Area
// もし、ロボットが座標喪失エリアにいたら？

bool World2Level3::GoToPosition(int x, int y, int wide_judge_arrived)
{
    if (x - wide_judge_arrived < pos_x && pos_x < x + wide_judge_arrived && y - wide_judge_arrived < pos_y && pos_y < y + wide_judge_arrived)
    {
        motor(0, 0);
        return true;
    }
    x = x - pos_x;
    y = y - pos_y;
    // There is 90 degrees difference between math degree and cospace angle
    // 数学上での角と、Cospaceの角度には90度の差がある
    int angle = static_cast<int>((atan2(y, x) / M_PI * 180.0)) - 90;
    GoToAngle(angle);
    return false;
}

int World2Level3::obstacle(int left, int front, int right)
{
    int ans = 0;
    if (US_Left < left)
    {
        ++ans;
    }
    if (US_Front < front)
    {
        ans += 2;
    }
    if (US_Right < right)
    {
        ans += 4;
    }
    return ans;
}

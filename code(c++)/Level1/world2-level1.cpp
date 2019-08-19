#include "world2-level1.hpp"

void World2::setup()
{
}

void World2::loop()
{
    if (SuperDuration > 0)
    {
        SuperDuration--;
    }
    // If the the robot is on the Red Object and The number of red loaded objects is less than 2
    // もしレッドオブジェクトの上にいて、すでに持っているレッドオブジェクトが2こ以下の場合
    else if (EitherColorJudge(red_obj) && loaded_objects[RED_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[RED_LOADED_ID]++;
    }
    // If the robot is on the Cyan Object and The number of Cyan loaded objects is less than 2
    // もし、シアンオブジェクトの上にいて、すでに持っているシアンオブジェクトの数が2こより少ない場合
    else if (EitherColorJudge(cyan_obj) && loaded_objects[CYAN_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[CYAN_LOADED_ID]++;
    }
    // If the robot is on the Black Object and The number of Cyan loaded objects is less than 2
    // もし、ブラックオブジェクトの上にいて、すでに持っているブラックオブジェクトの数が2こより少ない場合
    else if (EitherColorJudge(black_obj) && loaded_objects[BLACK_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[BLACK_LOADED_ID]++;
    }
    else if (EitherColorJudge(object_box) && LoadedObjects != 0)
    {
        // To Deposit, both color sensors are must in deposit area
        if (BothColorJudge(object_box))
        {
            // If both color sensors are in deposit area
            // もし、両方のセンサがDepositエリアに入っている場合
            action = DEPOSIT_OBJ;
            SuperDuration = 50;
        }
        else if (ColorJudgeLeft(object_box))
        {
            // If only left sensor is in deopsit area
            // 左側のセンサだけがDepositエリアにある場合
            motor(3, 0);
        }
        else
        {
            // If only right sensor is in deposit area
            // 右側のセンサだけがDepositエリアにある場合
            motor(0, 3);
        }
    }
    // If the robot is on the yellow
    // ロボットが黄色いトラップの上の場合
    else if (EitherColorJudge(trap_line))
    {
        motor(-3, 3);
    }
    else if (Duration > 0)
    {
        Duration--;
    }
    else if (US_Left < 10 || US_Front < 10 || US_Right < 10)
    {
        // If the robot is near the wall, turn left
        // 壁が近くにある場合、よける
        motor(-3, 3);

        // If you know a lot about c++, you should use this function
        // もし、C++をよく知っているなら、次のようにしてください
        // else if(obstacle(10, 10, 10))
    }
    else
    {
        if (process == 0)
        {
            if (!(20 < PositionX && PositionX <= 30 && 20 < PositionY && PositionY <= 30))
            {
                // If the robot is not in the target area
                GoToPosition(25, 25);
            }
            else
            {
                // If the robot is in the target area
                process++;
            }
        }
        else if (process == 1)
        {
            if (!(80 < PositionX && PositionX <= 90 && 20 < PositionY && PositionY <= 30))
            {
                GoToPosition(85, 25);
            }
            else
            {
                process++;
            }
        }
        else if (process == 2)
        {
            if (!(200 < PositionX && PositionX <= 220 && 160 < PositionY && PositionY <= 180))
            {
                GoToPosition(210, 170);
            }
            else
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

void World2::GoToAngle(int angle)
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

    // If the angle > 0, the target angle is on your left side
    // If the angle < 0, the traget angle is on your right side
    // angleが0より大きいなら、目的の方向はロボットからみて左側にある
    // angleが0より小さいなら、目的の方向はロボットから見て右側にある

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
}

// Problems 問題点
// If the robot is in Position Lost Area
// もし、ロボットが座標喪失エリアにいたら？

void World2::GoToPosition(int x, int y)
{
    x = x - PositionX;
    y = y - PositionY;
    // There is 90 degrees difference between math degree and cospace angle
    // 数学上での角と、Cospaceの角度には90度の差がある
    int angle = static_cast<int>((atan2(y, x) / M_PI * 180.0)) - 90;
    GoToAngle(angle);
}

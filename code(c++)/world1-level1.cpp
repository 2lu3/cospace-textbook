#include "world1-level1.hpp"

#define FOR for
#define rep(i, n) FOR(int i = 0; i < n; i++)

using namespace std;

void World1::setup()
{
}

void World1::loop()
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
    else if (EitherColorJudge(cyan_obj) && loaded_objects[RED_LOADED_ID] < 2)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[CYAN_LOADED_ID]++;
    }
    // If the robot is on the Black Object and The number of Cyan loaded objects is less than 2
    // もし、ブラックオブジェクトの上にいて、すでに持っているブラックオブジェクトの数が2こより少ない場合
    else if (EitherColorJudge(black_obj) && loaded_objects[RED_LOADED_ID] < 2)
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
        motor(3, 3);
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

int World1::shouldTeleport()
{
    return 180 > Time && !EitherColorJudge(object_box);
}

void World1::taskOnTeleport()
{
    LoadedObjects = 0;
    rep(i, static_cast<int>(extent<decltype(loaded_objects), 0>::value))
    {
        loaded_objects[i] = 0;
    }
    // teleport location
    Teleport = 1;
    CurGame = 1;
}

#include "cospaceBasicSettings.hpp"
#include "world1.hpp"
#include "world2.hpp"

#define _CRT_SECURE_NO_WARNINGS 1

World1 game0;
World2 game1;
using namespace std;

void Game0()
{
    static int triger = 0;
    if (triger == 0)
    {
        triger = 1;
        game0.setup();
    }
    if (game0.shouldTeleport())
    {
        game0.taskOnTeleport();
    }
    game0.loop();
}

void Game1()
{
    static int triger = 0;
    if (triger == 0)
    {
        game1.setup();
        triger = 1;
    }
    game1.loop();
}

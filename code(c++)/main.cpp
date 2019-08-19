#include "cospaceBasicSettings.hpp"
#include "Level1/world1-level1.hpp"
#include "Level1/world2-level1.hpp"
#include "Level2/world1-level2.hpp"
#include "Level2/world2-level2.hpp"

#define _CRT_SECURE_NO_WARNINGS 1

// level 1
World1 game0;
World2 game1;

// level 2
// Please un-comment if you try level-2
// level2に挑戦するときは、アンコメントしてください
// World1Level2 game0;
// World2Level2 game1;

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

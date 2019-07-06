#ifndef JUDGE_COLOR_TOOLS
#define JUDGE_COLOR_TOOLS

#include "cospaceBasicSettings.hpp"

extern int red_obj[3][2];
extern int cyan_obj[3][2];
extern int black_obj[3][2];
extern int trap_line[3][2];
extern int blue_zone[3][2];
extern int object_box[3][2];
extern int gray_zone[3][2];
extern int sp_obj[3][2];
extern int purple_line[3][2];
extern int white_zone[3][2];
extern int blue_trap[3][2];

int ColorJudgeLeft(int coloror[3][2]);
int ColorJudgeRight(int color[3][2]);
int EitherColorJudge(int color[3][2]);
int BothColorJudge(int color[3][2]);

#endif // !JUDGE_COLOR_TOOLS

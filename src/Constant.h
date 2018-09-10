#ifndef CONSTANT_H
#define CONSTANT_H
#include "QDebug"
//场景编号
enum SCENE_TYPE{START,BATTLE,STORY,SELECT
};
typedef int SCENE_ID;
const int SCENE_START = 1000;
const int SCENE_BATTLE_1 = 2000;
const int SCENE_BATTLE_2 = 2001;
const int SCENE_BATTLE_3 = 2002;
const int SCENE_BATTLE_4 = 2003;
const int SCENE_STORY_1 = 3000;
const int SCENE_STORY_2 = 3001;
const int SCENE_STORY_3 = 3002;
const int SCENE_STORY_ENDING_BAD = 3003;
const int SCENE_STORY_ENDING_TRUE = 3004;
const int SCENE_STORY_ENDING_HAPPY = 3005;
const int SCENE_STORY_THANKS = 3006;
const int SCENE_SELECT_1 = 4000;


const int DEFAULT_FPS = 60;
const double DEFAULT_INTERVAL = 1000.0/DEFAULT_FPS;

//修改scene的情况
typedef int  CONDITIONS_ID;
typedef QSet<CONDITIONS_ID> S_CONDITIONS;//S for set
                                         //原作者推荐的set,但SET真的不好用 感觉暂时用不到
//start                                  //主要C++中Set 太难用了
const int CONDITION_DEBUG = 1000;
const int CONDITION_TO_BATTLE = 1001;//避免0001 因为0开头代表八进制
const int CONDITION_QUIT = 1002;
const int CONDITION_LOAD = 1003;
//STORY
const int CONDITION_SAVE = 1004;
//battle
const int CONDITION_WIN = 1005;
const int CONDITION_LOSE = 1006;
//SELECT
const int CONDITION_TO_SELECT = 1007;
const int CONDITION_SELECT_GE = 1008;
const int CONDITION_SELECT_IE = 1009;//insanity ending
//
const int CONDITION_NEW_GAME_PLUS = 1010;

#define COLOR_AOI 139,129,195,50
#define HP_OF_BLOCK 1
#endif // CONSTANT_H

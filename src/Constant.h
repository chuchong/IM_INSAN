#ifndef CONSTANT_H
#define CONSTANT_H
#include "QDebug"
//场景编号
enum SCENE_TYPE{START,BATTLE,STORY,SELECT
};
typedef int SCENE_ID;
const int SCENE_START = 1000;
const int SCENE_START_BALCK = 1001;
const int SCENE_BATTLE_1 = 2000;
const int SCENE_BATTLE_2 = 2001;
const int SCENE_BATTLE_3 = 2002;
const int SCENE_BATTLE_4 = 2003;
const int SCENE_STORY_1_1 = 3000;
const int SCENE_STORY_1_2 = 3001;
const int SCENE_STORY_1_3 = 3002;
const int SCENE_STORY_ENDING_BAD = 3003;

const int SCENE_STORY_ENDING_TRUE = 3004;
const int SCENE_STORY_ENDING_HAPPY = 3005;
const int SCENE_STORY_THANKS = 3006;
const int SCENE_STORY_ENDING_LOSE = 3007;
const int SCENE_SELECT_1 = 4000;


const int DEFAULT_FPS = 60;
const double DEFAULT_INTERVAL = 1000.0/DEFAULT_FPS;

//修改scene的情况
typedef int  CONDITIONS_ID;
typedef QSet<CONDITIONS_ID> S_CONDITIONS;//S for set
                                         //原作者推荐的set,但SET真的不好用 感觉暂时用不到

//start
//主要C++中Set 太难用了
const int CONDITION_DEBUG = 1000;
const int CONDITION_START = 1001;//避免0001 因为0开头代表八进制
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

const qreal VELOCITY_OF_BAIT = 0.2;
#define COLOR_AOI 139,129,195,50

const int FRAME = 1000 / 60;

//鱼的血量为1000
const int LOGIC_INPUT_DANGER = 0;
const int LOGIC_INPUT_SAFE = 1;
const int LOGIC_INPUT_FEED = 2;
const int LOGIC_INPUT_HEAL = 3;
const int LOGIC_INPUT_CLICK = 4;
const int LOGIC_INPUT_REACHTIME = 5;
const int LOGIC_INPUT_ACTIVATE = 6;

const int OUTPUT_SUCCESS = 0;
const int OUTPUT_UNSUCCESS = 1;
const int OUTPUT_MONEY = 2;
const int OUTPUT_ALIEN = 3;
const int OUTPUT_ALIEN_NO_EFFECT = 4;

const int EFFECT_SUCCESS = 0;
const int EFFECT_UNSUCCESS = 1;
const int HP_OF_BLOCK = 1;

#define HP_OF_BLOCK 1
#endif // CONSTANT_H

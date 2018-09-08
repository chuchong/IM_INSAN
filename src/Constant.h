#ifndef CONSTANT_H
#define CONSTANT_H
#include "QDebug"
//场景编号
enum SCENE_TYPE{START,BATTLE,STORY,SELECT
};
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
typedef int SCENE_NUMBER;


#define HP_OF_BLOCK 1
#endif // CONSTANT_H

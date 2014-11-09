/************************************************************************/
/* 
**  Date   :   2013/9/21

** author  :   Bright Moon

** blog :  
** CSDN: http://blog.csdn.net/chenhaobright
** github: https://github.com/chenhaobright

** function:   游戏的主逻辑，全部放在此模块中， 主要包括：
			   1、游戏泡泡和等待发射的泡泡初始化
			   2、游戏触摸的开关和处理
			   3、泡泡的碰撞检测和处理（调整泡泡的位置）
			   4、碰撞后查找相同泡泡的算法
			   5、泡泡的消除
			   6、消除后是否有悬挂泡泡的检测
*/
/************************************************************************/

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
};
#endif

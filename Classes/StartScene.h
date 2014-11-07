#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class StartLayer : public cocos2d::Layer
{
public:

	StartLayer();
	~StartLayer();
    // a selector callback
	void menuCloseCallback(Ref* pSender);

	void menuNewGameCallback(Ref* pSender);

};

#endif  // __HELLOWORLD_SCENE_H__